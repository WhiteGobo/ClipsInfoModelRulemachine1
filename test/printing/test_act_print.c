#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "ClipsInfoModelRulemachine1.h"
#include <RIFRDFQuery.h>
#include <cwalk.h>
#include <Mime2Rdf4C.h>

const char* testuri = "http://grep.this/uri#";
const char* testpath = "/grep/this/path/";
static int call_print(Environment*);

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
	err = call_print(env);
	if(err != 0){
		fprintf(stderr, "failed\n");
		exit(EXIT_FAILURE);
	}
	DestroyEnvironment(env);
	//needed for pass_regular_expression
	fprintf(stdout, "pass\n");
	exit(EXIT_SUCCESS);
}

static int call_print(Environment* env){
	const char* testoutput_command =
		"(<http://www.w3.org/2007/rif-builtin-action#print> "
		"(gen-literal \"testoutput§\"))";
	CLIPSValue tmpcv;
	EvalError err;
	err = Eval(env, testoutput_command, &tmpcv);
	switch(err){
		case EE_NO_ERROR:
			return 0;
		case EE_PARSING_ERROR:
			fprintf(stderr, "Failed to parse command :\"%5s\"\n",
					testoutput_command);
			return 1;
		case EE_PROCESSING_ERROR:
			fprintf(stderr, "Failed to process command :\"%5s\"\n",
					testoutput_command);
			return 1;
	}
}
