#pragma once

#include <clips.h>
#include <AdvancedCDatatypesDecimal.h>

struct ret_CLIPSValue_to_int {
	int err;
	long long ret;
};

struct ret_CLIPSValue_to_int CLIPSValue_to_int(Environment*, CLIPSValue);

struct ret_CLIPSValue_to_int CLIPSValue_round_to_int(Environment*, CLIPSValue);

Number CLIPSValue_to_Number(CLIPSValue);
CLIPSValue CLIPSValue_from_Number(Environment*, Number);
