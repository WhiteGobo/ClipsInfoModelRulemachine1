#include "terms.h"
#include "shared_information.h"
#include "ClipsInfoModelRulemachine1_list.h"

#include "percent_encode.h"

typedef struct s_LocalTermMap {
	//guessed
	char prefix[20];
} LocalTermMap;

static struct ret_ExtractList ret_fail_ExtractList(Environment*);
static struct ret_ExtractList Fact_extract_list(Environment*, Fact*);
static struct ret_ExtractList AtomList_extract_list(Environment*, Fact*);
static struct ret_ExtractList Multifield_extract_list(Environment*, Multifield*);

LocalTermMap* LocalTermMap_new(Environment* env){
	size_t id = CIMR1_get_next_local_prefix_id(env);
	LocalTermMap* ret = malloc(sizeof(LocalTermMap));
	if (ret == NULL) return ret;
	sprintf(ret->prefix, "l%d_", id);
	return ret;
}

void free_LocalTermMap(LocalTermMap* x){
	if (x == NULL) return;
	free(x);
}

CLIPSValue generate_clipsvalue_from_typedliteral(Environment* env, const char* value, const char* type)
{
	char *value_enc,  *content;
	CLIPSValue ret;
	value_enc = percent_encode(value, strlen(value));
	if (
			type != NULL
			//|| ISURI(datatype, datatype_length, _RDF_string_)
			//|| ISURI(datatype, datatype_length, _XS_string_)
			)
	{
		content = malloc(strlen(value_enc) + strlen(type) + 3);
		sprintf(content, "%s^^%s", value_enc, type);
	} else {
		content = malloc(strlen(value_enc) + 1);
		sprintf(content, "%s", value_enc);
	}
	ret.lexemeValue = CreateString(env, content);
	free(content);
	free(value_enc);
	return ret;
}

CLIPSValue generate_clipsvalue_from_langliteral(Environment* env, const char* value, const char* lang){
	char *value_enc,  *content;
	CLIPSValue ret;
	value_enc = percent_encode(value, strlen(value));
	if (lang != NULL) {
		content = malloc(strlen(value_enc) + strlen(lang) + 3);
		sprintf(content, "%s@@%s", value_enc, lang);
	} else {
		content = malloc(strlen(value_enc) + 1);
		sprintf(content, "%s@@", value_enc);
	}
	ret.lexemeValue = CreateString(env, content);
	free(content);
	free(value_enc);
	return ret;
}



CLIPSValue generate_clipsvalue_from_termlist(Environment* env, LocalTermMap* cntxt, Multifield* items, CLIPSValue rest)
{
	return CLIPSValue_new_termlist(env, items, rest);
}

/**
 * Generate clips lexeme of the form "<http://example.com/myUri>" from iri.
 */
CLIPSValue generate_clipssymbol_from_iri(Environment* env, const char* iri)
{
	size_t l = strlen(iri);
	char* symb;
	CLIPSValue ret;
	symb = malloc(l + 3);
	symb[0]='<';
	memcpy(symb+1, iri, l);
	symb[l+1]='>';
	symb[l+2]='\0';
	ret.lexemeValue = CreateSymbol(env, symb);
	free(symb);
	return ret;
}


CLIPSValue generate_clipssymbol_from_local(Environment* env, LocalTermMap* cntxt, const char* name)
{
	char* content;
	fprintf(stderr, "brubru from_local\n");
	CLIPSValue ret;
	content = malloc(3 + strlen(cntxt->prefix) + strlen(name));
	sprintf(content, "_:%s%s", cntxt->prefix, name);
	ret.lexemeValue = CreateString(env, content);
	free(content);
	return ret;
}


static struct ret_ExtractAnyTerm string_to_literal(const char*);
static struct ret_ExtractAnyTerm string_to_iri(const char*);

struct ret_ExtractAnyTerm CLIPSValue_extract_any_term(CLIPSValue* val){
	struct ret_ExtractAnyTerm ret = {
		.value = NULL,
		.suffix = NULL,
	};

