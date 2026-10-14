#include "literals.h"
#include "lexeme.h"
#include "ClipsInfoModelRulemachine1_string.h"

#include "struct_literal.h"
#include "namespace_XS.h"

static Literal* Literal_new_uri(const char* x, size_t l);
static Literal* Literal_new_bnode(Environment*, CLIPSLexeme*);
static Literal* Literal_new_typedliteral(char* value, const char* type);

Literal* Literal_from_CLIPSString(Environment* env, CLIPSLexeme* x){
	if (x == NULL) return NULL;
	Literal* ret;
	char *ret_value;
	const char *value, *lang=NULL, *type=NULL;
	size_t suffix_length, value_length;
	value_length = 0;
	for(const char* tmp=x->contents; *tmp != '\0'; tmp++){
		if(*tmp == '@'){
			if(tmp[1] != '@'){
				fprintf(stderr, "ERROR broken literal\n");
				return NULL;
			}
			lang = tmp+2;
			suffix_length = strlen(lang);
			break;
		} else if (*tmp == '^'){
			if(tmp[1] != '^'){
				fprintf(stderr, "ERROR broken literal\n");
				return NULL;
			}
			type = tmp+2;
			suffix_length = strlen(type);
			break;
		}
		value_length++;
	}
	ret_value = CIMR1_percent_decode(x->contents, value_length);
	if (ret_value == NULL){
		return NULL;
	}

	if(lang != NULL){
		ret = Literal_new_langliteral(ret_value, lang);
	} else {
		ret = Literal_new(ret_value, type);
	}
	free(ret_value);
	return ret;
}

Literal* Literal_from_CLIPSSymbol(Environment* env, CLIPSLexeme* x){
	if(x == NULL) return NULL;
	size_t len;
	Literal* ret;

	len = strlen(x->contents);
	if(len < 2){
		return NULL;
	}
	if(x->contents[0] == '<' && x->contents[len-1] == '>'){
		return Literal_new_uri(x->contents + 1, len-2);
	}
	if(x->contents[0] == '_' && x->contents[1] == ':'){
		return Literal_new_bnode(env, x);
	}
	fprintf(stderr, "ERROR Literal_from_CLIPSSymbol: CV not a Literal\n");
	return NULL;
}


static Literal* Literal_new_uri(const char* x, size_t l){
	Literal* ret;
	ret = malloc(sizeof(Literal));
	if (ret == NULL){
		fprintf(stderr, "CRITICAL ERROR: malloc failed\n");
		return NULL;
	}
	ret->type = URI;
	ret->suffix = NULL;
	ret->value = malloc(l +1);
	if (ret->value == NULL){
		fprintf(stderr, "CRITICAL ERROR: malloc failed\n");
		return NULL;
	}
	memcpy(ret->value, x, l);
	ret->value[l] = '\0';
	return ret;
}

static Literal* Literal_new_bnode(Environment* env, CLIPSLexeme* x){
	Literal* ret;
	ret = malloc(sizeof(Literal));
	if (ret == NULL){
		fprintf(stderr, "CRITICAL ERROR: malloc failed\n");
		return NULL;
	}
	ret->type = BNODE;
	ret->env = env;
	ret->lexeme = x;
	RetainLexeme(env, x);
	return ret;
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
