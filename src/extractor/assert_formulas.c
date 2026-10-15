#include "extractor.h"
#include "shared_information.h"
#include "data.h"
#include "ClipsInfoModelRulemachine1_localnode.h"

static Multifield* Multifield_from_RIFITermList(Environment* env, RIFITermList*, IMR1ImportContext* cntxt);


/**
 * returns 0 on success.
 */
int CIMR1_assert_frame(Environment *env, RIFIFrame* frame, IMR1ImportContext* cntxt)
{
	CLIPSValue obj_cv, slotkey_cv, slotvalue_cv;
	obj_cv = CLIPSValue_from_RIFITerm(env, cntxt, frame->object);
	slotkey_cv = CLIPSValue_from_RIFITerm(env, cntxt, frame->slotkey);
	slotvalue_cv = CLIPSValue_from_RIFITerm(env, cntxt, frame->slotvalue);
	if (obj_cv.header->type == VOID_TYPE
			|| slotkey_cv.header->type == VOID_TYPE
			|| slotvalue_cv.header->type == VOID_TYPE)
	{
		fprintf(stderr, "ERROR CIMR1_assert_frame "
				"(failed translate to CLIPSValue)\n");
		return 1;
	}
	Fact* f = Fact_new_asserted_frame(env, obj_cv, slotkey_cv, slotvalue_cv);
	if(f != NULL){
		return 0;
	} else {
		fprintf(stderr, "ERROR CIMR1_assert_frame\n");
		return 1;
	}
}



/**
 * returns 0 on success.
 */
int CIMR1_assert_atom(Environment *env, RIFIAtom* atom, IMR1ImportContext* cntxt)
{
	CLIPSValue op_cv;
	Multifield* args;
	op_cv = CLIPSValue_from_RIFITerm(env, cntxt, atom->op);
	args = Multifield_from_RIFITermList(env, atom->args, cntxt);
	if (op_cv.header->type == VOID_TYPE || args == NULL){
		return 1;
	}
	Fact* f = Fact_new_asserted_atom(env, op_cv, args);
	if(f != NULL){
		return 0;
	} else {
		fprintf(stderr, "ERROR CIMR1_assert_atom\n");
		return 1;
	}
}


/**
 * returns 0 on success.
 */
int CIMR1_assert_member(Environment *env, RIFIMember* member, IMR1ImportContext* cntxt)
{
	CLIPSValue instance_cv, class_cv;
	instance_cv = CLIPSValue_from_RIFITerm(env, cntxt, member->instance);
	class_cv = CLIPSValue_from_RIFITerm(env, cntxt, member->class);
	if (instance_cv.header->type == VOID_TYPE
			|| class_cv.header->type == VOID_TYPE)
	{
		return 1;
	}
	Fact* f = Fact_new_asserted_member(env, instance_cv, class_cv);
	if(f != NULL){
		return 0;
	} else {
		fprintf(stderr, "ERROR CIMR1_assert_frame\n");
		return 1;
	}
}

/**
 * returns 0 on success.
 */
int CIMR1_assert_subclass(Environment *env, RIFISubclass* subclass, IMR1ImportContext* cntxt)
{
	CLIPSValue sub_cv, super_cv;
	sub_cv = CLIPSValue_from_RIFITerm(env, cntxt, subclass->sub);
	super_cv = CLIPSValue_from_RIFITerm(env, cntxt, subclass->super);
	if (sub_cv.header->type == VOID_TYPE
			|| super_cv.header->type == VOID_TYPE)
	{
		return 1;
	}
	Fact* f = Fact_new_asserted_subclass(env, sub_cv, super_cv);
	if(f != NULL){
		return 0;
	} else {
		fprintf(stderr, "ERROR CIMR1_assert_subclass\n");
		return 1;
	}
}

/**
 * returns 0 on success.
 */
int CIMR1_assert_equal(Environment *env, RIFIEqual* equal, IMR1ImportContext* cntxt)
{
	CLIPSValue left_cv, right_cv;
	left_cv = CLIPSValue_from_RIFITerm(env, cntxt, equal->left);
	right_cv = CLIPSValue_from_RIFITerm(env, cntxt, equal->right);
	if (left_cv.header->type == VOID_TYPE
			|| right_cv.header->type == VOID_TYPE)
	{
		return 1;
	}
	Fact* f = Fact_new_asserted_equal(env, left_cv, right_cv);
	if(f != NULL){
		return 0;
	} else {
		fprintf(stderr, "ERROR CIMR1_assert_equal\n");
		return 1;
	}
}



static Multifield* Multifield_from_RIFITermList(Environment* env, RIFITermList* termlist, IMR1ImportContext* cntxt){
	size_t length = 0;
	MultifieldBuilder* multifield_builder;
	Multifield* ret;
	RIFITerm* term;
	CLIPSValue tmp_cv;

	for(RIFITermList* tmp = termlist; tmp != NULL; tmp = tmp->rest){
		length += 1;
	}
	multifield_builder = CreateMultifieldBuilder(env, length);
	for(RIFITermList* tmp = termlist; tmp != NULL; tmp = tmp->rest){
		term = termlist->first;
		tmp_cv = CLIPSValue_from_RIFITerm(env, cntxt, term);
		if (tmp_cv.header->type == VOID_TYPE){
			MBDispose(multifield_builder);
			return NULL;
		}
		MBAppend(multifield_builder, &tmp_cv);
	}
	ret = MBCreate(multifield_builder);
	MBDispose(multifield_builder);
	return ret;
}
