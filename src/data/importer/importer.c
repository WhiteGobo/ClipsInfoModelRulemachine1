#include "ClipsInfoModelRulemachine1_data_importer.h"
#include "callback.h"

#include <Mime2Rdf4C.h>
#include <DataloaderRDF.h>
#include <RIFImporterDebug.h>

#ifndef INFO_MODEL_RULEMACHINE1_DATA_IMPORTER_INDEX
#define INFO_MODEL_RULEMACHINE1_DATA_IMPORTER_INDEX USER_ENVIRONMENT_DATA + 17
#endif

typedef struct s_MyData {
	CallbackConfig* cfg;
} MyData;

extern int load_RIFIData_into_Environment(RIFIData* data, Environment *env);

static CallbackConfig* Environment_get_importer_CallbackConfig(Environment* env);
static void release_data(Environment*);

int Environment_register_ClipsInfoModelRulemachine1_data_importer(Environment* env)
{
	bool success;
	success = AllocateEnvironmentData(env, INFO_MODEL_RULEMACHINE1_DATA_IMPORTER_INDEX,
					sizeof(MyData),
					release_data);
	if(!success){
		return 1;
	}
	MyData* data = (MyData*) GetEnvironmentData(env,
				INFO_MODEL_RULEMACHINE1_DATA_IMPORTER_INDEX);
	data->cfg = CallbackConfig_new();
	if(data->cfg == NULL){
		return 1;
	}
	return 0;
}

static void release_data(Environment* env){
	MyData* data = (MyData*) GetEnvironmentData(env,
				INFO_MODEL_RULEMACHINE1_DATA_IMPORTER_INDEX);
	free_CallbackConfig(data->cfg);
	data->cfg = NULL;
}

int Environment_add_local_import_location(Environment *env, const char* iri, const char* path){
	int err;
	CallbackConfig* config = Environment_get_importer_CallbackConfig(env);
	err = CallbackConfig_add_local_location(config, iri, path);
	return err;
}


int Environment_import_from_iri(Environment* env, const char* iri, const char* entailment){
	int err;
	CallbackConfig* config = Environment_get_importer_CallbackConfig(env);
	//return err;

	DRDFDataloader* dataloader = DRDFDataloader_new();
	if (dataloader == NULL){
		fprintf(stderr, "ERROR Environment_import_from_iri\n");
		return 1;
	}

	Path2IriArray* qq = CallbackConfig_get_all_path2iri(config);

	for (size_t i = 0; i<qq->len; i++){
		Path2Iri x = qq->contents[i];
		switch(DRDFDataloader_add_path_iri(dataloader, x.path, x.iri)){
			case 0:
				break;
			default:
				free_Path2IriArray(qq);
				free_DRDFDataloader(dataloader);
				fprintf(stderr, "Internal ERROR Environment_import_from_iri\n");
				return 1;
		}
	}
	free_Path2IriArray(qq);
	RIFIGraph* graph = RIFIGraph_new();
	if (graph == NULL){
		free_DRDFDataloader(dataloader);
		fprintf(stderr, "Internal ERROR Environment_import_from_iri\n");
		return 1;
	}
	err = DRDFDataloader_load_data(dataloader, iri,
					(TripleHandler*) RIFIGraph_add, graph);
	free_DRDFDataloader(dataloader);
	if(err != 0){
		fprintf(stderr, "ERROR Environment_import_from_iri\n");
		return 1;
	}
	RIFIData* data = RIFIGraph_to_RIFIData(graph, entailment);
	if (data == NULL){
		fprintf(stderr, "Internal Error.RIFIGraph_to_RIFIData failed\n");
		return 1;
	}
	err = load_RIFIData_into_Environment(data, env);
	if(err != 0){
		fprintf(stderr, "Something went wrong during "
				"load_RIFIData_into_environment\n");
	}
	return err;
}

int Environment_import_from_data(Environment* env, const char* data, const char* format, const char* entailment)
{
	int64_t err;
	Mime2Rdf4C_ParserConfig* parser;

	parser = Mime2Rdf4C_get_parser_from_ext(format);
	if(parser == NULL){
		parser = Mime2Rdf4C_get_parser_from_mediatype(format);
	}
	if(parser == NULL){
		fprintf(stderr, "ERROR Environment_import_from_data(format)\n");
		return 1;
	}

	RIFIGraph* graph = RIFIGraph_new();
	if (graph == NULL){
		free_Mime2Rdf4CParserConfig(parser);
		fprintf(stderr, "INTERNAL ERROR Environment_import_from_data\n");
		return 1;
	}
	err = Mime2Rdf4C_parse(data, (TripleHandler*) RIFIGraph_add, graph, parser);
	free_Mime2Rdf4CParserConfig(parser);
	RIFIData* rifidata = RIFIGraph_to_RIFIData(graph, entailment);
	if (rifidata == NULL){
		fprintf(stderr, "INTERNAL ERROR Environment_import_from_data\n");
		return 1;
	}
	err = load_RIFIData_into_Environment(rifidata, env);
	if(err != 0){
		fprintf(stderr, "ERROR Environment_import_from_data\n");
	}
	return err;
}



static CallbackConfig* Environment_get_importer_CallbackConfig(Environment* env){
	MyData* data = (MyData*) GetEnvironmentData(env,
				INFO_MODEL_RULEMACHINE1_DATA_IMPORTER_INDEX);
	return data->cfg;
}


char* Environment_generate_import_iri_from_path(Environment* env, const char* path)
{
	CallbackConfig* config = Environment_get_importer_CallbackConfig(env);
	return CallbackConfig_path2iri(config, path);
}

char* Environment_get_debug_information_for_import(Environment* env){
	char* ret;
	CallbackConfig* config = Environment_get_importer_CallbackConfig(env);
	if(config == NULL){
		ret = malloc(sizeof("BrokenImport()") + 1);
		sprintf(ret, "BrokenImport()");
		return ret;
	}
	Path2IriArray* qq = CallbackConfig_get_all_path2iri(config);
	size_t l = sizeof("ImportInformation()"+5);
	for (size_t i = 0; i<qq->len; i++){
		Path2Iri x = qq->contents[i];
		l += sizeof("->, ") + strlen(x.path) + strlen(x.iri);
	}
	ret = malloc(l);
	char* tmp = ret;
	sprintf(tmp, "ImportIri2Path(");
	tmp += strlen(tmp);
	for (size_t i = 0; i<qq->len; i++){
		Path2Iri x = qq->contents[i];
		sprintf(tmp, "%s->%s, ", x.iri, x.path);
		tmp += strlen(tmp);
	}
	sprintf(tmp, ")");
	return ret;
}
