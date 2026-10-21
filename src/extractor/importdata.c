#include "shared_information.h"
#include "extractor.h"

char* Environment_get_debug_information_import(Environment* env){
	char* ret, *tmp;
	size_t len;
	InfoModelRulemachine1Data* cntxt = LoadingInfoModelRulemachine1Data(env);
	if(cntxt == NULL){
		return NULL;
	}
	ImportLocation* import_locations = cntxt->import_locations;
	len = 0;
	for (ImportLocation* x = import_locations; x != NULL; x = x->next){
		len += strlen(x->path) + strlen(x->iri) + 5;
	}
	ret = malloc(len+1 + sizeof("Importlocations: "));
	if (ret == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
		return NULL;
	}
	tmp = ret;
	for (ImportLocation* x = import_locations; x != NULL; x = x->next){
		sprintf(tmp, "%s->%s; ");
		tmp += strlen(x->path) + strlen(x->iri) + 3;
	}
	return ret;
}
