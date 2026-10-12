#include "ClipsInfoModelRulemachine1.h"
#include "shared_information.h"
#include "external_functions.h"

bool load_basic_templates(Environment *env);

static bool InfoModelRulemachine1Data_initialize(InfoModelRulemachine1Data *data);
static void InfoModelRulemachine1Data_release(Environment *env);

int InfoModelRulemachine1Data_add_local_import_location(Environment *env, const char* iri, const char* path){
	ImportLocation* x;
	if (iri == NULL) {
		fprintf(stderr, "InfoModelRulemachine1Data_add_local_import"
				"_location failed because no iri was given\n");
		return 1;
	}
	if (path == NULL) {
		fprintf(stderr, "InfoModelRulemachine1Data_add_local_import"
				"_location failed because no path was given\n");
		return 1;
	}
	InfoModelRulemachine1Data *data;
	ImportLocation* loc = ImportLocation_new(iri, path);
	if (loc == NULL) {
		fprintf(stderr, "Internal Error: ImportLocation_new failed\n");
		return 1;
	}
	data = LoadingInfoModelRulemachine1Data(env);
	if (data->import_locations == NULL){
		data->import_locations = loc;
	} else {
		ImportLocation_append(data->import_locations, loc);
	}
	return 0;
}

ImportLocation* ImportLocation_new(const char* iri, const char* path){
	if(iri == NULL || path == NULL) return NULL;
	ImportLocation* new = malloc(sizeof(ImportLocation));
	new->iri = malloc(strlen(iri) + 1);
	strcpy(new->iri, iri);
	new->path = malloc(strlen(path) + 1);
	strcpy(new->path, path);
	new->next = NULL;
	return new;
}

int ImportLocation_append(ImportLocation* first, ImportLocation* new){
	if (first == NULL) return 1;
	ImportLocation* x = first;
	while (x->next != NULL){
		x = x->next;
	}
	x->next = new;
	return 0;
}

void free_ImportLocation(ImportLocation* x){
	if (x == NULL) return;
	free_ImportLocation(x->next);
	free(x->iri);
	free(x->path);
	free(x);
}

/*int InfoModelRulemachine1Data_set_basepath(Environment *env, const char* path){
	if (path == NULL) return 1;
	InfoModelRulemachine1Data *data;
	data = LoadingInfoModelRulemachine1Data(env);
	data->basepath = malloc(strlen(path)+1);
	strcpy(data->basepath, path);
	return 0;
}*/


int InfoModelRulemachine1Data_register(Environment *env){
	bool success;
	InfoModelRulemachine1Data *data;
	if(!load_basic_templates(env)){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	success = AllocateEnvironmentData(env, INFO_MODEL_RULEMACHINE1_INDEX,
					sizeof(InfoModelRulemachine1Data),
					InfoModelRulemachine1Data_release);
	if(!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	data = LoadingInfoModelRulemachine1Data(env);
	success = InfoModelRulemachine1Data_initialize(data);
	if(!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}

	success = add_literal_user_functions(env);
	if(!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	return 0;
}


static bool InfoModelRulemachine1Data_initialize(InfoModelRulemachine1Data *data){
	int err;
	data->import_locations = NULL;
	data->local_prefix_id = 0;
	return true;
}


static void InfoModelRulemachine1Data_release(Environment *env){
	InfoModelRulemachine1Data *data;
	data = LoadingInfoModelRulemachine1Data(env);
	free_ImportLocation(data->import_locations);
}
