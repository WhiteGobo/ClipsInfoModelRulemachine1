#pragma once
#include <clips.h>


typedef struct s_Literal Literal;



Literal* Literal_new(const char* value, const char* datatype);
Literal* Literal_new_langliteral(const char* value, const char* lang);
Literal* Literal_from_CLIPSValue(CLIPSValue);
CLIPSValue Literal_to_CLIPSValue(Environment* env, const Literal* x);

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
