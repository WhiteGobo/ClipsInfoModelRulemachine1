#pragma once
#include "literals.h"
#include "lexeme.h"
#include "datatype_to_internal_representation.h"

typedef struct s_Literal {
	TERMTYPE type;
	union {
		char* value;
		CLIPSLexeme* lexeme;
	};
	union {
		char* suffix;
		Environment* env;
	};
} Literal;
