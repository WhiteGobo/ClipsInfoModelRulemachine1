#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "ClipsInfoModelRulemachine1.h"
#include <RIFRDFQuery.h>
#include <cwalk.h>
#include <Mime2Rdf4C.h>

const char *datapath = NULL;
const char *conclusionpath = NULL;
const char *basepath = NULL;
const char *baseiri = NULL;
bool expect = true;

static int parse_args(int argc, char *argv[]);
static char* load_into_memory(const char* filepath);
static int check_data(const char* conclusion_data, const char* format, const char* expected_conclusionpath);
static RIFRDFQuery_Graph* generate_query_graph(const char* expected_conclusionpath);

int main(int argc, char *argv[]){
	bool evaluation_error;
	int err;
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
	fprintf(stderr, "load program\n");
	switch (Load(env, datapath)){
		case LE_NO_ERROR:
			break;
		case LE_OPEN_FILE_ERROR:
			fprintf(stderr, "clips open file error while loading "
					"clips program: %s\n", datapath);
			exit(EXIT_FAILURE);
		case LE_PARSING_ERROR:
			fprintf(stderr, "clips program not parsable\n");
			exit(EXIT_FAILURE);
	}
	fprintf(stderr, "clips reset and run\n");
	Reset(env);
	Run(env, -1);
	if(GetEvaluationError(env)){
		DestroyEnvironment(env);
		fprintf(stderr, "EvaluationError after Run\n");
		exit(EXIT_FAILURE);
	}
	Eval(env, "(println \"print facts:\" (facts))", NULL);
	conclusion_data = InfoModelRulemachine1Data_export_rif_data(env, exchange_format);
	Eval(env, "(println \"print error:\" (get-error))", NULL);
	DestroyEnvironment(env);
	if (conclusion_data == NULL){
		fprintf(stderr, "Failed to extract data from Environment\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "export_rif_data returned:\n%s\n", conclusion_data);
	err = check_data(conclusion_data, exchange_format, conclusionpath);
	free(conclusion_data);
	switch(err){
		case 0:
			if (expect){
				exit(EXIT_SUCCESS);
			} else {
				fprintf(stderr, "expected failure but check\n");
				exit(EXIT_FAILURE);
			}
		case 1:
			if (!expect){
				exit(EXIT_SUCCESS);
			} else {
				fprintf(stderr, "Check query failed.\n");
				exit(EXIT_FAILURE);
			}
		case -2:
			fprintf(stderr, "expected conclusion not found\n");
			exit(EXIT_FAILURE);
		default:
			fprintf(stderr, "check_data failed with "
					"unhandled error\n");
			exit(EXIT_FAILURE);
	}
}

static RIFRDFQuery_Graph* generate_query_graph(const char* expected_conclusionpath)
{
	int err;
	size_t _extlength;
	const char* fileext, *x;
	Mime2Rdf4C_ParserConfig* parser;
	RIFRDFQuery_Graph* ret = NULL;
	char* expected_data;
	if (!cwk_path_get_extension(expected_conclusionpath,
						&x, &_extlength)
	) {
		fprintf(stderr, "expected conclusion is missing extension: %s\n",
				expected_conclusionpath);
		return NULL;
	}
	fileext = x + 1; //skip '.'
	parser = Mime2Rdf4C_get_parser_from_ext(fileext);
	if (parser == NULL){
		fprintf(stderr, "Missing parser for extension '%s'\n", fileext);
		return NULL;
	}
	expected_data = load_into_memory(expected_conclusionpath);
	//ret = RIFRDFQ_Graph_from_data(expected_data, fileext);
	ret = RIFRDFQuery_Graph_new();
	if (ret == NULL){
		fprintf(stderr, "RIFRDFQuery_Graph_new failed\n");
		return NULL;
	}
	err = Mime2Rdf4C_parse(expected_data,
				(TripleHandler*) RIFRDFQuery_Graph_add, ret,
				parser);
	free_Mime2Rdf4CParserConfig(parser);
	free(expected_data);
	if (err != 0){
		fprintf(stderr, "Failed to parse query '%s'\n",
				expected_conclusionpath);
		return NULL;
	}
	return ret;
}

static int check_data(const char* conclusion_data, const char* format, const char* expected_conclusionpath){
	if (conclusion_data == NULL) return -3;
	int is_same;
	const char* expected_format = "ttl"; //TODO: extract from path instead
	RIFRDFQuery_Graph *conclusion_graph, *expected_graph;

	expected_graph = generate_query_graph(expected_conclusionpath);
	if (expected_graph == NULL){
		fprintf(stderr, "Failed to produce expected_graph\n");
		return -1;
	}
	conclusion_graph = RIFRDFQ_Graph_from_data(conclusion_data, format);

	if (conclusion_graph == NULL){
		fprintf(stderr, "Failed to produce conclusion_graph\n");
		free_RIFRDFQuery_Graph(expected_graph);
		return -2;
	}
	is_same = RIFRDFQuery_Graph_query_rif_data(conclusion_graph, expected_graph);
	free_RIFRDFQuery_Graph(conclusion_graph);
	free_RIFRDFQuery_Graph(expected_graph);
	if (is_same == 0){
		return 0;
	} else {
		return 1;
	}
}


static struct option parse_options[] = {
	{"premise", required_argument, NULL, 'd'},
	{"conclusion", required_argument, NULL, 'c'},
	{"basepath", required_argument, NULL, 'b'},
	{"baseiri", required_argument, NULL, 'i'},
	{"expected-failure", no_argument, NULL, 'x'},
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
			case 'x':
				expect = false;
				break;
			case 'd':
				datapath = optarg;
				break;
			case 'c':
				conclusionpath = optarg;
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
	if (conclusionpath == NULL){
		fprintf(stderr, "no conclusionpath given\n");
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
