#pragma once
#include "literals.h"

Literal* Literal_from_CLIPSString(Environment*, CLIPSLexeme*);
Literal* Literal_from_CLIPSSymbol(Environment*, CLIPSLexeme*);

Literal* Literal_from_int(Environment*, int64_t);
Literal* Literal_from_float(Environment*, double);
