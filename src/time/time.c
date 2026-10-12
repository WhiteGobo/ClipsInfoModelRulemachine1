#include "ClipsInfoModelRulemachine1_time.h"
#include "literals.h"

#include "namespace_XS.h"

CLIPSValue CLIPSValue_from_DateTime(Environment* env, DateTime x){
	char* tmpstring;
	const char* type;
	Literal* literal;
	CLIPSValue ret;
	tmpstring = DateTime_serialize(x);
	if (tmpstring == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	//TODO: use:
	//different types
	type = _XS_dateTime_;
	literal = Literal_new(tmpstring, type);
	free(tmpstring);
	if(literal == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	ret = Literal_to_CLIPSValue_plain(env, literal);
	free_Literal(literal);
	return ret;
}

CLIPSValue CLIPSValue_from_Time(Environment* env, Time x){
	char* tmpstring;
	const char* type;
	Literal* literal;
	CLIPSValue ret;
	tmpstring = Time_serialize(x);
	fprintf(stderr, "brubru time serialize %s\n", tmpstring);
	if (tmpstring == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	//TODO: use:
	//different types
	type = _XS_time_;
	literal = Literal_new(tmpstring, type);
	free(tmpstring);
	if(literal == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	ret = Literal_to_CLIPSValue_plain(env, literal);
	free_Literal(literal);
	return ret;
}

CLIPSValue CLIPSValue_from_Date(Environment* env, Date x){
	char* tmpstring;
	const char* type;
	Literal* literal;
	CLIPSValue ret;
	tmpstring = Date_serialize(x);
	if (tmpstring == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	//TODO: use:
	//different types
	type = _XS_date_;
	literal = Literal_new(tmpstring, type);
	free(tmpstring);
	if(literal == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	ret = Literal_to_CLIPSValue_plain(env, literal);
	free_Literal(literal);
	return ret;
}


CLIPSValue CLIPSValue_from_Duration(Environment* env, Duration x){
	char* tmpstring;
	const char* type;
	Literal* literal;
	CLIPSValue ret;
	tmpstring = Duration_serialize(x);
	if (tmpstring == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	//TODO: use:
	//bool Duration_is_dayTimeDuration(Duration);
	//bool Duration_is_yearMonthDuration(Duration);
	if (x.sum_months == 0){
		type = _XS_dayTimeDuration_;
	} else if (Decimal_equal(x.sum_seconds, Decimal_from_int(0))){
		type = _XS_yearMonthDuration_;
	} else {
		type = _XS_duration_;
	}
	literal = Literal_new(tmpstring, type);
	free(tmpstring);
	if(literal == NULL){
		ret.voidValue = VoidConstant(env);
		return ret;
	}
	ret = Literal_to_CLIPSValue_plain(env, literal);
	free_Literal(literal);
	return ret;
}

CLIPSValue CLIPSValue_from_serialized_Time(Environment* env, const char* x){
	Time time = Time_parse(x);
	return CLIPSValue_from_Time(env, time);
}

CLIPSValue CLIPSValue_from_serialized_Duration(Environment* env, const char* x){
	Duration dur = Duration_parse(x);
	return CLIPSValue_from_Duration(env, dur);
}

CLIPSValue CLIPSValue_from_serialized_DateTime(Environment* env, const char* x){
	DateTime dt = DateTime_parse(x);
	return CLIPSValue_from_DateTime(env, dt);
}

CLIPSValue CLIPSValue_from_serialized_Date(Environment* env, const char* x){
	Date date = Date_parse(x);
	return CLIPSValue_from_Date(env, date);
}
