#pragma once

#include <clips.h>

typedef struct s_DataDescription {
	char* data;
	char* format;
} DataDescription;

int Environment_register_ClipsInfoModelRulemachine1_data_importer(Environment*);
int Environment_add_local_import_location(Environment *env, const char* iri, const char* path);

int Environment_import_from_file(Environment* env, const char* filepath, const char* entailment);
int Environment_import_from_data(Environment* env, const char* data, const char* format, const char* entailment);
int Environment_import_from_iri(Environment* env, const char* iri, const char* entailment);
char* Environment_generate_import_iri_from_path(Environment*, const char* path);
DataDescription Environment_get_import_data_from_iri(Environment*, const char* iri);

bool Environment_is_importable(Environment*, CLIPSValue location);

char* Environment_get_debug_information_for_import(Environment* env);
