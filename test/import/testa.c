#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <ClipsInfoModelRulemachine1.h>
#include <ClipsInfoModelRulemachine1_data_importer.h>
const char* iri1 = "http://example.com/custom/base";
const char* path1 = "/a/b/c";

int main(int argc, char *argv[]){
	int err;
	Environment *env;

	env = CreateEnvironment();
	err = InfoModelRulemachine1Data_register(env);
	if (err != 0){
		fprintf(stderr, "Failed to register "
				"InfoModelRulemachine1Data\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "add import: %s->%s\n", iri1, path1);
	err = InfoModelRulemachine1Data_add_local_import_location(env,
			"http://example.com/custom/base",
			"/a/b/c");
	if (err != 0){
		fprintf(stderr, "Failed to add local import location\n");
		exit(EXIT_FAILURE);
	}

	char* as_iri = Environment_generate_import_iri_from_path(env,
			"/a/b/c/path/to/file");
	if(as_iri == NULL){
		fprintf(stderr, "Failed to generate iri from path"
				"(Environment_generate_import_iri_from_path)\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "generated iri: %s\n", as_iri);
	err = strcmp(as_iri, "http://example.com/custom/base/path/to/file");
	free(as_iri);
	if(err != 0){
		fprintf(stderr, "generated unexpected iri(http://example.com/"
				"custom/base/path/to/file)\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
