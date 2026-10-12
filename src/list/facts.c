#include "ClipsInfoModelRulemachine1_list.h"
#include "ClipsInfoModelRulemachine1_externaladdress.h"
#include "shared_information.h"

Multifield* Fact_get_termlist(Environment* env, Fact* fact){
	CLIPSValue cv_tmp;
	//Ignore fact template name and just query for "items"
	switch(GetFactSlot(fact, ATOMLISTSLOTITEMS, &cv_tmp)){
		case GSE_NO_ERROR:
			break;
		case GSE_NULL_POINTER_ERROR:
		case GSE_INVALID_TARGET_ERROR:
		case GSE_SLOT_NOT_FOUND_ERROR:
			return NULL;
	}
	switch(cv_tmp.header->type){
		case MULTIFIELD_TYPE:
			return cv_tmp.multifieldValue;
		default:
			fprintf(stderr, "ERROR Termlist got slot for items but "
					"there was no multifield but another "
					"Clipsvalue type found\n");
			return NULL;
	}
}

/*
 * TODO: rename
 */
Fact* CLIPSValue_new_termlist_as_fact(Environment* env, Multifield* items, CLIPSValue rest)
{
	Fact* ret;
        FactBuilderError error;
        FactBuilder *theFB;

	if(items == NULL) return NULL;
        theFB = CreateFactBuilder(env, ATOMLISTTEMPLATE);
	FBPutSlotMultifield(theFB, ATOMLISTSLOTITEMS, items);
	//CLIPSValue rest_cv = CLIPSValue_from_RIFITerm(env, rest);
        //FBPutSlot(theFB, ATOMLISTSLOTREST, &rest_cv);
        ret = FBAssert(theFB);
        FBDispose(theFB);
        if (ret == NULL){
		fprintf(stderr, "Failed to translate "
				"RIFITermList to Clips Fact\n");
		/*
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
                }
		*/
        }
        return ret;
}


bool Fact_is_list(Environment *env, Fact* fact){
	Deftemplate *listtempl, *facttempl;
	listtempl = FindDeftemplate(env, ATOMLISTTEMPLATE);
	facttempl = FactDeftemplate(fact);
	if (facttempl == listtempl){
		return true;
	}
	return false;
}

