#pragma once
#include "literals.h"
#include "lexeme.h"
#include "datatype_to_internal_representation.h"

typedef enum {
	LITERAL_TERM,
	LITERAL_LEXEME,
} LITERALTYPE;

typedef struct s_Literal {
	LITERALTYPE t;
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
