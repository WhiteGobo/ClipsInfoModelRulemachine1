#include "literals.h"
#include "lexeme.h"
#include "datatype_to_internal_representation.h"
#include "struct_literal.h"
#include "ClipsInfoModelRulemachine1_number.h"
#include "namespace_XS.h"


Literal* Literal_from_CLIPSValue(Environment* env, CLIPSValue cv){
	Number number;
	switch(cv.header->type){
		case STRING_TYPE:
			return Literal_from_CLIPSString(env, cv.lexemeValue);
		case SYMBOL_TYPE:
			return Literal_from_CLIPSSymbol(env, cv.lexemeValue);
		case INTEGER_TYPE:
			return Literal_from_int(env, cv.integerValue->contents);
		case FLOAT_TYPE:
			return Literal_from_float(env, cv.floatValue->contents);
		case FACT_ADDRESS_TYPE: //no facts that equal literals
		case VOID_TYPE:
			return NULL;
		default:
			WriteString(env, STDERR, "ERROR Literal_from_CLIPSValue not implemented for ");
			WriteCLIPSValue(env, STDERR, &cv);
			WriteString(env, STDERR, "\n");
			return NULL;
	}
}

CLIPSValue Literal_to_CLIPSValue_plain(Environment* env, const Literal* x){
	CLIPSValue ret;
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Func_CLIPSValueFromLiteralValue* gen;
	if(x == NULL){
		return void_value;
	}

	switch(x->type){
		case URI:
			return CLIPSValue_from_iri(env, x->value);
		case LANGLITERAL:
			return CLIPSValue_from_langliteral(env, x->value, x->suffix);
		case TYPEDLITERAL:
			gen = CLIPSValue_from_any;
			return gen(env, x->value, x->suffix);
		case BNODE:
			if (x->env != env){
				WriteString(env, STDERR, "ERROR Literal_to_CLIPSValue ");
				WriteLiteral(env, STDERR, x);
				WriteString(env, STDERR, "\n");
				return void_value;
			}
			ret.lexemeValue = x->lexeme;
			return ret;
	}
	fprintf(stderr, "Literal_to_CLIPSValue not implemented\n");
	return void_value;
}

CLIPSValue Literal_to_CLIPSValue(Environment* env, const Literal* x){
	CLIPSValue ret;
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	Func_CLIPSValueFromLiteralValue* gen;
	if(x == NULL){
		return void_value;
	}

	switch(x->type){
		case URI:
			return CLIPSValue_from_iri(env, x->value);
		case LANGLITERAL:
			return CLIPSValue_from_langliteral(env, x->value, x->suffix);
		case TYPEDLITERAL:
			gen =get_literal_generator_from_datatype(env, x->suffix);
			return gen(env, x->value, x->suffix);
		case BNODE:
			if (x->env != env){
				WriteString(env, STDERR, "ERROR Literal_to_CLIPSValue ");
				WriteLiteral(env, STDERR, x);
				WriteString(env, STDERR, "\n");
				return void_value;
			}
			ret.lexemeValue = x->lexeme;
			return ret;
	}
	fprintf(stderr, "Literal_to_CLIPSValue not implemented\n");
	return void_value;
}


bool Literal_equal(const Literal* x, const Literal* y){
	//TODO datatype NULL is equal to string i think
	if (x == NULL) return false;
	if (y == NULL) return false;
	if (x->value == NULL) return false;
	if (y->value == NULL) return false;
	if (x->type != y->type) return false;
	if (0 != strcmp(x->value, y->value)){
		return false;
	}
	if (x->suffix == NULL){
		return y->suffix == NULL;
	} else {
		if (y->suffix == NULL){
			return false;
		}
		return 0 == strcmp(x->suffix, y->suffix);
	}
}

Literal* Literal_new_langliteral(const char* value, const char* lang){
	Literal* ret;
	if (value == NULL) return NULL;
	ret = malloc(sizeof(Literal));
	if (ret == NULL) return NULL;
	ret->value = malloc(strlen(value) + 1);
	strcpy(ret->value, value);
	if (lang == NULL){
		ret->suffix = NULL;
	} else {
		ret->suffix = malloc(strlen(lang) + 1);
		strcpy(ret->suffix, lang);
	}
	ret->type = LANGLITERAL;
	return ret;
}

