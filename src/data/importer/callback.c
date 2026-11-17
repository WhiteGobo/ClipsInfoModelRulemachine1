#include "ClipsInfoModelRulemachine1_data_importer.h"
#include "callback.h"
#include <cwalk.h>

typedef struct s_Path2IriList {
	Path2Iri first;
	struct s_Path2IriList* rest;
} Path2IriList;

typedef struct s_CallbackConfig {
	Path2IriList* path2iri_list;
} CallbackConfig;

static Path2IriList* Path2IriList_insert(Path2IriList*, const char* path, const char* iri);
static void free_Path2IriList(Path2IriList*);

CallbackConfig* CallbackConfig_new(){
	CallbackConfig* ret = malloc(sizeof(CallbackConfig));
	if(ret == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
		return NULL;
	}
	ret->path2iri_list = NULL;
	return ret;
}

void free_CallbackConfig(CallbackConfig* x){
	if(x == NULL) return;
	free_Path2IriList(x->path2iri_list);
	free(x);
}

int CallbackConfig_add_local_location(CallbackConfig* cfg, const char* iri, const char* path){
	if(cfg == NULL || iri == NULL || path == NULL){
		fprintf(stderr, "brubru\n");
		return 1;
	}
	cfg->path2iri_list = Path2IriList_insert(cfg->path2iri_list, path, iri);
	return 0;
}

static char* Path2Iri_path2iri(Path2Iri*, const char* path, size_t lpath);

char* CallbackConfig_path2iri(CallbackConfig* cfg, const char* path){
	char* ret;
	size_t lpath = strlen(path);
	for(Path2IriList* x = cfg->path2iri_list; x != NULL; x = x->rest){
		ret = Path2Iri_path2iri(&(x->first), path, lpath);
		if(ret != NULL){
			return ret;
		}
	}
	return NULL;
}

static char* Path2Iri_path2iri(Path2Iri* path2iri, const char* path, size_t lpath)
{
	size_t lret;
	char* ret;
	int tmpi;
	size_t lbasepath = strlen(path2iri->path);
	if(lbasepath > lpath){
		return NULL;
	}
	if(0 != memcmp(path2iri->path, path, lbasepath)){
		return NULL;
	}
	//We expect that path2iri->path and path2iri->iri ends with a separator
	lret = strlen(path2iri->iri) + lpath - lbasepath + 1;
	ret = malloc(lret + 1);
	if(ret == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
	}
	sprintf(ret, "%s%s", path2iri->iri, path+lbasepath);
	return ret;
}


DataDescription CallbackConfig_get_data(CallbackConfig*, const char* iri){
	DataDescription ret = {.data= NULL, .format=NULL};
	fprintf(stderr, "CallbackConfig_get_data not implemented\n");
	return ret;
}


void release_DataDescription(DataDescription x){
	if(x.data != NULL){
		free(x.data);
	}
	if(x.format != NULL){
		free(x.format);
	}
}

Path2IriArray* CallbackConfig_get_all_path2iri(CallbackConfig* cfg){
	Path2IriArray* ret = malloc(sizeof(Path2IriArray));
	size_t len = 0;
	for(Path2IriList* x = cfg->path2iri_list; x != NULL; x = x->rest){
		len += 1;
	}
	ret->len = len;
	ret->contents = malloc(sizeof(Path2IriArray) * len);
	size_t i = 0;
	for(Path2IriList* x = cfg->path2iri_list; x != NULL; x = x->rest){
		ret->contents[i].path = malloc(strlen(x->first.path) + 1);
		strcpy(ret->contents[i].path, x->first.path);
		ret->contents[i].iri = malloc(strlen(x->first.iri) + 1);
		strcpy(ret->contents[i].iri, x->first.iri);
		i+=1;
	}
	return ret;
}

void free_Path2IriArray(Path2IriArray* x){
	if(x == NULL) return;
	for(size_t i=0; i< x->len;i++){
		free(x->contents[i].path);
		free(x->contents[i].iri);
	}
	free(x);
}

static Path2IriList* Path2IriList_insert(Path2IriList* rest, const char* path, const char* iri){
	Path2IriList* ret = malloc(sizeof(Path2IriList));
	if(ret == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
		return NULL;
	}
	ret->first.path = malloc(strlen(path) + 1);
	strcpy(ret->first.path, path);
	ret->first.iri = malloc(strlen(iri) + 1);
	strcpy(ret->first.iri, iri);
	ret->rest = rest;
	return ret;
}

static void free_Path2IriList(Path2IriList* x){
	Path2IriList* rest;
	while(x != NULL){
		rest = x->rest;
		free(x->first.path);
		free(x->first.iri);
		free(x);
		x = rest;
	}
}

void fprintf_CallbackConfig(FILE* f, CallbackConfig* x){
	fprintf(f, "CallbackConfig(");
	for(Path2IriList* pi = x->path2iri_list; pi != NULL; pi=pi->rest){
		fprintf(f, "%s->%s, ", pi->first.iri, pi->first.path);
	}
	fprintf(f, ")");
}
