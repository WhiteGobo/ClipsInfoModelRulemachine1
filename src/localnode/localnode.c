#include "ClipsInfoModelRulemachine1_localnode.h"

static Literal* try_Literal_new_localnode(Environment* env, const char* clipsname){
	Literal* ret;
	CLIPSValue cv;
	cv.lexemeValue = CreateSymbol(env, clipsname);
	//Check if symbol already exists
	if(cv.lexemeValue->count > 0){
		return NULL;
	}
	return Literal_from_CLIPSValue(env, cv);
}

Literal* Literal_new_localnode(Environment* env, const char* startvalue){
	Literal *ret;
	char *clipsname;
	clipsname = malloc(strlen(startvalue) + 10);
	sprintf(clipsname, "_:%s", startvalue);
	ret = try_Literal_new_localnode(env, clipsname);
	if (ret != NULL){
		free(clipsname);
		return ret;
	}
	for(size_t i=0; i<1000; i++){
		sprintf(clipsname, "_:%s_%d", startvalue, i);
		ret = try_Literal_new_localnode(env, clipsname);
		if (ret != NULL){
			free(clipsname);
			return ret;
		}
	}
	free(clipsname);
	fprintf(stderr, "ERROR failed to find new local "
			"nodename for %s\n", startvalue);
	return NULL;
}
