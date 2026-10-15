#include "udfdescription.h"
#include "extractor.h"

#include "namespace_CIMR1.h"

const UDFDescription builtinFunctionList_ImportExport[];

static void rif_import(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_ImportExport[] = {
	{"<"_CIMR1_import_">", "*", 1, 2, "*",
		rif_import, "rif_import"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


static void rif_import(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	Literal *location, *entailment;
	const char *location_value, *entailment_value;

	location = UDF_get_nth_as_literal(udfc, 1);
	location_value = Literal_get_value(location);
	if(location_value == NULL){
		fprintf(stderr, "ERROR import failed(location value)\n");
		UDFThrowError(udfc);
		return;
	}
	if(2 <= UDFArgumentCount(udfc)){
		fprintf(stderr, "Try to retrieve entailment\n");
		entailment = UDF_get_nth_as_literal(udfc, 2);
		fprintf_Literal(stderr, entailment);
		entailment_value = Literal_get_value(entailment);
		if(entailment_value == NULL){
			fprintf(stderr, "ERROR import failed(entailment value)\n");
			UDFThrowError(udfc);
			return;
		}
	} else {
		entailment = NULL;
		entailment_value = NULL;
	}
	fprintf(stderr, "relative import2\n");
	err = relative_import(env,
			location_value,
			entailment_value);
	free_Literal(entailment);
	free_Literal(location);
	if (err != 0){
		fprintf(stderr, "ERROR import of rif data failed\n");
		UDFThrowError(udfc);
	}
}
