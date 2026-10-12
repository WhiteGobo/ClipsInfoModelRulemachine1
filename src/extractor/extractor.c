#include "extractor.h"
#include <clips.h>
#include "terms.h"

#include <RIFImporterDebug.h>
#include "shared_information.h"

//static RIFITerm* Literal_from_single_string(const char*);
static char *extract_iri_from_symbol(CLIPSLexeme* lexeme);


RIFITermList* RIFITermList_from_CLIPSMultifield(Environment* env, Multifield *multifield){
	RIFITermList* ret = NULL;
	RIFITerm* tmp_term;
	for (int i = 0; i < multifield->length; i++){
		tmp_term = RIFITerm_from_CLIPSValue(env, multifield->contents + i);
		ret = RIFITermList_append(ret, tmp_term);
	}
	return ret;
}

static RIFITermType RDFType_to_RIFITermType(TERMTYPE x){
	switch(x){
		case URI:
			return RIF_IRI;
		case BNODE:
			return RIF_Local;
		case TYPEDLITERAL:
			return RIF_TypedLiteral;
		case LANGLITERAL:
			return RIF_LangLiteral;
	}
}


RIFITerm* RIFITerm_from_CLIPSValue(Environment* env, CLIPSValue* val){
	RIFITerm* ret;
	RIFITermList* retlist;
	
	struct ret_ExtractAnyTerm any_term = CLIPSValue_extract_any_term(val);
	if(EXTRACT_ANY_TERM_SUCCESS(any_term)){
		ret = malloc(sizeof(RIFITerm));
		ret->type = RDFType_to_RIFITermType(any_term.type);
		ret->value = any_term.value;
		ret->suffix = any_term.suffix;
		return ret;
	}
	struct ret_ExtractList extracted_list = CLIPSValue_extract_list(env, val);
	if(EXTRACT_LIST_SUCCESS(extracted_list)){
		retlist = RIFITermList_from_CLIPSMultifield(env, extracted_list.list);
		ret = malloc(sizeof(RIFITerm));
		ret->type = RIF_List;
		ret->list = retlist;
		ret->rest = NULL;
		return ret;
	}
	return NULL;

	/*

	switch(val->header->type){
                case STRING_TYPE:
			return Literal_from_single_string(
						val->lexemeValue->contents);
                case SYMBOL_TYPE:
			ret = malloc(sizeof(RIFITerm));
			ret->type = RIF_IRI;
			ret->value = extract_iri_from_symbol(val->lexemeValue);
			ret->suffix = NULL;
			return ret;
		case MULTIFIELD_TYPE:
			ret = malloc(sizeof(RIFITerm));
			ret->type = RIF_List;
			ret->list = RIFITermList_from_CLIPSMultifield(env,
						val->multifieldValue);
			ret->rest = NULL;
			return ret;
		case FACT_ADDRESS_TYPE:
			return CIMR1_Fact_to_RIFITerm(env, val->factValue);
                case INTEGER_TYPE:
                case FLOAT_TYPE:
		case VOID_TYPE:
			break;
	}
	fprintf(stderr, "RIFITerm_from_CLIPSValue not fully implemented\n");
	return NULL;
	*/
}


/*
static RIFITerm* Literal_from_single_string(const char* string){
	size_t suffix_length, value_length = 0;
	const char *lang = NULL, *type = NULL;
	char *value, *suffix;
	for(const char* tmp=string; *tmp != '\0'; tmp++){
		if(*tmp == '@'){
			if(tmp[1] != '@'){
				fprintf(stderr, "broken literal\n");
				return NULL;
			}
			lang = tmp+2;
			suffix_length = strlen(lang);
			break;
		} else if (*tmp == '^'){
			if(tmp[1] != '^'){
				fprintf(stderr, "broken literal\n");
				return NULL;
			}
			type = tmp+2;
			suffix_length = strlen(type);
			break;
		}
		value_length++;
	}
	RIFITerm* ret = malloc(sizeof(RIFITerm));
	ret->value = percent_decode(string, value_length);
	if(lang != NULL){
		ret->type = RIF_LangLiteral;
		ret->suffix = malloc(suffix_length + 1);
		strcpy(ret->suffix, lang);
	} else if (type != NULL){
		ret->type = RIF_TypedLiteral;
		ret->suffix = malloc(suffix_length + 1);
		strcpy(ret->suffix, type);
	} else {
		ret->type = RIF_TypedLiteral;
		ret->suffix = NULL;
	}
	return ret;
}
*/


/**
 * extract uri from clips symbol of the form "<http://example.com/myUri>".
 */
/*
static char *extract_iri_from_symbol(CLIPSLexeme* lexeme){
	char *ret = NULL;
	size_t orig_l = strlen(lexeme->contents);
	size_t l = orig_l - 2;
	ret = malloc(l + 1);
	memcpy(ret, lexeme->contents + 1, l);
	ret[l] = '\0';
	return ret;
}
*/
