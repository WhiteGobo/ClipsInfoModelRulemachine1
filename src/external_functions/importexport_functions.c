#include "udfdescription.h"
#include "extractor.h"

#include "namespace_CIMR1.h"

const UDFDescription builtinFunctionList_ImportExport[];

static void rif_import(Environment *env, UDFContext *udfc, UDFValue *out);
static void rif_import_errorprint(Environment* env, int err, const char* location, const char* entailment);

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
		entailment = UDF_get_nth_as_literal(udfc, 2);
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
	err = relative_import(env,
			location_value,
			entailment_value);
	if (err != 0){
		rif_import_errorprint(env, err, location_value, entailment_value);
		UDFThrowError(udfc);
	}
	free_Literal(entailment);
	free_Literal(location);
}

static void rif_import_errorprint(Environment* env, int err, const char* location, const char* entailment)
{
	char *tmp;
	rif_import_errorprint(env, err, location, entailment);
	WriteString(env, STDERR, "ERROR rif_import of ");
	WriteString(env, STDERR, location);
	if (entailment != NULL){
		WriteString(env, STDERR, " with entailment ");
		WriteString(env, STDERR, entailment);
	}
	WriteString(env, STDERR, " failed.\n");
	tmp = Environment_get_debug_information_import(env);
	if(tmp != NULL){
		WriteString(env, STDERR, tmp);
	}
	WriteString(env, STDERR, "\n");
	free(tmp);
}
