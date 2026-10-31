#pragma once
#include <clips.h>


typedef struct s_Literal Literal;

#ifndef RDF_TERMTYPE_DEFINED
#define RDF_TERMTYPE_DEFINED
typedef enum {
        URI = 0,
        BNODE = 1,
        TYPEDLITERAL = 2,
        LANGLITERAL = 3
} TERMTYPE;
#endif


/* TODO rename to Literal_new_typedliteral */
Literal* Literal_new_iri(const char* x, size_t l);
Literal* Literal_new(const char* value, const char* datatype);
Literal* Literal_new_langliteral(const char* value, const char* lang);
Literal* Literal_new_localnode(Environment*, const char* startvalue);
Literal* Literal_from_CLIPSValue(Environment* env, CLIPSValue cv);
CLIPSValue Literal_to_CLIPSValue(Environment* env, const Literal* x);
Literal* UDF_get_nth_as_literal(UDFContext *udfc, unsigned n);

bool Literal_check_value_against_regex(Literal*, const char*);

/*
 * Same as Literal_to_CLIPSValue but dont use special functions for typedliteral
 * but use standard serializer instead
 */
CLIPSValue Literal_to_CLIPSValue_plain(Environment* env, const Literal* x);
bool Literal_equal(const Literal*, const Literal*);
Literal* Literal_cast(const Literal*, const char* datatype);
bool Literal_check_datatype(const Literal*, const char* datatype);
void free_Literal(Literal*);
const char* Literal_get_value(Literal*);
const char* Literal_get_lang(Literal*);
const char* Literal_get_datatype(Literal*);
Environment* Literal_get_environment(Literal*);
TERMTYPE Literal_get_type(Literal*);

void fprintf_Literal(FILE*, const Literal*);
void WriteLiteral(Environment*, const char* logicalName, const Literal*);