Literal* Literal_new(const char* value, const char* datatype){
	Literal* ret;
	if (value == NULL) return NULL;
	ret = malloc(sizeof(Literal));
	if (ret == NULL) return NULL;
	ret->value = malloc(strlen(value) + 1);
	strcpy(ret->value, value);
	if (datatype == NULL){
		ret->suffix = NULL;
	} else {
		ret->suffix = malloc(strlen(datatype) + 1);
		strcpy(ret->suffix, datatype);
	}
	ret->type = TYPEDLITERAL;
	return ret;
}




Literal* Literal_cast(const Literal* orig, const char* datatype){
	if (orig == NULL) return NULL;
	return Literal_new(orig->value, datatype);
}


bool Literal_check_datatype(const Literal* x, const char* datatype){
	if (x == NULL) return false;
	if (datatype == NULL) return false;
	return 0 == strcmp(x->suffix, datatype);
}


void free_Literal(Literal* x){
	if(x == NULL) return;
	switch(x->type){
		case URI:
		case TYPEDLITERAL:
		case LANGLITERAL:
			free(x->value);
			free(x->suffix);
			break;
		case BNODE:
			ReleaseLexeme(x->env, x->lexeme);
			break;
	}
	free(x);
}

const char* Literal_get_value(Literal* x){
	if (x == NULL) return NULL;
	switch(x->type){
		case URI:
		case TYPEDLITERAL:
		case LANGLITERAL:
			return x->value;
		case BNODE:
			return x->lexeme->contents + 2;
	}
}

const char* Literal_get_datatype(Literal* x){
	if (x == NULL) return NULL;
	if (x->type == TYPEDLITERAL){
		return x->suffix;
	} else {
		return NULL;
	} 
}

const char* Literal_get_lang(Literal* x){
	if (x == NULL) return NULL;
	if (x->type == LANGLITERAL){
		return x->suffix;
	} else {
		return NULL;
	} 
}

TERMTYPE Literal_get_type(Literal* x){
	if (x == NULL) return URI;
	return x->type;
}

void WriteLiteral(Environment* env, const char* logicalName, const Literal* x){
	char *tmp;
	if (x == NULL){
		WriteString(env, logicalName, "(NULL)");
		return;
	}
	switch(x->type){
		case URI:
			tmp = malloc(strlen(x->value) + 5);
			sprintf(tmp, "<%s>", x->value);
			break;
		case LANGLITERAL:
			tmp = malloc(strlen(x->value) + strlen(x->suffix) + 8);
			sprintf(tmp, "\"%s\"@%s", x->value, x->suffix);
			break;
		case TYPEDLITERAL:
			tmp = malloc(strlen(x->value) + strlen(x->suffix) + 8);
			sprintf(tmp, "\"%s\"^^%s", x->value, x->suffix);
			break;
		case BNODE:
			tmp = malloc(strlen(x->lexeme->contents) + 4);
			sprintf(tmp, "%s", x->lexeme->contents);
			break;
		default:
			tmp = malloc(20);
			sprintf(tmp, "(unknown)");
			break;
	}
	WriteString(env, logicalName, tmp);
	free(tmp);
}

void fprintf_Literal(FILE* f, const Literal* x){
	if (x == NULL){
		fprintf(f, "(NULL)");
		return;
	}
	switch(x->type){
		case URI:
			fprintf(f, "<%s>", x->value);
			break;
		case LANGLITERAL:
			fprintf(f, "\"%s\"@%s", x->value, x->suffix);
			break;
		case TYPEDLITERAL:
			fprintf(f, "\"%s\"^^%s", x->value, x->suffix);
			break;
		case BNODE:
			fprintf(f, "%s", x->lexeme->contents);
			break;
	}
}


Literal* Literal_from_int(Environment*, int64_t x){
	char tmp[100];
	sprintf(tmp, "%d", x);
	return Literal_new(tmp, _XS_integer_);
}

Literal* Literal_from_float(Environment*, double x){
	char tmp[100];
	sprintf(tmp, "%f", x);
	return Literal_new(tmp, _XS_double_);
}
