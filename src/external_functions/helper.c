#include "helper.h"
#include "ClipsInfoModelRulemachine1_number.h"

Literal* UDF_get_nth_as_literal(UDFContext *udfc, unsigned n){
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	if(!UDFNthArgument(udfc, n, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "Failed to get %dth argument\n", n);
		return NULL;
	}
	tmpcv.header = tmpudf.header;
	return Literal_from_CLIPSValue(tmpcv);
}


Number UDF_get_nth_as_Number(Environment* env, UDFContext *udfc, unsigned n){
	Number ret;
	struct ret_CLIPSValue_to_int retcvtoint;
	UDFValue tmpudf;
	CLIPSValue tmpcv;
	if(!UDFNthArgument(udfc, n, ANY_TYPE_BITS, &tmpudf)){
		return NUMBER_NAN;
	}
	tmpcv.header = tmpudf.header;
	ret = CLIPSValue_to_Number(tmpcv);
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


