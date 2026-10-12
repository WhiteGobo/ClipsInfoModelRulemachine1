#include "udfdescription.h"
#include "literals.h"

#include "namespace_XS.h"
#include "namespace_FUNC.h"
#include "namespace_PRED.h"

const UDFDescription builtinFunctionList_Boolean[];

static void not(Environment *env, UDFContext *udfc, UDFValue *out);
static void equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void less(Environment *env, UDFContext *udfc, UDFValue *out);
static void greater(Environment *env, UDFContext *udfc, UDFValue *out);


const UDFDescription builtinFunctionList_Boolean[] = {
	{"<"_FUNC_not_">", "*", 1, 1, "*",
		not, "not"},
	{"<"_PRED_boolean_equal_">", "*", 2, 2, "*",
		equal, "equal"},
	{"<"_PRED_boolean_less_than_">", "*", 2, 2, "*",
		less, "less"},
	{"<"_PRED_boolean_greater_than_">", "*", 2, 2, "*",
		greater, "greater"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};

static void not(Environment *env, UDFContext *udfc, UDFValue *out){
	struct s_RetExtractTruth first;
	first = extract_truth(env, udfc, 1);
	if (first.err != 0){
		out->voidValue = VoidConstant(env);
		fprintf(stderr, "func:not failed(input)\n");
		UDFThrowError(udfc);
	} else {
		out->lexemeValue = CreateBoolean(env, !first.value);
	}
}


static void equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	struct s_RetExtractTruth first, second;
	first = extract_truth(env, udfc, 1);
	second = extract_truth(env, udfc, 2);
	if (first.err != 0 || second.err != 0){
		out->voidValue = VoidConstant(env);
		fprintf(stderr, "func:equal failed(input)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = first.value == second.value;
	out->lexemeValue = CreateBoolean(env, ret);
}


static void less(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	struct s_RetExtractTruth first, second;
	first = extract_truth(env, udfc, 1);
	second = extract_truth(env, udfc, 2);
	if (first.err != 0 || second.err != 0){
		out->voidValue = VoidConstant(env);
		fprintf(stderr, "func:equal failed(input)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = !first.value && second.value;
	out->lexemeValue = CreateBoolean(env, ret);
}


static void greater(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	struct s_RetExtractTruth first, second;
	first = extract_truth(env, udfc, 1);
	second = extract_truth(env, udfc, 2);
	if (first.err != 0 || second.err != 0){
		out->voidValue = VoidConstant(env);
		fprintf(stderr, "func:equal failed(input)\n");
		UDFThrowError(udfc);
		return;
	}
	ret = first.value && !second.value;
	out->lexemeValue = CreateBoolean(env, ret);
}
