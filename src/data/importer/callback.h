#pragma once

typedef struct s_CallbackConfig CallbackConfig;

typedef struct s_DataDescription {
	char* data;
	char* format;
} DataDescription;

typedef struct s_Path2Iri {
	char* path;
	char* iri;
} Path2Iri;
typedef struct s_Path2IriArray {
	size_t len;
	Path2Iri* contents;
} Path2IriArray;


CallbackConfig* CallbackConfig_new();
void free_CallbackConfig(CallbackConfig*);

int CallbackConfig_add_local_location(CallbackConfig*, const char* iri, const char* path);
char* CallbackConfig_path2iri(CallbackConfig*, const char* path);
//char* CallbackConfig_iri2path(CallbackConfig*, const char* iri);
DataDescription CallbackConfig_get_data(CallbackConfig*, const char* iri);
void release_DataDescription(DataDescription);

Path2IriArray* CallbackConfig_get_all_path2iri(CallbackConfig*);
void free_Path2IriArray(Path2IriArray*);

void fprintf_CallbackConfig(FILE*, CallbackConfig*);
