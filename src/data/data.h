#pragma once

#include <clips.h>
#include "extractor.h"
#include <RIFImporterTermGenerator.h>

int CLIPSValue_cmp(CLIPSValue x, CLIPSValue y);

Fact* Fact_new_asserted_frame(Environment *env, CLIPSValue obj, CLIPSValue slotkey, CLIPSValue slotvalue);
Fact* Fact_new_asserted_atom(Environment *env, CLIPSValue op, Multifield* args);
Fact* Fact_new_asserted_member(Environment *env, CLIPSValue instance, CLIPSValue class);
Fact* Fact_new_asserted_subclass(Environment *env, CLIPSValue sub, CLIPSValue super);
Fact* Fact_new_asserted_equal(Environment *env, CLIPSValue left, CLIPSValue right);

/**
 * returns 0 on success.
 */
int CIMR1_assert_frame(Environment *env, RIFIFrame* frame, IMR1ImportContext* cntxt);

/**
 * returns 0 on success.
 */
int CIMR1_assert_atom(Environment *env, RIFIAtom* atom, IMR1ImportContext* cntxt);

/**
 * returns 0 on success.
 */
int CIMR1_assert_member(Environment *env, RIFIMember* member, IMR1ImportContext* cntxt);

/**
 * returns 0 on success.
 */
int CIMR1_assert_subclass(Environment *env, RIFISubclass* subclass, IMR1ImportContext* cntxt);

/**
 * returns 0 on success.
 */
int CIMR1_assert_equal(Environment *env, RIFIEqual* equal, IMR1ImportContext* cntxt);
