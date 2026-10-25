#pragma once

#include <clips.h>
#include <RIFImporter.h>

typedef struct imr1_import_context IMR1ImportContext;

IMR1ImportContext* IMR1ImportContext_new(Environment* env);
void free_IMR1ImportContext(IMR1ImportContext*);
RIFITerm* RIFITerm_from_CLIPSValue(Environment* env, CLIPSValue* val);
RIFITermList* RIFITermList_from_CLIPSMultifield(Environment* env, Multifield *multifield);
char* Environment_get_debug_information_import(Environment*);

CLIPSValue CLIPSValue_from_RIFITerm(Environment* env, IMR1ImportContext* cntxt, const RIFITerm* term);

int CIMR1_load_data_from_rdf(Environment*, const char* data, const char* dataformat, const char* entailment);

int relative_import(Environment* env, const char* filepath, const char* entailment);

char* Environment_export_rif_data(Environment *env, const char* format);
char* Environment_export_rdf_data(Environment *env, const char* format);
