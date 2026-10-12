#pragma once

#include <clips.h>
#include "ClipsInfoModelRulemachine1_list.h"


#ifndef CLIPSPLUGIN_INDEX_CIMR1ExternalAddress
#define CLIPSPLUGIN_INDEX_CIMR1ExternalAddress USER_ENVIRONMENT_DATA + 8
#endif

int register_CIMR1ExternalAddressData(Environment*);
CIMR1List* CVExternalAddress_get_CIMR1List(CLIPSExternalAddress*);

