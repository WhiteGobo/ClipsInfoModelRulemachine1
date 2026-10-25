#pragma once

#include <clips.h>
#include "extractor.h"
#include <RIFImporterTermGenerator.h>

int CLIPSValue_cmp(CLIPSValue x, CLIPSValue y);
typedef struct s_RetFactFrameGetSlot {
	CLIPSValue key;
	CLIPSValue value;
} RetFactFrameGetSlot;

Fact* Fact_new_asserted_frame(Environment *env, CLIPSValue obj, CLIPSValue slotkey, CLIPSValue slotvalue);
Fact* Fact_new_asserted_atom(Environment *env, CLIPSValue op, Multifield* args);
Fact* Fact_new_asserted_member(Environment *env, CLIPSValue instance, CLIPSValue class);
Fact* Fact_new_asserted_subclass(Environment *env, CLIPSValue sub, CLIPSValue super);
Fact* Fact_new_asserted_equal(Environment *env, CLIPSValue left, CLIPSValue right);


Multifield* Environment_get_frames(Environment*);
CLIPSValue CLIPSValue_Frame_get_object(Environment*, CLIPSValue);
RetFactFrameGetSlot CLIPSValue_Frame_get_slot(Environment*, CLIPSValue);
