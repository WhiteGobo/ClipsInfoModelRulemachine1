#include "udfdescription.h"
#include "ClipsInfoModelRulemachine1_list.h"
#include "ClipsInfoModelRulemachine1_number.h"

#include "namespace_PRED.h"
#include "namespace_FUNC.h"

const UDFDescription builtinFunctionList_List[];

static void make_list(Environment *env, UDFContext *udfc, UDFValue *out);
static void list_contains(Environment *env, UDFContext *udfc, UDFValue *out);
static void count(Environment *env, UDFContext *udfc, UDFValue *out);
static void get(Environment *env, UDFContext *udfc, UDFValue *out);
static void sublist(Environment *env, UDFContext *udfc, UDFValue *out);
static void append(Environment *env, UDFContext *udfc, UDFValue *out);
static void concatenate(Environment *env, UDFContext *udfc, UDFValue *out);
static void insert_before(Environment *env, UDFContext *udfc, UDFValue *out);
static void my_remove(Environment *env, UDFContext *udfc, UDFValue *out);
static void reverse(Environment *env, UDFContext *udfc, UDFValue *out);
static void index_of(Environment *env, UDFContext *udfc, UDFValue *out);
static void my_union(Environment *env, UDFContext *udfc, UDFValue *out);
static void distinct_values(Environment *env, UDFContext *udfc, UDFValue *out);
static void intersect(Environment *env, UDFContext *udfc, UDFValue *out);
static void except(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_List[] = {
	{"make_list", "*", 0, UNBOUNDED, "*",
		make_list, "make_list"},
	{"<"_FUNC_make_list_">", "*", 0, UNBOUNDED, "*",
		make_list, "make_list"},
	{"<"_PRED_list_contains_">", "*", 2, 2, "*",
		list_contains, "list_contains"},
	{"<"_FUNC_count_">", "*", 1, 1, "*",
		count, "count"},
	{"<"_FUNC_get_">", "*", 2, 2, "*",
		get, "get"},
	{"<"_FUNC_sublist_">", "*", 2, 3, "*",
		sublist, "sublist"},
	{"<"_FUNC_append_">", "*", 2, UNBOUNDED, "*",
		append, "append"},
	{"<"_FUNC_concatenate_">", "*", 2, 2, "*",
		concatenate, "concatenate"},
	{"<"_FUNC_insert_before_">", "*", 3, 3, "*",
		insert_before, "insert_before"},
	{"<"_FUNC_remove_">", "*", 2, 2, "*",
		my_remove, "my_remove"},
	{"<"_FUNC_reverse_">", "*", 1, 1, "*",
		reverse, "reverse"},
	{"<"_FUNC_index_of_">", "*", 2, 2, "*",
		index_of, "index_of"},
	{"<"_FUNC_union_">", "*", 2, 2, "*",
		my_union, "my_union"},
	{"<"_FUNC_distinct_values_">", "*", 1, 1, "*",
		distinct_values, "distinct_values"},
	{"<"_FUNC_intersect_">", "*", 2, 2, "*",
		intersect, "intersect"},
	{"<"_FUNC_except_">", "*", 2, 2, "*",
		except, "except"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};

static Multifield* arguments_as_multifield(Environment*, UDFContext*);


static Multifield* arguments_as_multifield(Environment *env, UDFContext* udfc){
	unsigned int argcount = UDFArgumentCount(udfc);
	UDFValue tmpudf;
	Multifield* ret;
	MultifieldBuilder *mb;
	mb = CreateMultifieldBuilder(env, argcount);
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return NULL;
	}
	MBAppendUDFValue(mb, &tmpudf);
	for(unsigned int i = 1; i< argcount; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
			return NULL;
		}
		MBAppendUDFValue(mb, &tmpudf);
	}
	ret = MBCreate(mb);
	MBDispose(mb);
	return ret;
}


