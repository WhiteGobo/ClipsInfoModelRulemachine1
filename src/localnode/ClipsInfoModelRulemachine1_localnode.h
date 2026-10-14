#pragma once

#include <clips.h>
//#include "ClipsInfoModelRulemachine1_literals.h"
#include "literals.h"

bool CLIPSValue_is_localnode(CLIPSValue);
const char* CLIPSValue_get_localnode_id(CLIPSValue);

CLIPSValue CLIPSValue_new_localnode(Environment*);

typedef struct s_CLIPSValueMap CLIPSValueMap;

CLIPSValueMap* CLIPSValueMap_new(Environment*);
void free_CLIPSValueMap(CLIPSValueMap*);
CLIPSValue CLIPSValueMap_get_localnode(CLIPSValueMap*, const char* id);

Literal* Literal_new_localnode(Environment* env, const char* startvalue);
