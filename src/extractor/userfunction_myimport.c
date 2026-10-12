#include <clips.h>
#include "extractor.h"
#include <Mime2Rdf4C.h>
#include <cwalk.h>
#include "shared_information.h"
#include <DataloaderRDF.h>
#include "data.h"

static char* load_into_memory(const char* filepath);
static int relative_import(Environment* env, const ImportLocation* import_locations, const char* filepath, const char* entailment);
static int load_RIFIData_into_Environment(RIFIData* data, Environment *env);
static RIFIData* RIFIData_load(const char* filepath, const char* entailment);

#define RETURNFAIL(failure) \
		crifi_udf_error(env, failure, out);\
		return;


void CIMR1_import_rdf(Environment *env, UDFContext *udfc, UDFValue *out){
	int err;
	InfoModelRulemachine1Data* cntxt;
	bool truth;
	const char* entailment = NULL;
	RIFITerm* location, *entailment_term;
	UDFValue udfinput;
	CLIPSValue clipsinput;
	out->voidValue = VoidConstant(env);
	if (!UDFFirstArgument(udfc, ANY_TYPE_BITS, &udfinput)){
		//RETURNFAIL("Argerror for pred:is-literal-boolean");
		return;
	}
	clipsinput.value = udfinput.value;
	location = RIFITerm_from_CLIPSValue(env, &clipsinput);
	if (location == NULL){
		fprintf(stderr, "myimport couldnt translate "
				"position argument\n");
		return;
	}

	//Check hasnextargument because nextargument halts the run on failure
	if(UDFHasNextArgument(udfc)){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &udfinput)){
			fprintf(stderr, "ClipsInfoModelRulemachine "
					"Internal Error myimport\n");
			Eval(env, "(halt)", NULL);
			return;
		}
		clipsinput.value = udfinput.value;
		entailment_term = RIFITerm_from_CLIPSValue(env, &clipsinput);
		if (entailment_term == NULL){
			fprintf(stderr, "myimport couldnt translate entailment\n");
			return;
		}
		if (entailment_term->type != RIF_IRI){
			fprintf(stderr, "myimport entailment must be iri\n");
			return;
		}
		entailment = entailment_term->value;
	} else {
		entailment_term = NULL;
		entailment = NULL;
	}
	switch(location->type){
		case RIF_IRI:
			fprintf(stderr, "myimport doesnt support iris yet\n");
			//err = iri_import();
			err = 1;
			break;
		case RIF_TypedLiteral:
		case RIF_LangLiteral:
			cntxt = LoadingInfoModelRulemachine1Data(env);
			err = relative_import(env, cntxt->import_locations,
					location->value,
					entailment);
			break;
		default:
			err = 1;
			fprintf(stderr, "myimport got wrong argument type\n");
			return;
	}
	free_RIFITerm(location);
	if (entailment != NULL) free_RIFITerm(entailment_term);
	if (err != 0){
		UDFThrowError(udfc);
	}
}

