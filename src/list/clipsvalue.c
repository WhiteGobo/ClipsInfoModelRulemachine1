#include "ClipsInfoModelRulemachine1_list.h"
#include "ClipsInfoModelRulemachine1_externaladdress.h"
#include "shared_information.h"

/*
 * return negative on failure
 */
static int normalize_index(int index, size_t length);
static int MBAppendMultifieldAsCV(Environment*, MultifieldBuilder*, CLIPSValue*);

extern Multifield* Fact_get_termlist(Environment*, Fact*);
extern Fact* CLIPSValue_new_termlist_as_fact(Environment* env, Multifield* items, CLIPSValue rest);
extern bool Fact_is_list(Environment *env, Fact*);

bool CLIPSValue_is_list(Environment* env, CLIPSValue cv){
	CIMR1List* tmplist;
	switch(cv.header->type){
		case FACT_ADDRESS_TYPE:
			fprintf(stderr, "is_list: fact\n");
			return Fact_is_list(env, cv.factValue);
		case EXTERNAL_ADDRESS_TYPE:
			fprintf(stderr, "is_list: external address\n");
			tmplist = CVExternalAddress_get_CIMR1List(cv.externalAddressValue);
			return tmplist != NULL;
		case MULTIFIELD_TYPE:
			fprintf(stderr, "ERROR Missing type implementation for CLIPSValue_is_list\n");
		default:
			return false;
	}
}


CLIPSValue CLIPSValue_new_termlist(Environment* env, Multifield* items, CLIPSValue rest)
{
	CLIPSValue ret;
	ret.factValue = CLIPSValue_new_termlist_as_fact(env, items, rest);
	if (ret.factValue == NULL){
		fprintf(stderr, "ERROR CLIPSValue_new_termlist not fully implemented\n");
		ret.voidValue = VoidConstant(env);
	}
	return ret;
}


Multifield* CLIPSValue_get_termlist(Environment* env, CLIPSValue cv){
	switch(cv.header->type){
		case FACT_ADDRESS_TYPE:
			return Fact_get_termlist(env, cv.factValue);
		case EXTERNAL_ADDRESS_TYPE:
		case MULTIFIELD_TYPE:
		default:
			WriteString(env, STDERR, "CLIPSValue_get_termlist "
					"not implemented for:");
			WriteCLIPSValue(env, STDERR, &cv);
			WriteString(env, STDERR, "\n");
			return NULL;
	}
}


bool CLIPSValue_contains(Environment* env, CLIPSValue container, CLIPSValue item){
	Multifield *f1;
	f1 = CLIPSValue_get_termlist(env, container);
	if (f1 == NULL){
		return false;
	}
	for(size_t i=0; i<f1->length; i++){
		if (f1->contents[i].value == item.value){
			return true;
		}
	}
	return false;
}


int CLIPSValue_length(Environment* env, CLIPSValue cv){
	Multifield *f1;
	f1 = CLIPSValue_get_termlist(env, cv);
	if (f1 == NULL){
		return -1;
	}
	return f1->length;
}


CLIPSValue CLIPSValue_get_item(Environment* env, CLIPSValue cv, int index){
	CLIPSValue ret = {.voidValue = VoidConstant(env)};
	Multifield *f1;
	f1 = CLIPSValue_get_termlist(env, cv);
	if (f1 == NULL){
		return ret;
	}
	index = normalize_index(index, f1->length);
	if (index < 0){
		fprintf(stderr, "CLIPSValue_get_item got index out of bounds\n");
		return ret;
	}
	ret.value = f1->contents[index].value;
	return ret;
}

