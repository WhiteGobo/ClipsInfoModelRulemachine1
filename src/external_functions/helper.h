#pragma once
#include <clips.h>
#include "literals.h"
#include <AdvancedCDatatypesDecimal.h>
#include <AdvancedCDatatypesTime.h>

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
typedef struct s_UDFDescription {
	const char *clipsName;
	const char *returnTypes;
	unsigned short minArgs;
	unsigned short maxArgs;
	const char *argTypes;
	UserDefinedFunction *cfp;
	const char *cName;
} UDFDescription;

typedef struct s_UDFDescription_Ext {
	const char *clipsName;
	const char *returnTypes;
	unsigned short minArgs;
	unsigned short maxArgs;
	const char *argTypes;
	UserDefinedFunction *cfp;
	const char *cName;
	void* user;
} UDFDescription_Ext;


struct s_RetExtractTruth{
	int err;
	bool value;
};

typedef struct s_RetGetNthAsInt {
	int err;
	int value;
} RetGetNthAsInt;

typedef struct s_RetGetNthAsNumber {
	int err;
	Number value;
} RetGetNthAsNumber;

struct s_RetExtractTruth extract_truth(Environment* env, UDFContext *udfc, unsigned n);
Literal* UDF_get_nth_as_literal(UDFContext *udfc, unsigned n);
RetGetNthAsInt UDF_get_nth_as_int(Environment*, UDFContext *udfc, unsigned n);
Number UDF_get_nth_as_Number(Environment*, UDFContext *udfc, unsigned n);
RetGetNthAsNumber UDF_get_nth_as_NumberX(Environment*, UDFContext *udfc, unsigned n);

DateTime UDF_get_nth_as_DateTime(Environment*, UDFContext *udfc, unsigned n);
Time UDF_get_nth_as_Time(Environment*, UDFContext *udfc, unsigned n);
Date UDF_get_nth_as_Date(Environment*, UDFContext *udfc, unsigned n);
Duration UDF_get_nth_as_Duration(Environment*, UDFContext *udfc, unsigned n);
