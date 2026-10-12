#pragma once
#include <clips.h>
#include "literals.h"
#include <AdvancedCDatatypesDecimal.h>

/**
 *
 * See rules clips documentation "8.2 Registering User Defined Functions"
 *
 * return or arg types:
 * 'b' Boolean
 * 'd' Double Precision Float
 * 'e' External Address
 * 'f' Fact Address
 * 'i' Instance Address
 * 'l' Long Long Integer
 * 'm' Multifield
 * 'n' Instance Name
 * 's' String
 * 'y' Symbol
 * 'v' Void—No Return Value
 * '*' Any Type
 *
 * min/max: any or UNBOUNDED
 *
 * example: 
 * {"<"_CIMR1_import_">", "*", 1, 2, "*", CIMR1_import_rdf, "CIMR1_import_rdf"}
 */
typedef struct UDFDescription_ {
	const char *clipsName;
	const char *returnTypes;
	unsigned short minArgs;
	unsigned short maxArgs;
	const char *argTypes;
	UserDefinedFunction *cfp;
	const char *cName;
} UDFDescription;


struct s_RetExtractTruth{
	int err;
	bool value;
};

typedef struct s_RetGetNthAsInt {
	int err;
	int value;
} RetGetNthAsInt;

struct s_RetExtractTruth extract_truth(Environment* env, UDFContext *udfc, unsigned n);
Literal* UDF_get_nth_as_literal(UDFContext *udfc, unsigned n);
RetGetNthAsInt UDF_get_nth_as_int(Environment*, UDFContext *udfc, unsigned n);
Number UDF_get_nth_as_Number(Environment*, UDFContext *udfc, unsigned n);