static void is_list(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	UDFValue tmpudf;
	CLIPSValue tmpclips;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	tmpclips.header = tmpudf.header;
	ret = CLIPSValue_is_list(env, tmpclips);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void make_list(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue tmpclips;
	CLIPSValue voidc = {.voidValue = VoidConstant(env)};
	Multifield* mf = arguments_as_multifield(env, udfc);
	if (mf == NULL){
		fprintf(stderr, "func:make-list failed\n");
		UDFThrowError(udfc);
		return;
	}

	tmpclips = CLIPSValue_new_termlist(env, mf, voidc);
	out->header = tmpclips.header;
}

static void list_contains(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_item;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_item.header = tmpudf.header;

	ret = CLIPSValue_contains(env, cv_list, cv_item);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void count(Environment *env, UDFContext *udfc, UDFValue *out){
	int ret;
	UDFValue tmpudf;
	CLIPSValue tmpclips;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	tmpclips.header = tmpudf.header;
	ret = CLIPSValue_length(env, tmpclips);
	if (ret >= 0){
		out->integerValue = CreateInteger(env, ret);
	} else {
		fprintf(stderr, "func:count can only work on lists\n");
		UDFThrowError(udfc);
		return;
	}
}

static void get(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue ret;
	struct ret_CLIPSValue_to_int err_and_index;
	int index;
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_index;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_index.header = tmpudf.header;
	err_and_index = CLIPSValue_to_int(env, cv_index);
	if(0 != err_and_index.err){
		fprintf(stderr, "ERROR: func:get index not int\n");
		UDFThrowError(udfc);
		return;
	}
	index = err_and_index.ret;

	ret = CLIPSValue_get_item(env, cv_list, index);
	if (ret.header->type == VOID_TYPE){
		fprintf(stderr, "func:get failed\n");
		UDFThrowError(udfc);
		return;
	}
	out->header = ret.header;
}

static void sublist(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue ret;
	struct ret_CLIPSValue_to_int err_and_index;
	int start_index, length;
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_index;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_index.header = tmpudf.header;
	err_and_index = CLIPSValue_round_to_int(env, cv_index);
	if(0 != err_and_index.err){
		fprintf(stderr, "ERROR: func:sublist start not a number\n");
		UDFThrowError(udfc);
		return;
	}
	start_index = err_and_index.ret;

	if(UDFHasNextArgument(udfc)){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
			fprintf(stderr, "brubru err1\n");
			UDFThrowError(udfc);
			return;
		}
		cv_index.header = tmpudf.header;
		err_and_index = CLIPSValue_round_to_int(env, cv_index);
		if(0 != err_and_index.err){
			fprintf(stderr, "ERROR: func:sublist end not a number\n");
			UDFThrowError(udfc);
			return;
		}
		length = err_and_index.ret;
		if  (length < 0) {
			length = 0;
		}
	} else {
		//CLIPSValue_sublist returns full list, on negative length
		length = -1;
	}

	ret = CLIPSValue_sublist(env, cv_list, start_index, length);
	if (ret.header->type == VOID_TYPE){
		fprintf(stderr, "func:sublist failed\n");
		UDFThrowError(udfc);
		return;
	}
	out->header = ret.header;
}

static void append(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue ret;
	struct ret_CLIPSValue_to_int err_and_index;
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_item;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	
	while(UDFHasNextArgument(udfc)){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
			fprintf(stderr, "brubru err1\n");
			UDFThrowError(udfc);
			return;
		}
		cv_item.header = tmpudf.header;
		cv_list = CLIPSValue_append(env, cv_list, cv_item);
		if(cv_list.header->type == VOID_TYPE){
			fprintf(stderr, "brubru err1\n");
			UDFThrowError(udfc);
			return;
		}
	}
	out->header = cv_list.header;
}

static void concatenate(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue ret;
	struct ret_CLIPSValue_to_int err_and_index;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2, cv_ret;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.header = tmpudf.header;
	cv_ret = CLIPSValue_concatenate(env, cv1, cv2);
	if(cv_ret.header->type == VOID_TYPE){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	out->header = cv_ret.header;
}

static void insert_before(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue ret;
	struct ret_CLIPSValue_to_int err_and_index;
	UDFValue tmpudf;
	CLIPSValue cvlist, cv_item, cv_index, cv_ret;
	int index;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cvlist.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_index.header = tmpudf.header;
	err_and_index = CLIPSValue_to_int(env, cv_index);
	if (err_and_index.err != 0){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	index = err_and_index.ret;

	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_item.header = tmpudf.header;

	cv_ret = CLIPSValue_insert_before(env, cvlist, index, cv_item);
	if(cv_ret.header->type == VOID_TYPE){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	out->header = cv_ret.header;
}

static void my_remove(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue ret;
	struct ret_CLIPSValue_to_int err_and_index;
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_index, cv_ret;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_index.header = tmpudf.header;
	err_and_index = CLIPSValue_to_int(env, cv_index);
	if(0 != err_and_index.err){
		fprintf(stderr, "ERROR: func:get index not int\n");
		UDFThrowError(udfc);
		return;
	}

	cv_ret = CLIPSValue_remove(env, cv_list, err_and_index.ret);
	if(cv_ret.header->type == VOID_TYPE){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	out->header = cv_ret.header;
}

static void reverse(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_ret;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	cv_ret = CLIPSValue_reverse(env, cv_list);
	if(cv_ret.header->type == VOID_TYPE){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	out->header = cv_ret.header;
}

static void index_of(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv_list, cv_ret, cv_item;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_list.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv_item.header = tmpudf.header;
	cv_ret = CLIPSValue_index_of(env, cv_list, cv_item);
	out->header = cv_ret.header;
}

static void my_union(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv_ret, cv1, cv2;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.header = tmpudf.header;
	cv_ret = CLIPSValue_concatenate(env, cv1, cv2);
	cv_ret = CLIPSValue_distinct_values(env, cv_ret);
	if (cv_ret.header->type == VOID_TYPE){
		UDFThrowError(udfc);
	} else {
		out->header = cv_ret.header;
	}
}

static void distinct_values(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv_ret, cv1, cv2;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.header = tmpudf.header;
	cv_ret = CLIPSValue_distinct_values(env, cv1);
	out->header = cv_ret.header;
}

static void intersect(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv_ret, cv1, cv2;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.header = tmpudf.header;
	cv_ret = CLIPSValue_intersect(env, cv1, cv2);
	out->header = cv_ret.header;
}

static void except(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv_ret, cv1, cv2;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.header = tmpudf.header;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.header = tmpudf.header;
	cv_ret = CLIPSValue_except(env, cv1, cv2);
	out->header = cv_ret.header;
}
