#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "ClipsInfoModelRulemachine1.h"
#include <RIFImporter.h>
#include <RIFImporterDebug.h>
#include <Mime2Rdf4C.h>

const char *datapath = NULL;
const char *basepath = NULL;
const char *baseiri = NULL;

static int parse_args(int argc, char *argv[]);
static int test_two_distinct_atoms(const char* conclusion_data);
static RIFIData* RIFIData_parse_from(const char* conclusion_data);

int main(int argc, char *argv[]){
	int err;
	bool success;
	Environment *env;
	const char* exchange_format = "ttl";
	char* conclusion_data = NULL;
	err = parse_args(argc, argv);
	if (err != 0){
		exit(EXIT_FAILURE);
	}
	env = CreateEnvironment();

	err = InfoModelRulemachine1Data_register(env);
	if (err != 0){
		fprintf(stderr, "Failed to register "
				"InfoModelRulemachine1Data\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "add import: %s->%s\n", baseiri, basepath);
	err = InfoModelRulemachine1Data_add_local_import_location(env, baseiri, basepath);
	if (err != 0){
		fprintf(stderr, "Failed to add local import location\n");
		exit(EXIT_FAILURE);
	}
	Load(env, datapath);
	Reset(env);
	Run(env, -1);
	Eval(env, "(println \"print facts:\" (facts))", NULL);
	conclusion_data = InfoModelRulemachine1Data_export_rif_data(env, exchange_format);
	fprintf(stderr, "Conclusion data:\n%s\n", conclusion_data);
	DestroyEnvironment(env);
	err = test_two_distinct_atoms(conclusion_data);
	free(conclusion_data);
	switch(err){
		case 0:
			exit(EXIT_SUCCESS);
		case 1:
			fprintf(stderr, "failed to find 2 distinct atoms in conclusion data.\n");
			exit(EXIT_FAILURE);
		default:
			fprintf(stderr, "test_two_distinct_atoms failed with unknwon error\n");
			exit(EXIT_FAILURE);
	}
}

static RIFIData* RIFIData_parse_from(const char* conclusion_data){
	int err;
	RIFIData* data;
	RIFIGraph* graph;
	Mime2Rdf4C_ParserConfig* config;

	config = Mime2Rdf4C_get_parser_from_ext("ttl");
	graph = RIFIGraph_new();
	if (graph == NULL){
		fprintf(stderr, "Failed to initialize RIFIGraph\n");
		return NULL;
	}
	err = Mime2Rdf4C_parse(conclusion_data, (TripleHandler*) RIFIGraph_add,
					graph, config);
	free_Mime2Rdf4CParserConfig(config);
	data = RIFIGraph_to_RIFIData(graph, NULL); //use RIF entailment
	return data;
}

static int test_two_distinct_atoms(const char* conclusion_data){
	int err;
	int ret;
	RIFIAtom *first, *second, *third;
	RIFIData* data;
	data = RIFIData_parse_from(conclusion_data);
	if (data == NULL){
		fprintf(stderr, "Couldnt parse conclusion data.\n");
		return 3;
	}

	fprintf(stderr, "Try find first atom in conclusion:\n");
	first = RIFIData_get_next_atom_any_args(data, NULL);
	if (first == NULL){
		free_RIFIData(data);
		fprintf(stderr, "no atom found\n");
		return 2;
	}
	fprintf(stderr, "Found first atom:");
	fprintf_RIFIAtom(stderr, first);
	fprintf(stderr, "\n");
	second = RIFIData_get_next_atom_any_args(data, NULL);
	if (second == NULL){
		free_RIFIData(data);
		fprintf(stderr, "missing second atom\n");
		free_RIFIAtom(first);
		return 1;
	}
	fprintf(stderr, "Found second atom:");
	fprintf_RIFIAtom(stderr, second);
	fprintf(stderr, "\n");
	third = RIFIData_get_next_atom_any_args(data, NULL);
	free_RIFIData(data);
	ret = false;
	fprintf(stderr, "TODO: Dont know how to compare 2 local values\n");
	free_RIFIAtom(first);
	free_RIFIAtom(second);
	if (third != NULL){
		fprintf(stderr, "Got third atom. Default to Failure\n");
		fprintf(stderr, "Found third atom:");
		fprintf_RIFIAtom(stderr, third);
		fprintf(stderr, "\n");
		free_RIFIAtom(third);
		return 3;
	}
	return 0;
}


static struct option parse_options[] = {
	{"premise", required_argument, NULL, 'd'},
	{"basepath", required_argument, NULL, 'b'},
	{"baseiri", required_argument, NULL, 'i'},
        {NULL, 0, NULL, 0}
};

static int parse_args(int argc, char *argv[]){
	int err = 0;
	int c = 0;
	int option_index;
	while(c != -1){
		c = getopt_long(argc, argv, "",
				parse_options, &option_index);
		switch(c){
			case -1: //end of arguments
				break;
			case 'd':
				datapath = optarg;
				break;
			case 'b':
				basepath = optarg;
				break;
			case 'i':
				baseiri = optarg;
				break;
			default:
				fprintf(stderr, "unrecognized argument\n");
				err = 1;
				break;
		}
	}
	if (datapath == NULL){
		fprintf(stderr, "no datapath given\n");
		err = 1;
	}
	if (basepath == NULL){
		fprintf(stderr, "no basepath given\n");
		err = 1;
	}
	if (baseiri == NULL){
		fprintf(stderr, "no baseiri given\n");
		err = 1;
	}
	return err;
}
