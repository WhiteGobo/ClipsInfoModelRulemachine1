#include "helper.h"
#include "ClipsInfoModelRulemachine1_number.h"
#include "ClipsInfoModelRulemachine1_time.h"

Literal* UDF_get_nth_as_literal(UDFContext *udfc, unsigned n){
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	if(!UDFNthArgument(udfc, n, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "Failed to get %dth argument\n", n);
		return NULL;
	}
	tmpcv.header = tmpudf.header;
	//TODO use environment
	return Literal_from_CLIPSValue(NULL, tmpcv);
}

Number UDF_get_nth_as_Number(Environment* env, UDFContext *udfc, unsigned n){
	RetGetNthAsNumber ret = UDF_get_nth_as_NumberX(env, udfc, n);
	return ret.value;
}

RetGetNthAsNumber UDF_get_nth_as_NumberX(Environment* env, UDFContext *udfc, unsigned n)
{
	struct ret_CLIPSValue_to_Number tmp;
	RetGetNthAsNumber ret;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	if(!UDFNthArgument(udfc, n, ANY_TYPE_BITS, &tmpudf)){
		ret.err = true;
		ret.value = NUMBER_NAN;
		return ret;
	}
	tmpcv.header = tmpudf.header;
	tmp = CLIPSValue_to_NumberX(env, tmpcv);
	ret.value = tmp.ret;
	ret.err = (tmp.err != 0);
	return ret;
}

RetGetNthAsInt UDF_get_nth_as_int(Environment* env, UDFContext *udfc, unsigned n){
	RetGetNthAsInt ret;
	struct ret_CLIPSValue_to_int retcvtoint;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	if(!UDFNthArgument(udfc, n, ANY_TYPE_BITS, &tmpudf)){
		ret.err = 1;
		return ret;
	}
	tmpcv.header = tmpudf.header;

	retcvtoint = CLIPSValue_to_int(env, tmpcv);
	if(retcvtoint.err != 0){
		ret.err = 2;
		return ret;
	}
	ret.err = 0;
	ret.value = retcvtoint.ret;
	return ret;
}


struct s_RetExtractTruth extract_truth(Environment* env, UDFContext *udfc, unsigned n){
	struct s_RetExtractTruth ret = {0, true};
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	if(!UDFNthArgument(udfc, n, LEXEME_BITS, &tmpudf)){
		ret.err = 1;
		return ret;
	}
	if(tmpudf.lexemeValue == TrueSymbol(env)){
		ret.value = true;
	} else if(tmpudf.lexemeValue == FalseSymbol(env)){
		ret.value = false;
	} else {
		ret.err = 2;
	}
	return ret;
}


Duration UDF_get_nth_as_Duration(Environment *env, UDFContext *udfc, unsigned n){
	Duration ret;
	Literal* lit;
	const char* val;
	lit = UDF_get_nth_as_literal(udfc, n);
	val = Literal_get_value(lit);
	if(val == NULL){
		return DURATION_NAN;
	}
	ret = Duration_parse(val);
	free_Literal(lit);
	return ret;
}


DateTime UDF_get_nth_as_DateTime(Environment *env, UDFContext *udfc, unsigned n){
	DateTime ret;
	Literal* lit;
	const char* val;
	lit = UDF_get_nth_as_literal(udfc, n);
	val = Literal_get_value(lit);
	if(val == NULL){
		return DATETIME_NOTVALID;
	}
	ret = DateTime_parse(val);
	free_Literal(lit);
	return ret;
}

Time UDF_get_nth_as_Time(Environment *env, UDFContext *udfc, unsigned n){
	Time ret;
	Literal* lit;
	const char* val;
	lit = UDF_get_nth_as_literal(udfc, n);
	val = Literal_get_value(lit);
	if(val == NULL){
		return TIME_NOTVALID;
	}
	ret = Time_parse(val);
	free_Literal(lit);
	return ret;
}

Date UDF_get_nth_as_Date(Environment *env, UDFContext *udfc, unsigned n){
	Date ret;
	Literal* lit;
	const char* val;
	lit = UDF_get_nth_as_literal(udfc, n);
	val = Literal_get_value(lit);
	if(val == NULL){
		return DATE_NOTVALID;
	}
	ret = Date_parse(val);
	free_Literal(lit);
	return ret;
}

