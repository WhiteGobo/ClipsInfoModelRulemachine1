#include "reroute2stderr.h"

static bool myquery(Environment*, const char* logicalName, void* cntxt);
static void mywrite(Environment*, const char *logicalName, const char *str, void *cntxt);
static void myexit(Environment*, int exitCode, void *cntxt);

void reroute2stderr(Environment* env, FILE* fp){
	AddRouter(env, "reroute2stderr", 20,
			myquery, mywrite, NULL, NULL, myexit, fp);
}

static bool myquery(Environment*, const char* logicalName, void* cntxt)
{
	if (strcmp(logicalName, STDERR) == 0){
	       return true;
	} else if (strcmp(logicalName, STDOUT) == 0){
	       return true;
	}
	return false;
}

static void mywrite(Environment*, const char *logicalName, const char *str, void *cntxt)
{
	FILE *fp = (FILE *) cntxt;
	fprintf(fp, "%s", str);
}

static void myexit(Environment*, int exitCode, void *cntxt){
}