CLIPSValue CLIPSValue_sublist(Environment* env, CLIPSValue cv, int start, int length)
{
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	f1 = CLIPSValue_get_termlist(env, cv);
	if (f1 == NULL){
		fprintf(stderr, "ERROR sublist got no list\n");
		return void_value;
	}
	if (start < 0){
		start = 0;
	} else if (start > f1->length){
		start = f1->length;
	}
	if(length < 0 || length > f1->length){
		length = f1->length;
	}

	mb = CreateMultifieldBuilder(env, length);
	for(size_t i = start; i < start + length; i++){
		MBAppend(mb, f1->contents + i);
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR sublist. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_append(Environment* env, CLIPSValue list, CLIPSValue item){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, list);
	if (f1 == NULL){
		return void_value;
	}

	switch(item.header->type){
		case MULTIFIELD_TYPE:
			length = f1->length + item.multifieldValue->length;
			break;
		default:
			length = f1->length + 1;
			break;
	}
	mb = CreateMultifieldBuilder(env, length);
	MBAppendMultifield(mb, f1);
	MBAppend(mb, &item);
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR append. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_concatenate(Environment* env, CLIPSValue first, CLIPSValue second){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *f2, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, first);
	if (f1 == NULL){
		return void_value;
	}
	f2 = CLIPSValue_get_termlist(env, second);
	if (f2 == NULL){
		return void_value;
	}

	length = 0;
	length += f1->length;
	length += f2->length;

	mb = CreateMultifieldBuilder(env, length);
	MBAppendMultifield(mb, f1);
	MBAppendMultifield(mb, f2);
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR concatenate. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_insert_before(Environment* env, CLIPSValue list, int position, CLIPSValue item)
{
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, list);
	if (f1 == NULL){
		return void_value;
	}

	length = f1->length + 1;
	mb = CreateMultifieldBuilder(env, length);
	CLIPSValue *x;
	position = normalize_index(position, f1->length);
	if (position < 0){
		fprintf(stderr, "ERROR insert_before: position out of bounds\n");
		return void_value;
	}
	for(size_t i=0; i<position; i++){
		x = f1->contents + i;
		switch(x->header->type){
			case MULTIFIELD_TYPE:
				fprintf(stderr, "ERROR insert_before not fully implemented\n");
				return void_value;
			default:
				MBAppend(mb, x);
				break;
		}
	}
	switch(item.header->type){
		case MULTIFIELD_TYPE:
			fprintf(stderr, "ERROR insert_before not fully implemented\n");
			return void_value;
		default:
			MBAppend(mb, &item);
			break;
	}
	for(size_t i=position; i<f1->length; i++){
		x = f1->contents + i;
		switch(x->header->type){
			case MULTIFIELD_TYPE:
				fprintf(stderr, "ERROR insert_before not fully implemented\n");
				return void_value;
			default:
				MBAppend(mb, x);
				break;
		}
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR insert_before. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_remove(Environment* env, CLIPSValue list, int position){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, list);
	if (f1 == NULL){
		return void_value;
	}

	length = f1->length - 1;
	mb = CreateMultifieldBuilder(env, length);
	CLIPSValue *x;
	position = normalize_index(position, f1->length);
	if (position < 0){
		fprintf(stderr, "ERROR remove: position out of bounds\n");
		return void_value;
	}
	for(size_t i=0; i<f1->length; i++){
		if (i == position){
			continue;
		}
		x = f1->contents + i;
		switch(x->header->type){
			case MULTIFIELD_TYPE:
				fprintf(stderr, "ERROR insert_before not fully implemented\n");
				return void_value;
			default:
				MBAppend(mb, x);
				break;
		}
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR remove. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_reverse(Environment* env, CLIPSValue cv){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, cv);
	if (f1 == NULL){
		return void_value;
	}

	mb = CreateMultifieldBuilder(env, f1->length);
	CLIPSValue *x;
	for(int i = f1->length-1; i >= 0; i--){
		x = f1->contents + i;
		switch(x->header->type){
			case MULTIFIELD_TYPE:
				fprintf(stderr, "ERROR reverse not fully implemented\n");
				return void_value;
			default:
				MBAppend(mb, x);
				break;
		}
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR reverse. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_index_of(Environment* env, CLIPSValue list, CLIPSValue item){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	size_t number_found, *indices;
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	f1 = CLIPSValue_get_termlist(env, list);
	if (f1 == NULL){
		return void_value;
	}
	indices = malloc(sizeof(size_t) * f1->length);
	number_found = 0;
	for(size_t j=0; j<f1->length; j++){
		if (f1->contents[j].value == item.value){
			indices[number_found] = j;
			number_found += 1;
		}
	}
	mb = CreateMultifieldBuilder(env, number_found);
	for(size_t i=0; i<number_found; i++){
		MBAppendInteger(mb, indices[i]);
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR index_of. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}



CLIPSValue CLIPSValue_distinct_values(Environment* env, CLIPSValue cv){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, cv);
	if (f1 == NULL){
		return void_value;
	}

	mb = CreateMultifieldBuilder(env, f1->length);
	CLIPSValue x;
	for(size_t i = 0; i<f1->length; i++){
		x = f1->contents[i];
		bool duplicate = false;
		for(int j=i-1; j>=0; j--){
			if (x.value == f1->contents[j].value){
				duplicate = true;
				break;
			}
		}
		if (!duplicate){
			if (0 != MBAppendMultifieldAsCV(env, mb, &x)){
				MBDispose(mb);
				return void_value;
			}
		}
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR distinct values. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_intersect(Environment* env, CLIPSValue first, CLIPSValue second){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, first);
	if (f1 == NULL){
		return void_value;
	}

	mb = CreateMultifieldBuilder(env, f1->length);
	CLIPSValue x;
	for(size_t i = 0; i < f1->length; i++){
		x = f1->contents[i];
		if(CLIPSValue_contains(env, second, x)){
			if (0 != MBAppendMultifieldAsCV(env, mb, &x)){
				MBDispose(mb);
				return void_value;
			}
		}
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR intersect. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}


CLIPSValue CLIPSValue_except(Environment* env, CLIPSValue first, CLIPSValue second)
{
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Multifield *f1, *retlist;
	MultifieldBuilder* mb;
	size_t length;
	f1 = CLIPSValue_get_termlist(env, first);
	if (f1 == NULL){
		return void_value;
	}

	mb = CreateMultifieldBuilder(env, f1->length);
	CLIPSValue x;
	for(size_t i = 0; i < f1->length; i++){
		x = f1->contents[i];
		if(!CLIPSValue_contains(env, second, x)){
			if (0 != MBAppendMultifieldAsCV(env, mb, &x)){
				MBDispose(mb);
				return void_value;
			}
		}
	}
	retlist = MBCreate(mb);
	MBDispose(mb);
	if (retlist == NULL){
		fprintf(stderr, "ERROR except. MBCreate failed\n");
		return void_value;
	}
	return CLIPSValue_new_termlist(env, retlist, void_value);
}

static int normalize_index(int index, size_t length){
	if (index < 0){
		index += length;
	}
	if (index < 0 || index > length){
		return -1;
	}
	return index;
}

static int MBAppendMultifieldAsCV(Environment* env, MultifieldBuilder* mb, CLIPSValue* cv)
{
	switch(cv->header->type){
		case MULTIFIELD_TYPE:
			return -1;
		default:
			MBAppend(mb, cv);
			return 0;
	}
}
