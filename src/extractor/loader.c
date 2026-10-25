#include "ClipsInfoModelRulemachine1_extractor.h"
#include <Mime2Rdf4C.h>
#include <RIFImporter.h>

extern int load_RIFIData_into_Environment(RIFIData* data, Environment *env);

int CIMR1_load_data_from_rdf(Environment* env, const char* datastring, const char* dataformat, const char* entailment)
{
	int64_t err;
	Mime2Rdf4C_ParserConfig* parser;

	parser = Mime2Rdf4C_get_parser_from_ext(dataformat);
	if(parser == NULL){
		parser = Mime2Rdf4C_get_parser_from_mediatype(dataformat);
	}
	if(parser == NULL){
		fprintf(stderr, "Couldnt get rdf parser for format %s\n",
				dataformat);
		return 1;
	}

	RIFIGraph* graph = RIFIGraph_new();
	if (graph == NULL){
		free_Mime2Rdf4CParserConfig(parser);
		fprintf(stderr, "Internal Error. RIFIGraph_new failed\n");
		return 1;
	}
	err = Mime2Rdf4C_parse(datastring, (TripleHandler*) RIFIGraph_add, graph, parser);
	free_Mime2Rdf4CParserConfig(parser);
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
