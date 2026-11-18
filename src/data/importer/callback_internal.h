#include "callback.h"


typedef struct s_Path2IriList {
	Path2Iri first;
	struct s_Path2IriList* rest;
} Path2IriList;

typedef struct s_CallbackConfig {
	Path2IriList* path2iri_list;
} CallbackConfig;