	switch(val->header->type){
                case STRING_TYPE:
			return string_to_literal(val->lexemeValue->contents);
                case SYMBOL_TYPE:
			return string_to_iri(val->lexemeValue->contents);
                case INTEGER_TYPE:
                case FLOAT_TYPE:
			break;
		case VOID_TYPE:
		case MULTIFIELD_TYPE:
		case FACT_ADDRESS_TYPE:
		default:
			break;
	}
	fprintf(stderr, "RIFITerm_from_CLIPSValue not fully implemented\n");
	return ret;
}

struct ret_ExtractList CLIPSValue_extract_list(Environment* env, CLIPSValue* val)
{
	switch(val->header->type){
		case MULTIFIELD_TYPE:
			return Multifield_extract_list(env, val->multifieldValue);
		case FACT_ADDRESS_TYPE:
			return Fact_extract_list(env, val->factValue);
	}
	return ret_fail_ExtractList(env);
}



static struct ret_ExtractList Fact_extract_list(Environment* env, Fact* fact){
	const char* template_name;
	Deftemplate* template;
	template = FactDeftemplate(fact);

	template_name = DeftemplateName(template);
	if (0 == strcmp(ATOMLISTTEMPLATE, template_name)){
		return AtomList_extract_list(env, fact);
	}
	return ret_fail_ExtractList(env);
}


static struct ret_ExtractList AtomList_extract_list(Environment* env, Fact* fact){
	CLIPSValue items_cv;
	struct ret_ExtractList ret = {
		.list = NULL,
	};
	ret.rest.voidValue = VoidConstant(env);

	GetFactSlot(fact, ATOMLISTSLOTITEMS, &items_cv);
	ret.list = items_cv.multifieldValue;
	return ret;
}


static struct ret_ExtractAnyTerm string_to_literal(const char* string){
	struct ret_ExtractAnyTerm ret = {
		.value = NULL,
		.suffix = NULL,
	};
	size_t suffix_length, value_length = 0;
	const char *lang = NULL, *type = NULL;
	for(const char* tmp=string; *tmp != '\0'; tmp++){
		if(*tmp == '@'){
			if(tmp[1] != '@'){
				fprintf(stderr, "broken literal\n");
				return ret;
			}
			lang = tmp+2;
			suffix_length = strlen(lang);
			break;
		} else if (*tmp == '^'){
			if(tmp[1] != '^'){
				fprintf(stderr, "broken literal\n");
				return ret;
			}
			type = tmp+2;
			suffix_length = strlen(type);
			break;
		}
		value_length++;
	}
	ret.value = percent_decode(string, value_length);
	if(lang != NULL){
		ret.type = LANGLITERAL;
		ret.suffix = malloc(suffix_length + 1);
		strcpy(ret.suffix, lang);
	} else if (type != NULL){
		ret.type = TYPEDLITERAL;
		ret.suffix = malloc(suffix_length + 1);
		strcpy(ret.suffix, type);
	} else {
		ret.type = TYPEDLITERAL;
		ret.suffix = NULL;
	}
	return ret;
}

static struct ret_ExtractAnyTerm string_to_iri(const char* string){
	struct ret_ExtractAnyTerm ret = {
		.type = URI,
		//.value = NULL,
		.suffix = NULL,
	};
	size_t l = strlen(string) - 2;
	ret.value = malloc(l + 1);
	memcpy(ret.value, string + 1, l);
	ret.value[l] = '\0';
	return ret;
}


static struct ret_ExtractList Multifield_extract_list(Environment* env, Multifield* x)
{
	struct ret_ExtractList ret = {
		.list = x,
	};
	ret.rest.voidValue = VoidConstant(env);
	return ret;
}

static struct ret_ExtractList ret_fail_ExtractList(Environment* env){
	struct ret_ExtractList ret = {
		.list = NULL,
	};
	ret.rest.voidValue = VoidConstant(env);
	return ret;
}
