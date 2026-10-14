#include "udfdescription.h"
#include "literals.h"
#include "ClipsInfoModelRulemachine1_list.h"

#include <regex.h>

#include "namespace_PRED.h"
#include "namespace_FUNC.h"

const UDFDescription builtinFunctionList_IsLiteral[];

static void is_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_base64Binary(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_list(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_IsLiteral[] = {
	{"<"_PRED_is_literal_hexBinary_">", "b", 1, 1, "s",
		is_hexBinary, "is_hexBinary"},
	{"<"_PRED_is_literal_base64Binary_">", "b", 1, 1, "s",
		is_base64Binary, "is_base64Binary"},
	{"<"_PRED_is_list_">", "b", 1, 1, "*",
		is_list, "is_list"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


#define REGHEXBINARY "^([0-9a-fA-F][0-9a-fA-F])*$"
static void is_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out)
{
	int err;
	UDFValue tmpudf;
	CLIPSValue tmpclips;
	Literal *x1;
	regex_t reg;
	err = regcomp(&reg, REGHEXBINARY, REG_EXTENDED);
	if (err != 0){
		fprintf(stderr, "REGEX failed\n");
		UDFThrowError(udfc);
		return;
	}

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	} else {
		tmpclips.header = tmpudf.header;
		x1 = Literal_from_CLIPSValue(env, tmpclips);
	}

	err = regexec(&reg, Literal_get_value(x1), 0, NULL, 0);
	regfree(&reg);
	free_Literal(x1);
	switch(err){
		case 0:
			out->lexemeValue = CreateBoolean(env, true);
			break;
		default:
			out->lexemeValue = CreateBoolean(env, false);
	}
}

#define B64quad "([A-Za-z0-9+/][A-Za-z0-9+/][A-Za-z0-9+/][A-Za-z0-9+/])"
#define Padded16 "([A-Za-z0-9+/][A-Za-z0-9+/][AEIMQUYcgkosw048]=)"
#define Padded8 "([A-Za-z0-9+/][AQgw]=[ ]?=)"
#define REGBASE64BINARY "^("B64quad"*("B64quad"|"Padded16"|"Padded8"))?$"
static void is_base64Binary(Environment *env, UDFContext *udfc, UDFValue *out)
{
	int err;
	UDFValue tmpudf;
	CLIPSValue tmpclips;
	Literal *x1;
	regex_t reg;
	//err = regcomp(&reg, REGBASE64BINARY, REG_EXTENDED);
	err = regcomp(&reg, REGBASE64BINARY, REG_EXTENDED);
	if (err != 0){
		fprintf(stderr, "REGEX failed\n");
		UDFThrowError(udfc);
		return;
	}

	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	} else {
		tmpclips.header = tmpudf.header;
		x1 = Literal_from_CLIPSValue(env, tmpclips);
	}

	err = regexec(&reg, Literal_get_value(x1), 0, NULL, 0);
	regfree(&reg);
	free_Literal(x1);
	switch(err){
		case 0:
			out->lexemeValue = CreateBoolean(env, true);
			break;
		default:
			out->lexemeValue = CreateBoolean(env, false);
	}
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
