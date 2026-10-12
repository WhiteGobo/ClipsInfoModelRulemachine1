#include "udfdescription.h"
#include "ClipsInfoModelRulemachine1_list.h"
#include "ClipsInfoModelRulemachine1_number.h"

#include "namespace_PRED.h"
#include "namespace_FUNC.h"

const UDFDescription builtinFunctionList_Math[];

static void add(Environment *env, UDFContext *udfc, UDFValue *out);
static void subtract(Environment *env, UDFContext *udfc, UDFValue *out);
static void multiply(Environment *env, UDFContext *udfc, UDFValue *out);
static void divide(Environment *env, UDFContext *udfc, UDFValue *out);
static void integer_divide(Environment *env, UDFContext *udfc, UDFValue *out);
static void mod(Environment *env, UDFContext *udfc, UDFValue *out);
//static void integer_mod(Environment *env, UDFContext *udfc, UDFValue *out);
static void equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void not_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void less_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void greater_than(Environment *env, UDFContext *udfc, UDFValue *out);
static void greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_Math[] = {
	{"<"_FUNC_numeric_add_">", "*", 2, 2, "*",
		add, "add"},
	{"<"_FUNC_numeric_subtract_">", "*", 2, 2, "*",
		subtract, "subtract"},
	{"<"_FUNC_numeric_multiply_">", "*", 2, 2, "*",
		multiply, "multiply"},
	{"<"_FUNC_numeric_divide_">", "*", 2, 2, "*",
		divide, "divide"},
	{"<"_FUNC_numeric_integer_divide_">", "*", 2, 2, "*",
		integer_divide, "integer_divide"},
	{"<"_FUNC_numeric_integer_mod_">", "*", 2, 2, "*",
		mod, "mod"},
	{"<"_FUNC_numeric_mod_">", "*", 2, 2, "*",
		mod, "mod"},
	{"<"_FUNC_numeric_equal_">", "*", 2, 2, "*",
		equal, "equal"},
	{"<"_FUNC_numeric_not_equal_">", "*", 2, 2, "*",
		not_equal, "not_equal"},
	{"<"_FUNC_numeric_less_than_">", "*", 2, 2, "*",
		less_than, "less_than"},
	{"<"_FUNC_numeric_less_than_or_equal_">", "*", 2, 2, "*",
		less_than_or_equal, "less_than_or_equal"},
	{"<"_FUNC_numeric_greater_than_">", "*", 2, 2, "*",
		greater_than, "greater_than"},
	{"<"_FUNC_numeric_greater_than_or_equal_">", "*", 2, 2, "*",
		greater_than_or_equal, "greater_than_or_equal"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


static void add(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv1, cv2, ret;
	Number x, y, z;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	z = Number_add(x, y);
	ret = CLIPSValue_from_Number(env, z);
	switch(ret.header->type){
		case INTEGER_TYPE:
			fprintf(stderr, "correct type %d\n", ret.integerValue->contents);
			break;
		default:
			fprintf(stderr, "wrong type\n");
	}
	
	out->value = ret.value;
}

static void subtract(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv1, cv2, ret;
	Number x, y, z;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	z = Number_sub(x, y);
	ret = CLIPSValue_from_Number(env, z);
	out->value = ret.value;
}

static void multiply(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv1, cv2, ret;
	Number x, y, z;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	z = Number_mult(x, y);
	ret = CLIPSValue_from_Number(env, z);
	out->value = ret.value;
}

static void divide(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv1, cv2, ret;
	Number x, y, z;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	z = Number_div(x, y);
	ret = CLIPSValue_from_Number(env, z);
	out->value = ret.value;
}

static void integer_divide(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;
	int ret;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_idiv(x, y);
	out->integerValue = CreateInteger(env, ret);
}

static void mod(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	CLIPSValue cv1, cv2, ret;
	Number x, y, z;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	z = Number_mod(x, y);
	ret = CLIPSValue_from_Number(env, z);
	out->value = ret.value;
}

static void equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;
	
	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void not_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_not_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void less_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_less(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void less_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_less_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void greater_than(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_greater(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}

static void greater_than_or_equal(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	UDFValue tmpudf;
	CLIPSValue cv1, cv2;
	Number x, y;

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv1.value = tmpudf.value;
	if (!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	}
	cv2.value = tmpudf.value;

	x = CLIPSValue_to_Number(cv1);
	y = CLIPSValue_to_Number(cv2);
	ret = Number_greater_or_equal(x, y);
	out->lexemeValue = CreateBoolean(env, ret);
}
