#pragma once
#include "literals.h"
#include "lexeme.h"
#include "datatype_to_internal_representation.h"

#ifndef RDF_TERMTYPE_DEFINED
#define RDF_TERMTYPE_DEFINED
typedef enum {
        URI = 0,
        BNODE = 1,
        TYPEDLITERAL = 2,
        LANGLITERAL = 3
} TERMTYPE;
#endif

typedef struct s_Literal {
	TERMTYPE type;
	char* value;
	char* suffix;
} Literal;
