#pragma once

#include <clips.h>
#include <AdvancedCDatatypesDecimal.h>

struct ret_CLIPSValue_to_int {
	int err;
	long long ret;
};
struct ret_CLIPSValue_to_Number {
	int err;
	Number ret;
};

struct ret_CLIPSValue_to_int CLIPSValue_to_int(Environment*, CLIPSValue);

struct ret_CLIPSValue_to_int CLIPSValue_round_to_int(Environment*, CLIPSValue);
struct ret_CLIPSValue_to_Number CLIPSValue_to_NumberX(Environment* env, CLIPSValue cv);
Number CLIPSValue_to_Number(Environment* env, CLIPSValue cv);
CLIPSValue CLIPSValue_from_Number(Environment*, Number);
