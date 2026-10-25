#include "udfdescription.h"
#include "extractor.h"
#include "helper.h"

#include "namespace_CIMR1.h"


const UDFDescription builtinFunctionList_ImportExport[];

static void rif_import(Environment *env, UDFContext *udfc, UDFValue *out);
static void rif_import_errorprint(Environment* env, int err, const char* location, const char* entailment);
static void rif_load(Environment *env, UDFContext *udfc, UDFValue *out);
static void rif_export(Environment *env, UDFContext *udfc, UDFValue *out);
static void rdf_export(Environment *env, UDFContext *udfc, UDFValue *out);

const UDFDescription builtinFunctionList_ImportExport[] = {
	{"<"_CIMR1_import_">", "*", 1, 2, "*",
		rif_import, "rif_import"},
	{"<"_CIMR1_load_">", "*", 2, 3, "*",
		rif_load, "rif_load"},
	{"<"_CIMR1_export_rif_">", "*", 0, 1, "*",
		rif_export, "rif_export"},
	{"<"_CIMR1_export_rdf_">", "*", 0, 1, "*",
		rdf_export, "rdf_export"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};

static void rif_load(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	Literal *data_lit, *format_lit, *entailment_lit;
	const char *data_value, *format_value, *entailment_value;

	data_lit = UDF_get_nth_as_literal(udfc, 1);
	data_value = Literal_get_value(data_lit);
	if(data_value == NULL){
		fprintf(stderr, "ERROR rif-load failed(data value)\n");
		UDFThrowError(udfc);
		return;
	}
	format_lit = UDF_get_nth_as_literal(udfc, 2);
	format_value = Literal_get_value(format_lit);
	if(format_value == NULL){
		fprintf(stderr, "ERROR rif-load failed(format value)\n");
		UDFThrowError(udfc);
		return;
	}
	if(3 <= UDFArgumentCount(udfc)){
		entailment_lit = UDF_get_nth_as_literal(udfc, 3);
		entailment_value = Literal_get_value(entailment_lit);
		if(entailment_value == NULL){
			fprintf(stderr, "ERROR rif-load failed"
					"(entailment value)\n");
			UDFThrowError(udfc);
			return;
		}
	} else {
		entailment_lit = NULL;
		entailment_value = NULL;
	}
	err = CIMR1_load_data_from_rdf(env, data_value, format_value, entailment_value);
	if (err != 0){
		fprintf(stderr, "Failed CIMR1_load_data_from_rdf\n");
		UDFThrowError(udfc);
	}
	free_Literal(data_lit);
	free_Literal(format_lit);
	free_Literal(entailment_lit);
}

static void rif_export(Environment *env, UDFContext *udfc, UDFValue *out){
	char* tmpout;
	Literal *format = NULL;
	Literal *retlit;
	CLIPSValue ret;
	const char *format_value = "ttl";
	if(1 <= UDFArgumentCount(udfc)){
		format = UDF_get_nth_as_literal(udfc, 1);
		format_value = Literal_get_value(format);
	}
	tmpout = Environment_export_rif_data(env, format_value);
	free_Literal(format);
	if(tmpout == NULL){
		fprintf(stderr, "CIMR1:rif-export failed\n");
		return;
	}
	retlit = Literal_new(tmpout, NULL);
	ret = Literal_to_CLIPSValue(env, retlit);
	out->value = ret.value;
	free(tmpout);
	free_Literal(retlit);
}


static void rdf_export(Environment *env, UDFContext *udfc, UDFValue *out){
	char* tmpout;
	Literal *format = NULL;
	Literal *retlit;
	CLIPSValue ret;
	const char *format_value = "ttl";
	if(1 <= UDFArgumentCount(udfc)){
		format = UDF_get_nth_as_literal(udfc, 1);
		format_value = Literal_get_value(format);
	}
	tmpout = Environment_export_rdf_data(env, format_value);
	free_Literal(format);
	if(tmpout == NULL){
		fprintf(stderr, "CIMR1:rdf-export failed\n");
		return;
	}
	retlit = Literal_new(tmpout, NULL);
	ret = Literal_to_CLIPSValue(env, retlit);
	out->value = ret.value;
	free(tmpout);
	free_Literal(retlit);
}


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
