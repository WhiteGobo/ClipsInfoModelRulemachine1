#pragma once

#include <clips.h>
#include <RIFImporter.h>

typedef struct imr1_import_context IMR1ImportContext;

IMR1ImportContext* IMR1ImportContext_new(Environment* env);
void free_IMR1ImportContext(IMR1ImportContext*);
RIFITerm* RIFITerm_from_CLIPSValue(Environment* env, CLIPSValue* val);
RIFITermList* RIFITermList_from_CLIPSMultifield(Environment* env, Multifield *multifield);

CLIPSValue CLIPSValue_from_RIFITerm(Environment* env, IMR1ImportContext* cntxt, const RIFITerm* term);


char* Environment_export_rif_data(Environment *env, const char* format);
char* Environment_export_rdf_data(Environment *env, const char* format);
