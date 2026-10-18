#include "udfdescription.h"
#include "literals.h"
#include "ClipsInfoModelRulemachine1_list.h"

#include <regex.h>
#include "helper.h"

#include "namespace_XS.h"
#include "namespace_PRED.h"
#include "namespace_FUNC.h"

const UDFDescription builtinFunctionList_IsLiteral[];

static void is_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_base64Binary(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_base64Binary(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_anyURI(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_anyURI(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_boolean(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_boolean(Environment *env, UDFContext *udfc, UDFValue *out);

static void is_double(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_double(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_float(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_float(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_decimal(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_decimal(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_integer(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_integer(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_long(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_long(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_int(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_int(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_short(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_short(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_byte(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_byte(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out);

static void is_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_dateTime(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_dateTimeStamp(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_dateTimeStamp(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_date(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_time(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_not_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out);


//static void is_(Environment *env, UDFContext *udfc, UDFValue *out);
//static void is_not_(Environment *env, UDFContext *udfc, UDFValue *out);
static void is_list(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_IsLiteral[] = {
	{"<"_PRED_is_literal_hexBinary_">", "b", 1, 1, "*",
		is_hexBinary, "is_hexBinary"},
	{"<"_PRED_is_literal_not_hexBinary_">", "b", 1, 1, "*",
		is_not_hexBinary, "is_not_hexBinary"},
	{"<"_PRED_is_literal_base64Binary_">", "b", 1, 1, "*",
		is_base64Binary, "is_base64Binary"},
	{"<"_PRED_is_literal_not_base64Binary_">", "b", 1, 1, "*",
		is_not_base64Binary, "is_not_base64Binary"},
	{"<"_PRED_is_literal_anyURI_">", "b", 1, 1, "*",
		is_anyURI, "is_anyURI"},
	{"<"_PRED_is_literal_not_anyURI_">", "b", 1, 1, "*",
		is_not_anyURI, "is_not_anyURI"},
	{"<"_PRED_is_literal_boolean_">", "b", 1, 1, "*",
		is_boolean, "is_boolean"},
	{"<"_PRED_is_literal_not_boolean_">", "b", 1, 1, "*",
		is_not_boolean, "is_not_boolean"},
	{"<"_PRED_is_literal_double_">", "b", 1, 1, "*",
		is_double, "is_double"},
	{"<"_PRED_is_literal_not_double_">", "b", 1, 1, "*",
		is_not_double, "is_not_double"},
	{"<"_PRED_is_literal_float_">", "b", 1, 1, "*",
		is_float, "is_float"},
	{"<"_PRED_is_literal_not_float_">", "b", 1, 1, "*",
		is_not_float, "is_not_float"},
	{"<"_PRED_is_literal_decimal_">", "b", 1, 1, "*",
		is_decimal, "is_decimal"},
	{"<"_PRED_is_literal_not_decimal_">", "b", 1, 1, "*",
		is_not_decimal, "is_not_decimal"},
	{"<"_PRED_is_literal_integer_">", "b", 1, 1, "*",
		is_integer, "is_integer"},
	{"<"_PRED_is_literal_not_integer_">", "b", 1, 1, "*",
		is_not_integer, "is_not_integer"},
	{"<"_PRED_is_literal_int_">", "b", 1, 1, "*",
		is_int, "is_int"},
	{"<"_PRED_is_literal_not_int_">", "b", 1, 1, "*",
		is_not_int, "is_not_int"},
	{"<"_PRED_is_literal_long_">", "b", 1, 1, "*",
		is_long, "is_long"},
	{"<"_PRED_is_literal_not_long_">", "b", 1, 1, "*",
		is_not_long, "is_not_long"},
	{"<"_PRED_is_literal_short_">", "b", 1, 1, "*",
		is_short, "is_short"},
	{"<"_PRED_is_literal_not_short_">", "b", 1, 1, "*",
		is_not_short, "is_not_short"},
	{"<"_PRED_is_literal_byte_">", "b", 1, 1, "*",
		is_byte, "is_byte"},
	{"<"_PRED_is_literal_not_byte_">", "b", 1, 1, "*",
		is_not_byte, "is_not_byte"},
	{"<"_PRED_is_literal_nonNegativeInteger_">", "b", 1, 1, "*",
		is_nonNegativeInteger, "is_nonNegativeInteger"},
	{"<"_PRED_is_literal_not_nonNegativeInteger_">", "b", 1, 1, "*",
		is_not_nonNegativeInteger, "is_not_nonNegativeInteger"},
	{"<"_PRED_is_literal_positiveInteger_">", "b", 1, 1, "*",
		is_positiveInteger, "is_positiveInteger"},
	{"<"_PRED_is_literal_not_positiveInteger_">", "b", 1, 1, "*",
		is_not_positiveInteger, "is_not_positiveInteger"},
	{"<"_PRED_is_literal_unsignedLong_">", "b", 1, 1, "*",
		is_unsignedLong, "is_unsignedLong"},
	{"<"_PRED_is_literal_not_unsignedLong_">", "b", 1, 1, "*",
		is_not_unsignedLong, "is_not_unsignedLong"},
	{"<"_PRED_is_literal_unsignedInt_">", "b", 1, 1, "*",
		is_unsignedInt, "is_unsignedInt"},
	{"<"_PRED_is_literal_not_unsignedInt_">", "b", 1, 1, "*",
		is_not_unsignedInt, "is_not_unsignedInt"},
	{"<"_PRED_is_literal_unsignedShort_">", "b", 1, 1, "*",
		is_unsignedShort, "is_unsignedShort"},
	{"<"_PRED_is_literal_not_unsignedShort_">", "b", 1, 1, "*",
		is_not_unsignedShort, "is_not_unsignedShort"},
	{"<"_PRED_is_literal_unsignedByte_">", "b", 1, 1, "*",
		is_unsignedByte, "is_unsignedByte"},
	{"<"_PRED_is_literal_not_unsignedByte_">", "b", 1, 1, "*",
		is_not_unsignedByte, "is_not_unsignedByte"},
	{"<"_PRED_is_literal_nonPositiveInteger_">", "b", 1, 1, "*",
		is_nonPositiveInteger, "is_nonPositiveInteger"},
	{"<"_PRED_is_literal_not_nonPositiveInteger_">", "b", 1, 1, "*",
		is_not_nonPositiveInteger, "is_not_nonPositiveInteger"},
	{"<"_PRED_is_literal_negativeInteger_">", "b", 1, 1, "*",
		is_negativeInteger, "is_negativeInteger"},
	{"<"_PRED_is_literal_not_negativeInteger_">", "b", 1, 1, "*",
		is_not_negativeInteger, "is_not_negativeInteger"},
	{"<"_PRED_is_literal_dateTime_">", "b", 1, 1, "*",
		is_dateTime, "is_dateTime"},
	{"<"_PRED_is_literal_not_dateTime_">", "b", 1, 1, "*",
		is_not_dateTime, "is_not_dateTime"},
	{"<"_PRED_is_literal_dateTimeStamp_">", "b", 1, 1, "*",
		is_dateTimeStamp, "is_dateTimeStamp"},
	{"<"_PRED_is_literal_not_dateTimeStamp_">", "b", 1, 1, "*",
		is_not_dateTimeStamp, "is_not_dateTimeStamp"},
	{"<"_PRED_is_literal_date_">", "b", 1, 1, "*",
		is_date, "is_date"},
	{"<"_PRED_is_literal_not_date_">", "b", 1, 1, "*",
		is_not_date, "is_not_date"},
	{"<"_PRED_is_literal_time_">", "b", 1, 1, "*",
		is_time, "is_time"},
	{"<"_PRED_is_literal_not_time_">", "b", 1, 1, "*",
		is_not_time, "is_not_time"},
	{"<"_PRED_is_literal_dayTimeDuration_">", "b", 1, 1, "*",
		is_dayTimeDuration, "is_dayTimeuration"},
	{"<"_PRED_is_literal_not_dayTimeDuration_">", "b", 1, 1, "*",
		is_not_dayTimeDuration, "is_not_dayTimeDuration"},
	{"<"_PRED_is_literal_yearMonthDuration_">", "b", 1, 1, "*",
		is_yearMonthDuration, "is_yearMonthDuration"},
	{"<"_PRED_is_literal_not_yearMonthDuration_">", "b", 1, 1, "*",
		is_not_yearMonthDuration, "is_not_yearMonthDuration"},
	//{"<"_PRED_is_literal__">", "b", 1, 1, "*",
	//	is_, "is_"},
	//{"<"_PRED_is_literal_not__">", "b", 1, 1, "*",
	//	is_not_, "is_not_"},
	{"<"_PRED_is_list_">", "b", 1, 1, "*",
		is_list, "is_list"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


#define REGHEXBINARY "^([0-9a-fA-F][0-9a-fA-F])*$"
static void is_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	Literal* value = UDF_get_nth_as_literal(udfc, 1);
	if (value == NULL){
		ret = false;
	} else {
		ret = Literal_check_value_against_regex(value, REGHEXBINARY);
	}
	out->lexemeValue = CreateBoolean(env, ret);
}


static void is_not_hexBinary(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	Literal* value = UDF_get_nth_as_literal(udfc, 1);
	if (value == NULL){
		ret = false;
	} else {
		ret = Literal_check_value_against_regex(value, REGHEXBINARY);
	}
	out->lexemeValue = CreateBoolean(env, !ret);
}


#define B64quad "([A-Za-z0-9+/][A-Za-z0-9+/][A-Za-z0-9+/][A-Za-z0-9+/])"
#define Padded16 "([A-Za-z0-9+/][A-Za-z0-9+/][AEIMQUYcgkosw048]=)"
#define Padded8 "([A-Za-z0-9+/][AQgw]=[ ]?=)"
#define REGBASE64BINARY "^("B64quad"*("B64quad"|"Padded16"|"Padded8"))?$"
static void is_base64Binary(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	Literal* value = UDF_get_nth_as_literal(udfc, 1);
	if (value == NULL){
		ret = false;
	} else {
		ret = Literal_check_value_against_regex(value, REGBASE64BINARY);
	}
	out->lexemeValue = CreateBoolean(env, ret);
}

static void is_not_base64Binary(Environment *env, UDFContext *udfc, UDFValue *out)
{
	bool ret;
	Literal* value = UDF_get_nth_as_literal(udfc, 1);
	if (value == NULL){
		ret = false;
	} else {
		ret = Literal_check_value_against_regex(value, REGBASE64BINARY);
	}
	out->lexemeValue = CreateBoolean(env, !ret);
}

static void is_anyURI(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Literal* value = UDF_get_nth_as_literal(udfc, 1);
	if (value == NULL){
		ret = false;
	} else {
		//TODO
		fprintf(stderr, "WARNING is_anyURI doesnt check correct valuespace\n");
		ret = Literal_check_value_against_regex(value, ".*");
	}
	if(ret){
		ret = 0==strcmp(_XS_anyURI_, Literal_get_datatype(value));
	}
	out->lexemeValue = CreateBoolean(env, ret);
}

static void is_not_anyURI(Environment *env, UDFContext *udfc, UDFValue *out){
	bool ret;
	Literal* value = UDF_get_nth_as_literal(udfc, 1);
	if (value == NULL){
		ret = false;
	} else {
		//TODO
		fprintf(stderr, "WARNING is_anyURI doesnt check correct valuespace\n");
		ret = Literal_check_value_against_regex(value, ".*");
	}
	if(ret){
		ret = 0==strcmp(_XS_anyURI_, Literal_get_datatype(value));
	}
	out->lexemeValue = CreateBoolean(env, !ret);
}

static void is_boolean(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "ERROR is_boolean\n");
		UDFThrowError(udfc);
		return;
	}
	if(tmpudf.lexemeValue == TrueSymbol(env)){
		out->lexemeValue = CreateBoolean(env, true);
	} else if(tmpudf.lexemeValue == FalseSymbol(env)){
		out->lexemeValue = CreateBoolean(env, true);
	} else {
		out->lexemeValue = CreateBoolean(env, false);
	}
}
static void is_not_boolean(Environment *env, UDFContext *udfc, UDFValue *out){
	UDFValue tmpudf;
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "ERROR is_not_boolean\n");
		UDFThrowError(udfc);
		return;
	}
	if(tmpudf.lexemeValue == TrueSymbol(env)){
		out->lexemeValue = CreateBoolean(env, false);
	} else if(tmpudf.lexemeValue == FalseSymbol(env)){
		out->lexemeValue = CreateBoolean(env, false);
	} else {
		out->lexemeValue = CreateBoolean(env, true);
	}
}

static void is_double(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_double(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_float(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_float(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_decimal(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_decimal(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_integer(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented is_literal_integer\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_integer(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_long(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_long(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_int(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_int(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_short(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_short(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_byte(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_byte(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_nonNegativeInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_positiveInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_unsignedLong(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_unsignedInt(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_unsignedShort(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_unsignedByte(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_nonPositiveInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_negativeInteger(Environment *env, UDFContext *udfc, UDFValue *out){
	RetGetNthAsNumber val = UDF_get_nth_as_NumberX(env, udfc, 1);
	if(val.err){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	//TODO
	fprintf(stderr, "Not Implemented\n");
	out->lexemeValue = CreateBoolean(env, false);
}

static void is_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime value = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(!DateTime_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	out->lexemeValue = CreateBoolean(env, true);
}

static void is_not_dateTime(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime value = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(!DateTime_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	fprintf(stderr, "qwertz 1234\n");
	fprintf_DateTime(stderr, value);
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_dateTimeStamp(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime value = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(!DateTime_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_dateTimeStamp(Environment *env, UDFContext *udfc, UDFValue *out){
	DateTime value = UDF_get_nth_as_DateTime(env, udfc, 1);
	if(!DateTime_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	out->lexemeValue = CreateBoolean(env, false);
}

static void is_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date value = UDF_get_nth_as_Date(env, udfc, 1);
	if(!Date_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	out->lexemeValue = CreateBoolean(env, true);
}

static void is_not_date(Environment *env, UDFContext *udfc, UDFValue *out){
	Date value = UDF_get_nth_as_Date(env, udfc, 1);
	fprintf(stderr, "is_not_date\n");
	fprintf_Date(stderr, value);
	fprintf(stderr, "is_not_date %d %d\n", value.year, DATE_NOTVALID.year);
	if(!Date_is_valid(value)){
		fprintf(stderr, "was not valid\n");
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	out->lexemeValue = CreateBoolean(env, false);
}

static void is_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time value = UDF_get_nth_as_Time(env, udfc, 1);
	if(!Time_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	out->lexemeValue = CreateBoolean(env, true);
}

static void is_not_time(Environment *env, UDFContext *udfc, UDFValue *out){
	Time value = UDF_get_nth_as_Time(env, udfc, 1);
	if(!Time_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	out->lexemeValue = CreateBoolean(env, false);
}

static void is_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration value = UDF_get_nth_as_Duration(env, udfc, 1);
	if(!Duration_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_dayTimeDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration value = UDF_get_nth_as_Duration(env, udfc, 1);
	if(!Duration_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	out->lexemeValue = CreateBoolean(env, false);
}
static void is_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration value = UDF_get_nth_as_Duration(env, udfc, 1);
	if(!Duration_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, false);
		return;
	}
	out->lexemeValue = CreateBoolean(env, true);
}
static void is_not_yearMonthDuration(Environment *env, UDFContext *udfc, UDFValue *out){
	Duration value = UDF_get_nth_as_Duration(env, udfc, 1);
	if(!Duration_is_valid(value)){
		out->lexemeValue = CreateBoolean(env, true);
		return;
	}
	out->lexemeValue = CreateBoolean(env, false);
}

/*static void is_(Environment *env, UDFContext *udfc, UDFValue *out){
			out->lexemeValue = CreateBoolean(env, false);
}
static void is_not_(Environment *env, UDFContext *udfc, UDFValue *out){
			out->lexemeValue = CreateBoolean(env, false);
}*/

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
