#pragma once

#include <clips.h>

#define EXTRACT_ANY_TERM_SUCCESS(x) (x.value != NULL)
#define EXTRACT_LIST_SUCCESS(x) (x.list != NULL)

#ifndef RDF_TERMTYPE_DEFINED
#define RDF_TERMTYPE_DEFINED
typedef enum {
        URI = 0,
        BNODE = 1,
        TYPEDLITERAL = 2,
        LANGLITERAL = 3
} TERMTYPE;
#endif

typedef struct s_LocalTermMap LocalTermMap;
struct ret_ExtractAnyTerm {
	TERMTYPE type;
	char* value;
	char* suffix;
};
struct ret_ExtractList {
	Multifield* list;
	CLIPSValue rest;
};

LocalTermMap* LocalTermMap_new(Environment*);
void free_LocalTermMap(LocalTermMap*);

CLIPSValue generate_clipssymbol_from_iri(Environment* env, const char* iri);
CLIPSValue generate_clipssymbol_from_local(Environment* env, LocalTermMap* cntxt, const char* name);
CLIPSValue generate_clipsvalue_from_typedliteral(Environment* env, const char* value, const char* type);
CLIPSValue generate_clipsvalue_from_langliteral(Environment* env, const char* value, const char* lang);
CLIPSValue generate_clipsvalue_from_termlist(Environment* env, LocalTermMap* cntxt, Multifield* items, CLIPSValue rest);


/*
 * On failure return value has (.value == NULL)
 */
struct ret_ExtractAnyTerm CLIPSValue_extract_any_term(CLIPSValue*);
struct ret_ExtractList CLIPSValue_extract_list(Environment*, CLIPSValue*);
