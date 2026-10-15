#include "data.h"
//#include "ClipsInfoModelRulemachine1.h"
#include "extractor.h"
#include "shared_information.h"

static int put_term_at_slot(Environment*, FactBuilder*, const char* slotname, RIFITerm*, IMR1ImportContext*);
static int put_termlist_at_slot(Environment*, FactBuilder*, const char* slotname, RIFITermList*, IMR1ImportContext*);


static Multifield* Multifield_from_RIFITermList(Environment* env, RIFITermList*, IMR1ImportContext* cntxt);

Fact* Fact_new_asserted_frame(Environment *env, CLIPSValue obj, CLIPSValue slotkey, CLIPSValue slotvalue){
	Fact* ret;
        FactBuilder* theFB = CreateFactBuilder(env, FRAMETEMPLATE);
        FBPutSlot(theFB, FRAMESLOTOBJECT, &obj);
        FBPutSlot(theFB, FRAMESLOTSLOTKEY, &slotkey);
        FBPutSlot(theFB, FRAMESLOTSLOTVALUE, &slotvalue);
        ret = FBAssert(theFB);
        FBDispose(theFB);
        if (ret == NULL){
        	FactBuilderError error = FBError(env);
                switch (error) {
                        case FBE_NO_ERROR:
                                break;
                        case FBE_NULL_POINTER_ERROR:
                        case FBE_IMPLIED_DEFTEMPLATE_ERROR:
                        case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
                        case FBE_COULD_NOT_ASSERT_ERROR:
                        case FBE_RULE_NETWORK_ERROR:
                        default:
				break;
                }
        }
	return ret;
}

Fact* Fact_new_asserted_atom(Environment *env, CLIPSValue op, Multifield* args){
	Fact* ret;
        FactBuilder* theFB = CreateFactBuilder(env, ATOMTEMPLATE);
        FBPutSlot(theFB, ATOMSLOTOP, &op);
        FBPutSlotMultifield(theFB, ATOMSLOTARGS, args);
        ret = FBAssert(theFB);
        FBDispose(theFB);
	return ret;
}

