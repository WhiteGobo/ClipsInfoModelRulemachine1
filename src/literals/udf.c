#include "ClipsInfoModelRulemachine1_literals.h"

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

