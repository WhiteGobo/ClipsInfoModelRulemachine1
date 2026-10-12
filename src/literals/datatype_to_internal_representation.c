#include <stdlib.h>
#include "datatype_to_internal_representation.h"
#include "namespace_XS.h"
#include "terms.h"
#include "ClipsInfoModelRulemachine1_number.h"
#include "ClipsInfoModelRulemachine1_time.h"
#include <AdvancedCDatatypesTime.h>


static CLIPSValue CLIPSValue_from_decimal(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_string(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_anyURI(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_base64Binary(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_boolean(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_date(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_dateTime(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_double(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_duration(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_hexBinary(Environment*, const char* value, const char* datatype);
//static CLIPSValue CLIPSValue_from_QName(Environment*, const char* value, const char* datatype);
static CLIPSValue CLIPSValue_from_time(Environment*, const char* value, const char* datatype);


Func_CLIPSValueFromLiteralValue* get_literal_generator_from_datatype(Environment*, const char* datatype)
{
	if (datatype == NULL) return CLIPSValue_from_string;
	const char* suffix;
	size_t slen;
	size_t dlen = strlen(datatype);
	if (dlen <= sizeof(_XS_)){
		return CLIPSValue_from_any;
	} else if (0 != memcmp(datatype, _XS_, sizeof(_XS_)-1)){
		return CLIPSValue_from_any;
	}
	suffix = datatype + sizeof(_XS_) -1;
	slen = dlen - sizeof(_XS_) + 2;
#define MYTEST(X) slen == sizeof(X) && 0 == strcmp(suffix, X)
	if (MYTEST("decimal")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("integer")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("long")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("int")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("short")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("byte")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("nonNegativeInteger")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("positiveInteger")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("unsignedLong")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("unsignedInt")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("unsignedShort")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("unsignedByte")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("nonPositiveInteger")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("negativeInteger")){
		return CLIPSValue_from_decimal;
	} else if (MYTEST("boolean")){
		return CLIPSValue_from_boolean;
	} else if (MYTEST("date")){
		return CLIPSValue_from_date;
	} else if (MYTEST("dateTime")){
		return CLIPSValue_from_dateTime;
	} else if (MYTEST("dateTimeStamp")){
		return CLIPSValue_from_dateTime;
	} else if (MYTEST("double")){
		return CLIPSValue_from_double;
	} else if (MYTEST("float")){
		return CLIPSValue_from_double;
	} else if (MYTEST("duration")){
		return CLIPSValue_from_duration;
	} else if (MYTEST("dayTimeDuration")){
		return CLIPSValue_from_duration;
	} else if (MYTEST("yearMonthDuration")){
		return CLIPSValue_from_duration;
	} else if (MYTEST("time")){
		return CLIPSValue_from_time;
	} else if (MYTEST("string")){
		fprintf(stderr, "qwertz 1234 string\n");
		return CLIPSValue_from_string;
	//} else if (MYTEST("normalizedString")){
	//	return CLIPSValue_from_string;
	//} else if (MYTEST("token")){
	//	return CLIPSValue_from_string;
	//} else if (MYTEST("language")){
	//	return CLIPSValue_from_string;
	//} else if (MYTEST("Name")){
	//	return CLIPSValue_from_string;
	//} else if (MYTEST("NCName")){
	//	return CLIPSValue_from_string;
	//} else if (MYTEST("NMTOKEN")){
	//	return CLIPSValue_from_string;
	//} else if (MYTEST("anyURI")){
	//	return CLIPSValue_from_anyURI;
	//} else if (MYTEST("base64Binary")){
	//	return CLIPSValue_from_base64Binary;
	//} else if (MYTEST("hexBinary")){
	//	return CLIPSValue_from_hexBinary;
	}
	fprintf(stderr, "qwertz 1234 not string %s %s\n", datatype, suffix);
#undef MYTEST
	return CLIPSValue_from_any;
}

CLIPSValue CLIPSValue_from_any(Environment* env, const char* value, const char* datatype){
	return generate_clipsvalue_from_typedliteral(env, value, datatype);
}

static CLIPSValue CLIPSValue_from_decimal(Environment* env, const char* value, const char* datatype)
{
	Number number;
	Decimal d = Decimal_parse(value, -1);
	number = Number_from_decimal(d);
	return CLIPSValue_from_Number(env, number);
}

static CLIPSValue CLIPSValue_from_string(Environment* env, const char* value, const char* datatype)
{
	return generate_clipsvalue_from_typedliteral(env, value, NULL);
}

static CLIPSValue CLIPSValue_from_anyURI(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_any(env, value, datatype);
}

static CLIPSValue CLIPSValue_from_base64Binary(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_any(env, value, datatype);
}

static CLIPSValue CLIPSValue_from_boolean(Environment* env, const char* value, const char* datatype)
{
	CLIPSValue ret = {.voidValue = VoidConstant(env)};
	if(0 == strcmp(value, "true")){
		ret.lexemeValue = CreateBoolean(env, true);
	} else if(0 == strcmp(value, "1")){
		ret.lexemeValue = CreateBoolean(env, true);
	} else if(0 == strcmp(value, "false")){
		ret.lexemeValue = CreateBoolean(env, false);
	} else if(0 == strcmp(value, "0")){
		ret.lexemeValue = CreateBoolean(env, false);
	}
	return ret;
}

static CLIPSValue CLIPSValue_from_date(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_serialized_Date(env, value);
}

static CLIPSValue CLIPSValue_from_dateTime(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_serialized_DateTime(env, value);
}

static CLIPSValue CLIPSValue_from_double(Environment* env, const char* value, const char* datatype)
{
	CLIPSValue ret;
	double tmp = strtof(value, NULL);
	ret.floatValue = CreateFloat(env, tmp);
	return ret;
}

static CLIPSValue CLIPSValue_from_duration(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_serialized_Duration(env, value);
}

static CLIPSValue CLIPSValue_from_hexBinary(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_any(env, value, datatype);
}

static CLIPSValue CLIPSValue_from_time(Environment* env, const char* value, const char* datatype)
{
	return CLIPSValue_from_serialized_Time(env, value);
}
