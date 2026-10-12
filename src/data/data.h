#pragma once

#include <clips.h>
#include "extractor.h"
#include <RIFImporterTermGenerator.h>

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
