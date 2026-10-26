#include "udfdescription.h"
#include "literals.h"
#include "helper.h"

#include "namespace_XS.h"
#include "namespace_FUNC.h"
#include "namespace_PRED.h"
#include "namespace_ACT.h"

#include "ClipsInfoModelRulemachine1_string.h"
#include "ClipsInfoModelRulemachine1_number.h"

const UDFDescription builtinFunctionList_String[];

static void compare(Environment *env, UDFContext *udfc, UDFValue *out);
static void concat(Environment *env, UDFContext *udfc, UDFValue *out);
static void string_join(Environment *env, UDFContext *udfc, UDFValue *out);
static void substring(Environment *env, UDFContext *udfc, UDFValue *out);
static void string_length(Environment *env, UDFContext *udfc, UDFValue *out);
static void upper_case(Environment *env, UDFContext *udfc, UDFValue *out);
static void lower_case(Environment *env, UDFContext *udfc, UDFValue *out);
static void encode_for_uri(Environment *env, UDFContext *udfc, UDFValue *out);
static void iri_to_uri(Environment *env, UDFContext *udfc, UDFValue *out);
static void escape_html_uri(Environment *env, UDFContext *udfc, UDFValue *out);
static void substring_before(Environment *env, UDFContext *udfc, UDFValue *out);
static void substring_after(Environment *env, UDFContext *udfc, UDFValue *out);
static void replace(Environment *env, UDFContext *udfc, UDFValue *out);
static void contains(Environment *env, UDFContext *udfc, UDFValue *out);
static void starts_with(Environment *env, UDFContext *udfc, UDFValue *out);
static void ends_with(Environment *env, UDFContext *udfc, UDFValue *out);
static void matches(Environment *env, UDFContext *udfc, UDFValue *out);
static void myprint(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_String[] = {
	{"<"_FUNC_compare_">", "*", 2, 2, "*",
		compare, "compare"},
	{"<"_FUNC_concat_">", "*", 2, UNBOUNDED, "*",
		concat, "concat"},
	{"<"_FUNC_string_join_">", "*", 3, 3, "*",
		string_join, "string_join"},
	{"<"_FUNC_substring_">", "*", 2, 3, "*",
		substring, "substring"},
	{"<"_FUNC_string_length_">", "*", 1, 1, "*",
		string_length, "string_length"},
	{"<"_FUNC_upper_case_">", "*", 1, 1, "*",
		upper_case, "upper_case"},
	{"<"_FUNC_lower_case_">", "*", 1, 1, "*",
		lower_case, "lower_case"},
	{"<"_FUNC_encode_for_uri_">", "*", 1, 1, "*",
		encode_for_uri, "encode_for_uri"},
	{"<"_FUNC_iri_to_uri_">", "*", 1, 1, "*",
		iri_to_uri, "iri_to_uri"},
	{"<"_FUNC_escape_html_uri_">", "*", 1, 1, "*",
		escape_html_uri, "escape_html_uri"},
	{"<"_FUNC_substring_before_">", "*", 2, 2, "*",
		substring_before, "substring_before"},
	{"<"_FUNC_substring_after_">", "*", 2, 2, "*",
		substring_after, "substring_after"},
	{"<"_FUNC_replace_">", "*", 3, 3, "*",
		replace, "replace"},
	{"<"_PRED_contains_">", "b", 2, 2, "*",
		contains, "contains"},
	{"<"_PRED_starts_with_">", "b", 2, 2, "*",
		starts_with, "starts_with"},
	{"<"_PRED_ends_with_">", "b", 2, 2, "*",
		ends_with, "ends_with"},
	{"<"_PRED_matches_">", "b", 2, 2, "*",
		matches, "matches"},
	{"<"_ACT_print_">", "b", 1, 1, "*",
		myprint, "myprint"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};

static void compare(Environment *env, UDFContext *udfc, UDFValue *out){
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

static void concat(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue tmpcv;
	size_t argcount;
	Literal *ret;
	Literal** literals;
	const char** values;
	char* result, *tmpx;
	size_t result_size = 0;
	size_t tmpl;
	argcount = UDFArgumentCount(udfc);
	literals = malloc(sizeof(Literal*) * argcount);
	values = malloc(sizeof(const char*) * argcount);
	if (literals == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
		UDFThrowError(udfc);
		return;
	}
	for(size_t i = 0; i < argcount; i++){
		literals[i] = UDF_get_nth_as_literal(udfc, i+1);
		values[i] = Literal_get_value(literals[i]);
		if(values[i] == NULL){
			fprintf(stderr, "func:concat: Failed to get "
					"string value\n");
			UDFThrowError(udfc);
			return;
		}
		result_size += strlen(values[i]);
	}
	result = malloc(result_size + 1);
	tmpx = result;
	for(size_t i = 0; i < argcount; i++){
		tmpl = strlen(values[i]);
		memcpy(tmpx, values[i], tmpl);
		tmpx += tmpl;
		free_Literal(literals[i]);
	}
	result[result_size] = '\0';
	ret = Literal_new(result, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret);
	out->value = tmpcv.value;
	free(result);
	free_Literal(ret);
}

static void string_join(Environment *env, UDFContext *udfc, UDFValue *out){
	CLIPSValue tmpcv;
	size_t partcount, connector_length;
	Literal *connector, *ret;
	Literal** literals;
	const char** values;
	const char* connector_value;
	char* result, *tmpx;
	size_t result_size = 0;
	size_t tmpl;
	partcount = UDFArgumentCount(udfc) - 1;
	literals = malloc(sizeof(Literal*) * partcount);
	values = malloc(sizeof(const char*) * partcount);
	if (literals == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
		UDFThrowError(udfc);
		return;
	}
	connector = UDF_get_nth_as_literal(udfc, partcount+1);
	connector_value = Literal_get_value(connector);
	if (connector_value == NULL){
		fprintf(stderr, "func:string-join failed(connector value)\n");
		UDFThrowError(udfc);
		return;
	}
	connector_length = strlen(connector_value);
	for(size_t i = 0; i < partcount; i++){
		literals[i] = UDF_get_nth_as_literal(udfc, i+1);
		values[i] = Literal_get_value(literals[i]);
		if(values[i] == NULL){
			fprintf(stderr, "func:concat: Failed to get "
					"string value\n");
			UDFThrowError(udfc);
			return;
		}
		result_size += strlen(values[i]) + connector_length;
	}

	result = malloc(result_size + 1);
	tmpl = strlen(values[0]);
	memcpy(result, values[0], tmpl);
	tmpx = result + tmpl;
	for(size_t i = 1; i < partcount; i++){
		memcpy(tmpx, connector_value, connector_length);
		tmpx += connector_length;
		tmpl = strlen(values[i]);
		memcpy(tmpx, values[i], tmpl);
		tmpx += tmpl;
		free_Literal(literals[i]);
	}
	*tmpx = '\0';
	ret = Literal_new(result, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret);
	out->value = tmpcv.value;
	free(result);
	free_Literal(ret);
	free_Literal(connector);
}


static void substring(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	int start, end;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	size_t argcount = UDFArgumentCount(udfc);
	RetGetNthAsInt retgetnthasint;

	Literal *input_lit;
	const char *input;

	out->voidValue = VoidConstant(env);
	input_lit = UDF_get_nth_as_literal(udfc, 1);
	input = Literal_get_value(input_lit);
	if (input == NULL){
		fprintf(stderr, "func:substring: input\n");
		UDFThrowError(udfc);
		return;
	}

	retgetnthasint = UDF_get_nth_as_int(env, udfc, 2);
	if(retgetnthasint.err != 0){
		fprintf(stderr, "func:substring: Failed(index)\n");
		UDFThrowError(udfc);
		return;
	}
	start = retgetnthasint.value;
	fprintf(stderr, "\nsubstring start %d\n", start);
	if (argcount >= 3){
		retgetnthasint = UDF_get_nth_as_int(env, udfc, 3);
		if(retgetnthasint.err != 0){
			fprintf(stderr, "func:substring: Failed(index)\n");
			UDFThrowError(udfc);
			return;
		}
		end = retgetnthasint.value;
		ret = CIMR1_string_substring(input, start, end);
	} else {
		ret = CIMR1_string_string_cut(input, start);
	}

	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;
	free(ret);
	free_Literal(input_lit);
	free_Literal(ret_lit);
}


static void string_length(Environment *env, UDFContext *udfc, UDFValue *out){
	int ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit;
	const char *first;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	if (first == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	out->integerValue = CreateInteger(env, strlen(first));
	free_Literal(first_lit);
}


static void upper_case(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit;
	const char *first;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	if (first == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_uppercase(first);
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(ret_lit);
	free_Literal(first_lit);
}


static void lower_case(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit;
	const char *first;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	if (first == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_lowercase(first);
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(first_lit);
	free_Literal(ret_lit);
}


static void encode_for_uri(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit;
	const char *first;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	if (first == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_encode_for_uri(first, strlen(first));
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(first_lit);
	free_Literal(ret_lit);
}


static void iri_to_uri(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit;
	const char *first;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	if (first == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_iri_to_uri(first, strlen(first));
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(first_lit);
	free_Literal(ret_lit);
}


static void escape_html_uri(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit;
	const char *first;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	if (first == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_escape_html_uri(first, strlen(first));
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(first_lit);
	free_Literal(ret_lit);
}


static void substring_before(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
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
	ret = CIMR1_string_substring_before(first, second);
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(first_lit);
	free_Literal(second_lit);
	free_Literal(ret_lit);
}


static void substring_after(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
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

	ret = CIMR1_string_substring_after(first, second);
	Literal* ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free_Literal(first_lit);
	free_Literal(second_lit);
	free_Literal(ret_lit);
}


static void replace(Environment *env, UDFContext *udfc, UDFValue *out){
	char* ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit, *query_lit, *target_lit, *ret_lit, *flags_lit;
	const char *first, *query, *target, *flags;
	size_t argcount = UDFArgumentCount(udfc);
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	query_lit = UDF_get_nth_as_literal(udfc, 2);
	query = Literal_get_value(query_lit);
	target_lit = UDF_get_nth_as_literal(udfc, 3);
	target = Literal_get_value(target_lit);
	if (first == NULL || query == NULL || target == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	if (argcount >= 4){
		flags_lit = UDF_get_nth_as_literal(udfc, 4);
		flags = Literal_get_value(target_lit);
	} else {
		flags = NULL;
	}

	ret = CIMR1_string_replace(first, query, target, flags);
	ret_lit = Literal_new(ret, NULL);
	tmpcv = Literal_to_CLIPSValue(env, ret_lit);
	out->value = tmpcv.value;

	free(ret);
	free_Literal(first_lit);
	free_Literal(query_lit);
	free_Literal(target_lit);
	free_Literal(ret_lit);
}


static void contains(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
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
	ret = CIMR1_string_contains(first, second);
	out->lexemeValue = CreateBoolean(env, ret);

	free_Literal(first_lit);
	free_Literal(second_lit);
}


static void starts_with(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit, *second_lit;
	const char *first, *query;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	second_lit = UDF_get_nth_as_literal(udfc, 2);
	query = Literal_get_value(second_lit);
	if (first == NULL || query == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_starts_with(first, query);
	out->lexemeValue = CreateBoolean(env, ret);

	free_Literal(first_lit);
	free_Literal(second_lit);
}


static void ends_with(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	Literal *first_lit, *second_lit;
	const char *first, *query;
	out->voidValue = VoidConstant(env);
	first_lit = UDF_get_nth_as_literal(udfc, 1);
	first = Literal_get_value(first_lit);
	second_lit = UDF_get_nth_as_literal(udfc, 2);
	query = Literal_get_value(second_lit);
	if (first == NULL || query == NULL){
		fprintf(stderr, "PlainLiteral_from_string_lang failed(value)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = CIMR1_string_ends_with(first, query);
	out->lexemeValue = CreateBoolean(env, ret);

	free_Literal(first_lit);
	free_Literal(second_lit);
}


static void matches(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
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
	ret = CIMR1_string_matches(first, second);
	out->lexemeValue = CreateBoolean(env, ret);

	free_Literal(first_lit);
	free_Literal(second_lit);
}

static void myprint(Environment *env, UDFContext *udfc, UDFValue *out){
	const size_t argcount = UDFArgumentCount(udfc);
	Literal* tmplit;
	const char* tmpstr;
	bool ret = true;
	out->lexemeValue = CreateBoolean(env, ret);
	for(size_t i= 0; i<argcount; i++){
		tmplit = UDF_get_nth_as_literal(udfc, i+1);
		tmpstr = Literal_get_value(tmplit);
		//STDOUT is defined in clips.h and is the symbol stdout
		if(tmpstr != NULL){
			WriteString(env, STDOUT, tmpstr);
		} else {
			WriteString(env, STDOUT, "(not a literal)");
		}
	}
}
