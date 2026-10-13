#pragma once
#include "literals.h"

Literal* Literal_from_CLIPSString(Environment*, CLIPSLexeme*);
Literal* Literal_from_CLIPSSymbol(Environment*, CLIPSLexeme*);