static int relative_import(Environment* env, const ImportLocation* import_locations, const char* filepath, const char* entailment)
{
	int err;
	DRDFDataloader* dataloader = DRDFDataloader_new();
	if (dataloader == NULL){
		fprintf(stderr, "Failed DRDFDataloader_new\n");
		return 1;
	}
	for (ImportLocation* x = import_locations; x != NULL; x = x->next){
		switch(DRDFDataloader_add_path_iri(dataloader, x->path, x->iri)){
			case 0:
				break;
			default:
				free_DRDFDataloader(dataloader);
				fprintf(stderr, "Internal error. DRDFDataloader_"
						"add_path_iri failed\n");
				return 1;
		}
	}
	RIFIGraph* graph = RIFIGraph_new();
	if (graph == NULL){
		free_DRDFDataloader(dataloader);
		fprintf(stderr, "Internal Error. RIFIGraph_new failed\n");
		return 1;
	}
	err = DRDFDataloader_load_data(dataloader, filepath,
					(TripleHandler*) RIFIGraph_add, graph);
	free_DRDFDataloader(dataloader);
	if (err != 0){
		fprintf(stderr, "Internal Error. "
				"DRDFDataloader_load_data failed\n");
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
	/*
	int err;
	RIFIData* data;
	size_t buffersize;
	size_t qq;
	char* buffer;
	if(!cwk_path_is_relative(filepath)){
		fprintf(stderr, "import with literals support only "
				"relative filepaths. Got %s\n", filepath);
		return 1;
	}
	fprintf(stderr, "relativeimport 00\n");
	buffersize = strlen(basepath) + strlen(filepath) + 2;
	buffer = malloc(buffersize);
	qq = cwk_path_join(basepath, filepath, buffer, buffersize);
	fprintf(stderr, "relative import: %s\n", buffer);
	data = RIFIData_load(buffer, entailment);
	free(buffer);
	fprintf(stderr, "relativeimport 01\n");
	if (data == NULL){
		fprintf(stderr, "failed to import data from %s.\n", buffer);
		return 2;
	}
	fprintf(stderr, "relativeimport 02\n");
	err = load_RIFIData_into_Environment(data, env);
	if(err != 0){
		fprintf(stderr, "Something went wrong during "
				"load_RIFIData_into_environment\n");
	}
	fprintf(stderr, "relativeimport 03\n");
	return err;
	*/
}

static RIFIData* RIFIData_load(const char* filepath, const char* entailment){
	int err;
	RIFIGraph* graph;
	char *tmpinput;
	const char* ext;
	Mime2Rdf4C_ParserConfig* config;
	const char* found_ext;
	size_t ext_length;
	if (!cwk_path_get_extension(filepath, &found_ext, &ext_length)){
		fprintf(stderr, "Couldnt find extension to file \"%s\"\n",
				filepath);
		return NULL;
	}
	config = Mime2Rdf4C_get_parser_from_ext(found_ext + 1);
	tmpinput = load_into_memory(filepath);
	if (tmpinput == NULL){
		fprintf(stderr, "Couldnt find data: %s\n", filepath);
		return NULL;
	}
	fprintf(stderr, "input : %s\n", tmpinput);
	graph = RIFIGraph_new();
	if (graph == NULL){
		fprintf(stderr, "Failed to initialize RIFIGraph\n");
		return NULL;
	}
	err = Mime2Rdf4C_parse(tmpinput, (TripleHandler*) RIFIGraph_add,
					graph, config);
	free_Mime2Rdf4CParserConfig(config);
	free(tmpinput);
	if (err != 0){
		fprintf(stderr, "parsing failed\n");
		return NULL;
	}
	return RIFIGraph_to_RIFIData(graph, entailment);
}



static char* load_into_memory(const char* filepath){
        char *ret;
        long fsize;
        FILE *f = fopen(filepath, "rb");
        if (f == NULL) return NULL;
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        //fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

        ret = malloc(fsize + 1);
        fread(ret, fsize, 1, f);
        ret[fsize] = 0;
        fclose(f);
        return ret;
}


static int load_RIFIData_into_Environment(RIFIData* data, Environment *env){
	int err;
	IMR1ImportContext* cntxt = IMR1ImportContext_new(env);
	if (cntxt==NULL){
		return 1;
	}
	for(RIFIAtom* q = RIFIData_get_next_atom_any_args(data, NULL);
			q != NULL;
			q = RIFIData_get_next_atom_any_args(data, NULL))
	{
		err = CIMR1_assert_atom(env, q, cntxt);
		free_RIFIAtom(q);
		switch(err){
			case 0:
				break;
			default:
				fprintf(stderr, "failed to assert atom\n");
				return 1;
		}
	}
	for(RIFIFrame* q = RIFIData_get_next_frame(data, NULL, NULL, NULL);
			q != NULL;
			q = RIFIData_get_next_frame(data, NULL, NULL, NULL))
	{
		err = CIMR1_assert_frame(env, q, cntxt);
		free_RIFIFrame(q);
		switch(err){
			case 0:
				break;
			default:
				fprintf(stderr, "failed to assert frame\n");
				return 1;
		}
	}
	for(RIFISubclass* q = RIFIData_get_next_subclass(data, NULL, NULL);
			q != NULL;
			q = RIFIData_get_next_subclass(data, NULL, NULL))
	{
		err = CIMR1_assert_subclass(env, q, cntxt);
		free_RIFISubclass(q);
		switch(err){
			case 0:
				break;
			default:
				fprintf(stderr, "failed to assert subclass\n");
				return 1;
		}
	}
	for(RIFIMember* q = RIFIData_get_next_member(data, NULL, NULL);
			q != NULL;
			q = RIFIData_get_next_member(data, NULL, NULL))
	{
		err = CIMR1_assert_member(env, q, cntxt);
		free_RIFIMember(q);
		switch(err){
			case 0:
				break;
			default:
				fprintf(stderr, "failed to assert member\n");
				return 1;
		}
	}
	for(RIFIEqual* q = RIFIData_get_next_equal(data, NULL, NULL);
			q != NULL;
			q = RIFIData_get_next_equal(data, NULL, NULL))
	{
		err = CIMR1_assert_equal(env, q, cntxt);
		free_RIFIEqual(q);
		switch(err){
			case 0:
				break;
			default:
				fprintf(stderr, "failed to assert equal\n");
				return 1;
		}
	}
	free_IMR1ImportContext(cntxt);
	return 0;
}
