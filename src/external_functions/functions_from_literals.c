#include "literals.h"
#include "functions_from_literals.h"

/**
 * Compares two literal strings on equality.
 * No checks for correct arguments.
 */
void pred_literal_not_identical(Environment *env, UDFContext *udfc, UDFValue *out)
{
	UDFValue tmpudf;
	CLIPSValue tmpclips;
	Literal *x1, *x2;
	bool ret;
	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err1\n");
		UDFThrowError(udfc);
		return;
	} else {
		tmpclips.header = tmpudf.header;
		x1 = Literal_from_CLIPSValue(env, tmpclips);
	}
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		fprintf(stderr, "brubru err2\n");
		UDFThrowError(udfc);
		return;
	} else {
		tmpclips.header = tmpudf.header;
		x2 = Literal_from_CLIPSValue(env, tmpclips);
	}
	ret = !Literal_equal(x1, x2);
	free_Literal(x1);
	free_Literal(x2);
	out->lexemeValue = CreateBoolean(env, ret);
}