Fact* Fact_new_asserted_member(Environment *env, CLIPSValue instance, CLIPSValue class){
	Fact* ret;
        FactBuilder* theFB = CreateFactBuilder(env, MEMBERTEMPLATE);
        FBPutSlot(theFB, MEMBERSLOTINSTANCE, &instance);
        FBPutSlot(theFB, MEMBERSLOTCLASS, &class);
        ret = FBAssert(theFB);
        FBDispose(theFB);
	return ret;
}
Fact* Fact_new_asserted_subclass(Environment *env, CLIPSValue sub, CLIPSValue super){
	Fact* ret;
        FactBuilder* theFB = CreateFactBuilder(env, SUBCLASSTEMPLATE);
        FBPutSlot(theFB, SUBCLASSSLOTSUB, &sub);
        FBPutSlot(theFB, SUBCLASSSLOTSUPER, &super);
        ret = FBAssert(theFB);
        FBDispose(theFB);
	return ret;
}
Fact* Fact_new_asserted_equal(Environment *env, CLIPSValue left, CLIPSValue right){
	Fact* ret;
        FactBuilder* theFB = CreateFactBuilder(env, EQUALTEMPLATE);
	if(CLIPSValue_cmp(left, right) < 0){
		FBPutSlot(theFB, EQUALSLOTLEFT, &right);
		FBPutSlot(theFB, EQUALSLOTRIGHT, &left);
	} else {
		FBPutSlot(theFB, EQUALSLOTLEFT, &left);
		FBPutSlot(theFB, EQUALSLOTRIGHT, &right);
	}
        ret = FBAssert(theFB);
        FBDispose(theFB);
	return ret;
}


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
	/*
	int err;
        FactBuilderError error;
        Fact *factaddress;
        FactBuilder *theFB;
        theFB = CreateFactBuilder(env, ATOMTEMPLATE);
	err = put_term_at_slot(env, theFB, ATOMSLOTOP, atom->op, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
	err = put_termlist_at_slot(env, theFB, ATOMSLOTARGS, atom->args, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
        factaddress = FBAssert(theFB);
        FBDispose(theFB);
        if (factaddress == NULL){
                error = FBError(env);
                switch (error) {
                        case FBE_NO_ERROR:
                                break;
                        case FBE_NULL_POINTER_ERROR:
                        case FBE_IMPLIED_DEFTEMPLATE_ERROR:
                        case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
                        case FBE_COULD_NOT_ASSERT_ERROR:
                        case FBE_RULE_NETWORK_ERROR:
                        default:
                                return 1;
                }
        }
        return 0;
	*/
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

	/*
	int err;
        FactBuilderError error;
        Fact *factaddress;
        FactBuilder *theFB;
        theFB = CreateFactBuilder(env, MEMBERTEMPLATE);
	err = put_term_at_slot(env, theFB, MEMBERSLOTINSTANCE, member->instance, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
	err = put_term_at_slot(env, theFB, MEMBERSLOTCLASS, member->class, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
        factaddress = FBAssert(theFB);
        FBDispose(theFB);
        if (factaddress == NULL){
                error = FBError(env);
                switch (error) {
                        case FBE_NO_ERROR:
                                break;
                        case FBE_NULL_POINTER_ERROR:
                        case FBE_IMPLIED_DEFTEMPLATE_ERROR:
                        case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
                        case FBE_COULD_NOT_ASSERT_ERROR:
                        case FBE_RULE_NETWORK_ERROR:
                        default:
                                return 1;
                }
        }
        return 0;
	*/
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
	/*
	int err;
        FactBuilderError error;
        Fact *factaddress;
        FactBuilder *theFB;
        theFB = CreateFactBuilder(env, SUBCLASSTEMPLATE);
	err = put_term_at_slot(env, theFB, SUBCLASSSLOTSUB, subclass->sub, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
	err = put_term_at_slot(env, theFB, SUBCLASSSLOTSUPER, subclass->super, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
        factaddress = FBAssert(theFB);
        FBDispose(theFB);
        if (factaddress == NULL){
                error = FBError(env);
                switch (error) {
                        case FBE_NO_ERROR:
                                break;
                        case FBE_NULL_POINTER_ERROR:
                        case FBE_IMPLIED_DEFTEMPLATE_ERROR:
                        case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
                        case FBE_COULD_NOT_ASSERT_ERROR:
                        case FBE_RULE_NETWORK_ERROR:
                        default:
                                return 1;
                }
        }
        return 0;
	*/
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
	/*
	int err;
        FactBuilderError error;
        Fact *factaddress;
        FactBuilder *theFB;
        theFB = CreateFactBuilder(env, EQUALTEMPLATE);
	err = put_term_at_slot(env, theFB, EQUALSLOTLEFT, equal->left, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
	err = put_term_at_slot(env, theFB, EQUALSLOTRIGHT, equal->right, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
        factaddress = FBAssert(theFB);
        FBDispose(theFB);
        if (factaddress == NULL){
                error = FBError(env);
                switch (error) {
                        case FBE_NO_ERROR:
                                break;
                        case FBE_NULL_POINTER_ERROR:
                        case FBE_IMPLIED_DEFTEMPLATE_ERROR:
                        case FBE_DEFTEMPLATE_NOT_FOUND_ERROR:
                        case FBE_COULD_NOT_ASSERT_ERROR:
                        case FBE_RULE_NETWORK_ERROR:
                        default:
                                return 1;
                }
        }
        return 0;
	*/
}

static int put_term_at_slot(Environment* env, FactBuilder* theFB, const char* slotname, RIFITerm* term, IMR1ImportContext* cntxt)
{
	CLIPSValue term_cv = CLIPSValue_from_RIFITerm(env, cntxt, term);
	if (term_cv.header->type == VOID_TYPE){
		return 1;
	}
	//assign term_cv
        FBPutSlot(theFB, slotname, &term_cv);
	return 0;
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

static int put_termlist_at_slot(Environment* env, FactBuilder* theFB, const char* slotname, RIFITermList* termlist, IMR1ImportContext* cntxt)
{
	Multifield* termlist_cv = Multifield_from_RIFITermList(env, termlist, cntxt);
        FBPutSlotMultifield(theFB, slotname, termlist_cv);
	return 0;
}
