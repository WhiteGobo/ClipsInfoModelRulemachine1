#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <ClipsInfoModelRulemachine1.h>
#include <ClipsInfoModelRulemachine1_data_importer.h>
const char* baseiri = "http://example.com/custom/base/";
const char* loadiri = "http://example.com/custom/base/datac.clp";
const char* basepath = NULL;
const char* expected_data = "(defrule rule1 =>)\n";
const char* expected_format = "clp";
static int parse_args(int argc, char *argv[]);

int main(int argc, char *argv[]){
	int err;
	Environment *env;
	err = parse_args(argc, argv);
	if(err!=0){
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
	err = InfoModelRulemachine1Data_add_local_import_location(env,
			baseiri, basepath);
	if (err != 0){
		fprintf(stderr, "Failed to add local import location\n");
		exit(EXIT_FAILURE);
	}
	DataDescription x = Environment_get_import_data_from_iri(env, loadiri);
	if(x.data == NULL){
		fprintf(stderr, "Failed to load data\n");
		exit(EXIT_FAILURE);
	}
	int ret = EXIT_SUCCESS;
	if(0 != strcmp(x.data, expected_data)){
		fprintf(stderr, "Unexpected data: %s\n", x.data);
		ret = EXIT_FAILURE;
	}
	if(0 != strcmp(x.format, expected_format)){
		fprintf(stderr, "Unexpected format: %s\n", x.format);
		ret = EXIT_FAILURE;
	}
	free(x.data);
	free(x.format);
	exit(ret);
}


static struct option parse_options[] = {
	{"basepath", required_argument, NULL, 'b'},
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
			case 'b':
				basepath = optarg;
				break;
			default:
				fprintf(stderr, "unrecognized argument\n");
				err = 1;
				break;
		}
	}
	if (basepath == NULL){
		fprintf(stderr, "no basepath given\n");
		err = 1;
	}
	return err;
}

