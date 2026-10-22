#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "ClipsInfoModelRulemachine1.h"
#include <RIFRDFQuery.h>
#include <cwalk.h>
#include <Mime2Rdf4C.h>

#include "reroute2stderr.h"

const char* testuri = "http://grep.this/uri#";
const char* testpath = "/grep/this/path/";
static int call_failing_import(Environment*);

int main(int argc, char *argv[]){
	int err;
	Environment *env;
	env = CreateEnvironment();
	reroute2stderr(env, stderr);

	err = InfoModelRulemachine1Data_register(env);
	if (err != 0){
		fprintf(stderr, "Failed to register "
				"InfoModelRulemachine1Data\n");
		exit(EXIT_FAILURE);
	}
	err = InfoModelRulemachine1Data_add_local_import_location(env,
			testuri, testpath);
	if (err != 0){
		fprintf(stderr, "Failed to add local import location\n");
		exit(EXIT_FAILURE);
	}

	err = call_failing_import(env);
	if(err != 0){
		exit(EXIT_FAILURE);
	}
	DestroyEnvironment(env);
	exit(EXIT_SUCCESS);
}

static int call_failing_import(Environment* env){
	CLIPSValue tmpcv;
	FunctionCallBuilder *fcb;
	fcb = CreateFunctionCallBuilder(env, 2);
	FCBAppendString(fcb, "http://this.uri/can/never/be/found");
	FCBAppendSymbol(fcb, "<http://www.w3.org/ns/entailment/Simple>");
	FCBCall(fcb, "<http://white.gobo/ClipsInfoModelRulemachine1#import>", &tmpcv);
	FCBDispose(fcb);
	return 0;
}
