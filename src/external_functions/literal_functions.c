#include "udfdescription.h"
#include "helper.h"

#include "namespace_XS.h"
#include "namespace_FUNC.h"
#include "namespace_PRED.h"
#include <bcd47LanguageTagsC.h>

const UDFDescription builtinFunctionList_Literal[];

static bool check_lang_range(const char* lang, const char* range);


static void generate_string_lang(Environment *env, UDFContext *udfc, UDFValue *out);
static void generate_literal(Environment *env, UDFContext *udfc, UDFValue *out);
static void PlainLiteral_from_string_lang(Environment *env, UDFContext *udfc, UDFValue *out);
static void string_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out);
static void lang_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out);
static void PlainLiteral_compare(Environment *env, UDFContext *udfc, UDFValue *out);
static void matches_language_range(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_Literal[] = {
	{"gen-string-lang", "*", 1, 2, "s",
		generate_string_lang, "generate_string_lang"},
	{"gen-literal", "*", 1, 2, "s",
		generate_literal, "generate_literal"},
	{"<"_FUNC_PlainLiteral_from_string_lang_">", "*", 1, 2, "*",
		PlainLiteral_from_string_lang, "PlainLiteral_from_string_lang"},
	{"<"_FUNC_string_from_PlainLiteral_">", "*", 1, 1, "*",
		string_from_PlainLiteral, "string_from_PlainLiteral"},
	{"<"_FUNC_lang_from_PlainLiteral_">", "*", 1, 1, "*",
		lang_from_PlainLiteral, "lang_from_PlainLiteral"},
	{"<"_FUNC_PlainLiteral_compare_">", "*", 2, 2, "*",
		PlainLiteral_compare, "PlainLiteral_compare"},
	{"<"_PRED_matches_language_range_">", "*", 2, 2, "*",
		matches_language_range, "matches_language_range"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


static void generate_string_lang(Environment *env, UDFContext *udfc, UDFValue *out)
{
	UDFValue tmpudf;
	CLIPSValue tmpclips;
	CLIPSLexeme *first, *second;
	const char *value, *lang;
	Literal *ret;
	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, LEXEME_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	first = tmpudf.lexemeValue;
	value = first->contents;
	if(1 < UDFArgumentCount(udfc)){
		if (!UDFNextArgument(udfc, LEXEME_BITS, &tmpudf)){
			fprintf(stderr, "brubru err1\n");
			UDFThrowError(udfc);
			return;
		}
		second = tmpudf.lexemeValue;
		lang = second->contents;
	} else {
		lang = NULL;
	}
	ret = Literal_new_langliteral(value, lang);
	if (ret != NULL){
		tmpclips = Literal_to_CLIPSValue(env, ret);
		out->value = tmpclips.value;
		free_Literal(ret);
	} else {
		UDFThrowError(udfc);
	}
}


static void generate_literal(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue tmpclips;
	CLIPSLexeme *first, *second;
	const char *value, *datatype;
	Literal *ret;
	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	first = tmpudf.lexemeValue;
	value = first->contents;
	if(1 < UDFArgumentCount(udfc)){
		if (!UDFNextArgument(udfc, LEXEME_BITS, &tmpudf)){
			fprintf(stderr, "brubru err1\n");
			UDFThrowError(udfc);
			return;
		}
		second = tmpudf.lexemeValue;
		datatype = second->contents;
	} else {
		datatype = NULL;
	}
	ret = Literal_new(value, datatype);
	if (ret != NULL){
		tmpclips = Literal_to_CLIPSValue(env, ret);
		out->value = tmpclips.value;
		free_Literal(ret);
	} else {
		UDFThrowError(udfc);
	}
}


static void PlainLiteral_from_string_lang(Environment *env, UDFContext *udfc, UDFValue *out)
{
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	CLIPSLexeme *first, *second;
	Literal *value_lit, *lang_lit;
	const char *value, *lang;
	Literal *ret;
	out->voidValue = VoidConstant(env);
	value_lit = UDF_get_nth_as_literal(udfc, 1);
	value = Literal_get_value(value_lit);
	if (value == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	if(1 < UDFArgumentCount(udfc)){
		lang_lit = UDF_get_nth_as_literal(udfc, 2);
		lang = Literal_get_value(lang_lit);
		if (lang == NULL){
			fprintf(stderr, "PlainLiteral_from_string_lang failed"
					"(lang)\n");
			UDFThrowError(udfc);
			return;
		}
	} else {
		lang_lit = NULL;
		lang = NULL;
	}
	ret = Literal_new_langliteral(value, lang);
	free_Literal(value_lit);
	free_Literal(lang_lit);
	if (ret != NULL){
		tmpcv = Literal_to_CLIPSValue(env, ret);
		out->value = tmpcv.value;
		free_Literal(ret);
	} else {
		fprintf(stderr, "PlainLiteral_from_string_lang failed"
				"(return)\n");
		UDFThrowError(udfc);
	}
}


static void string_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out)
{
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	CLIPSLexeme *first, *second;
	Literal *value_lit, *lang_lit;
	const char *value, *lang;
	Literal *ret;
	out->voidValue = VoidConstant(env);
	value_lit = UDF_get_nth_as_literal(udfc, 1);
	value = Literal_get_value(value_lit);
	if (value == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = Literal_new(value, NULL);
	free_Literal(value_lit);
	if (ret != NULL){
		tmpcv = Literal_to_CLIPSValue(env, ret);
		out->value = tmpcv.value;
		free_Literal(ret);
	} else {
		fprintf(stderr, "PlainLiteral_from_string_lang failed"
				"(return)\n");
		UDFThrowError(udfc);
	}
}


static void lang_from_PlainLiteral(Environment *env, UDFContext *udfc, UDFValue *out)
{
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	CLIPSLexeme *first, *second;
	Literal *value_lit, *lang_lit;
	const char *value, *lang;
	Literal *ret;
	out->voidValue = VoidConstant(env);
	value_lit = UDF_get_nth_as_literal(udfc, 1);
	value = Literal_get_lang(value_lit);
	if (value == NULL){
		ret = Literal_new("", NULL);
	} else {
		ret = Literal_new(value, _XS_lang_);
	}
	free_Literal(value_lit);
	if (ret != NULL){
		tmpcv = Literal_to_CLIPSValue(env, ret);
		out->value = tmpcv.value;
		free_Literal(ret);
	} else {
		fprintf(stderr, "PlainLiteral_from_string_lang failed"
				"(return)\n");
		UDFThrowError(udfc);
	}
}


static void PlainLiteral_compare(Environment *env, UDFContext *udfc, UDFValue *out)
{
	int ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit, *second_lit;
	const char *first, *second;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	second_lit = UDF_get_nth_as_literal(udfc, 2);
	second = Literal_get_value(second_lit);
	if (first == NULL || second == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = strcmp(first, second);
	free_Literal(first_lit);
	free_Literal(second_lit);
	if (ret == 0){
		out->integerValue = CreateInteger(env, 0);
	} else if (ret < 0){
		out->integerValue = CreateInteger(env, -1);
	} else {
		out->integerValue = CreateInteger(env, 1);
	}
}


static void matches_language_range(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit, *range_lit;
	const char *lang, *range;

	out->lexemeValue = CreateBoolean(env, false);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	lang = Literal_get_lang(first_lit);
	if (lang == NULL){
		free_Literal(first_lit);
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	range_lit = UDF_get_nth_as_literal(udfc, 2);
	range = Literal_get_value(range_lit);
	if (range == NULL){
		free_Literal(first_lit);
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = extended_match_language_tag(range, lang);
	free_Literal(first_lit);
	free_Literal(range_lit);
	out->lexemeValue = CreateBoolean(env, ret);
}
