#pragma once

#ifndef CLIPSPLUGIN_INDEX_CIMR1TermsData
#define CLIPSPLUGIN_INDEX_CIMR1TermsData USER_ENVIRONMENT_DATA + 10
#endif

#include "literals.h"

typedef CLIPSValue Func_CLIPSValueFromLiteralValue(Environment*, const char* value, const char* datatype);

Func_CLIPSValueFromLiteralValue* get_literal_generator_from_datatype(Environment*, const char*);

CLIPSValue CLIPSValue_from_any(Environment*, const char* value, const char* datatype);
