#pragma once

#include <clips.h>
#include <AdvancedCDatatypesTime.h>

CLIPSValue CLIPSValue_from_Duration(Environment*, Duration);
CLIPSValue CLIPSValue_from_DateTime(Environment*, DateTime);
CLIPSValue CLIPSValue_from_Time(Environment*, Time);
CLIPSValue CLIPSValue_from_Date(Environment*, Date);

CLIPSValue CLIPSValue_from_serialized_Time(Environment*, const char*);
CLIPSValue CLIPSValue_from_serialized_Duration(Environment*, const char*);
CLIPSValue CLIPSValue_from_serialized_DateTime(Environment*, const char*);
CLIPSValue CLIPSValue_from_serialized_Date(Environment*, const char*);
