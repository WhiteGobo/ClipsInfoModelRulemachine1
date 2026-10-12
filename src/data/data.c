#include "data.h"
//#include "ClipsInfoModelRulemachine1.h"
#include "extractor.h"
#include "shared_information.h"

static int put_term_at_slot(Environment*, FactBuilder*, const char* slotname, RIFITerm*, IMR1ImportContext*);
static int put_termlist_at_slot(Environment*, FactBuilder*, const char* slotname, RIFITermList*, IMR1ImportContext*);

/**
 * returns 0 on success.
 */
int CIMR1_assert_frame(Environment *env, RIFIFrame* frame, IMR1ImportContext* cntxt)
{
	int err;
        FactBuilderError error;
        Fact *factaddress;
        FactBuilder *theFB;
        theFB = CreateFactBuilder(env, FRAMETEMPLATE);
	err = put_term_at_slot(env, theFB, FRAMESLOTOBJECT, frame->object, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
	err = put_term_at_slot(env, theFB, FRAMESLOTSLOTKEY, frame->slotkey, cntxt);
	if (err != 0){
		FBDispose(theFB);
		return 1;
	}
	err = put_term_at_slot(env, theFB, FRAMESLOTSLOTVALUE, frame->slotvalue, cntxt);
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
}



/**
 * returns 0 on success.
 */
int CIMR1_assert_atom(Environment *env, RIFIAtom* atom, IMR1ImportContext* cntxt)
{
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
}


/**
 * returns 0 on success.
 */
int CIMR1_assert_member(Environment *env, RIFIMember* member, IMR1ImportContext* cntxt)
{
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
}

/**
 * returns 0 on success.
 */
int CIMR1_assert_subclass(Environment *env, RIFISubclass* subclass, IMR1ImportContext* cntxt)
{
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
}

/**
 * returns 0 on success.
 */
int CIMR1_assert_equal(Environment *env, RIFIEqual* equal, IMR1ImportContext* cntxt)
{
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


static int put_termlist_at_slot(Environment* env, FactBuilder* theFB, const char* slotname, RIFITermList* termlist, IMR1ImportContext* cntxt)
{
	size_t length = 0;
	MultifieldBuilder* multifield_builder;
	Multifield* termlist_cv;
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
			return 1;
		}
		MBAppend(multifield_builder, &tmp_cv);
	}
	termlist_cv = MBCreate(multifield_builder);
	MBDispose(multifield_builder);
        FBPutSlotMultifield(theFB, slotname, termlist_cv);
	return 0;
}
