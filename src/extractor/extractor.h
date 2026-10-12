#pragma once

#include <clips.h>
#include <RIFImporter.h>

typedef struct imr1_import_context IMR1ImportContext;

IMR1ImportContext* IMR1ImportContext_new(Environment* env);
void free_IMR1ImportContext(IMR1ImportContext*);
RIFITerm* RIFITerm_from_CLIPSValue(Environment* env, CLIPSValue* val);
RIFITermList* RIFITermList_from_CLIPSMultifield(Environment* env, Multifield *multifield);

CLIPSValue CLIPSValue_from_RIFITerm(Environment* env, IMR1ImportContext* cntxt, const RIFITerm* term);

void CIMR1_import_rdf(Environment *env, UDFContext *udfc, UDFValue *out);
