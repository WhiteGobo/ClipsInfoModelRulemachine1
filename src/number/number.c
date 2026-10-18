#include "ClipsInfoModelRulemachine1_number.h"
#include "AdvancedCDatatypesDecimal.h"
#include "literals.h"
#include "namespace_XS.h"

static CLIPSValue CLIPSValue_from_quotient(Environment* env, Quotient x);
static CLIPSValue CLIPSValue_from_decimal(Environment* env, Decimal x);

struct ret_CLIPSValue_to_int CLIPSValue_to_int(Environment* env, CLIPSValue cv){
	struct ret_CLIPSValue_to_int ret = {
		.err = 0
	};
	switch(cv.header->type){
		case INTEGER_TYPE:
			ret.ret = cv.integerValue->contents;
			return ret;
		default:
			ret.err = 1;
			return ret;
	}
}


struct ret_CLIPSValue_to_int CLIPSValue_round_to_int(Environment* env, CLIPSValue cv)
{
	return CLIPSValue_to_int(env, cv);
}

struct ret_CLIPSValue_to_Number CLIPSValue_to_NumberX(Environment* env, CLIPSValue cv){
	struct ret_CLIPSValue_to_Number ret = {.err = 0};
	Literal *literal;
	Decimal as_decimal;
	switch(cv.header->type){
		case INTEGER_TYPE:
			ret.ret = Number_from_int(cv.integerValue->contents);
			return ret;
		case FLOAT_TYPE:
			ret.ret = Number_from_float(cv.floatValue->contents);
			return ret;
	}
	literal = Literal_from_CLIPSValue(env, cv);
	if (literal == NULL){
		ret.ret = NUMBER_NAN;
		ret.err = 0;
		return ret;
	}
	as_decimal = Decimal_parse(Literal_get_value(literal), -1);
	ret.ret = Number_from_decimal(as_decimal);
	if (Decimal_equal(as_decimal, DECIMAL_NAN)){
		if(NAN_parse(Literal_get_value(literal))){
			ret.err = 0;
		} else {
			ret.err = 1;
		}
	}
	return ret;
}

Number CLIPSValue_to_Number(Environment* env, CLIPSValue cv){
	struct ret_CLIPSValue_to_Number ret = CLIPSValue_to_NumberX(env, cv);
	return ret.ret;
}

static CLIPSValue CLIPSValue_from_quotient(Environment* env, Quotient x){
	CLIPSValue ret;
	double x_f;
	Decimal x_d = Quotient_try_to_decimal(x);
	if (Decimal_not_equal(x_d, DECIMAL_NAN)){
		return CLIPSValue_from_decimal(env, x_d);
	}
	x_f = x.numerator / x.denominator;
	ret.floatValue = CreateFloat(env, x_f);
	return ret;
}

static CLIPSValue CLIPSValue_from_decimal(Environment* env, Decimal x){
	char* tmpstring;
	Literal* literal;
	CLIPSValue ret;
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	if(Decimal_is_int(x)){
		ret.integerValue = CreateInteger(env, Decimal_round(x));
		return ret;
	}
	tmpstring = Decimal_serialize(x);
	if (tmpstring == NULL){
		return void_value;
	}
	literal = Literal_new(tmpstring, _XS_decimal_);
	free(tmpstring);
	if(literal == NULL){
		return void_value;
	}
	ret = Literal_to_CLIPSValue_plain(env, literal);
	free_Literal(literal);
	return ret;
}

CLIPSValue CLIPSValue_from_Number(Environment* env, Number x){
	CLIPSValue void_value = {.voidValue = VoidConstant(env)};
	CLIPSValue ret = {.voidValue = VoidConstant(env)};
	if (Number_is_int(x)){
		ret.integerValue = CreateInteger(env, Number_round(x));
		return ret;
	}
	switch(x.type){
		case NT_NAN:
			fprintf(stderr, "CLIPSValue_from Number not implemented\n");
			//TODO
			break;
		case NT_FLOAT:
			ret.floatValue = CreateFloat(env, x.f);
			return ret;
		case NT_DECIMAL:
			return CLIPSValue_from_decimal(env, x.d);
		case NT_QUOTIENT:
			return CLIPSValue_from_quotient(env, x.q);
	}
	return void_value;
}
