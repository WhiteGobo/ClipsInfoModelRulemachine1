#include <clips.h>
#include "extractor.h"
#include <Mime2Rdf4C.h>
#include <cwalk.h>
#include "shared_information.h"
#include <DataloaderRDF.h>
#include "data.h"
#include <RIFImporterDebug.h>

static char* load_into_memory(const char* filepath);
extern int load_RIFIData_into_Environment(RIFIData* data, Environment *env);
static RIFIData* RIFIData_load(const char* filepath, const char* entailment);

extern int CIMR1_assert_frame(Environment *env, RIFIFrame* frame, IMR1ImportContext* cntxt);
extern int CIMR1_assert_atom(Environment *env, RIFIAtom* atom, IMR1ImportContext* cntxt);
extern int CIMR1_assert_member(Environment *env, RIFIMember* member, IMR1ImportContext* cntxt);
extern int CIMR1_assert_subclass(Environment *env, RIFISubclass* subclass, IMR1ImportContext* cntxt);
extern int CIMR1_assert_equal(Environment *env, RIFIEqual* equal, IMR1ImportContext* cntxt);



int relative_import(Environment* env, const char* filepath, const char* entailment)
{
	InfoModelRulemachine1Data* cntxt = LoadingInfoModelRulemachine1Data(env);
	if(cntxt == NULL){
		return 1;
	}
	ImportLocation* import_locations = cntxt->import_locations;
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


int load_RIFIData_into_Environment(RIFIData* data, Environment *env){
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
		switch(err){
			case 0:
				break;
			default:
				fprintf(stderr, "failed to assert frame\n");
				fprintf_RIFIFrame(stderr, q);
				free_RIFIFrame(q);
				return 1;
		}
		free_RIFIFrame(q);
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
