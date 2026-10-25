#include "data.h"
//#include "ClipsInfoModelRulemachine1.h"
#include "extractor.h"
#include "shared_information.h"


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


Multifield* Environment_get_frames(Environment* env){
	Multifield* ret;
	size_t capacity;
	MultifieldBuilder *mb;
	mb = CreateMultifieldBuilder(env, capacity);

	Deftemplate *tripletmplt = FindDeftemplate(env, FRAMETEMPLATE);
	for (Fact* f = GetNextFactInTemplate(tripletmplt, NULL); f!= NULL;
			f = GetNextFactInTemplate(tripletmplt, f))
	{
		MBAppendFact(mb, f);
	}

	ret = MBCreate(mb);
	MBDispose(mb);
	return ret;
}

CLIPSValue CLIPSValue_Frame_get_object(Environment* env, CLIPSValue cv){
	CLIPSValue ret;
	switch(cv.header->type){
		case FACT_ADDRESS_TYPE:
			GetFactSlot(cv.factValue, FRAMESLOTOBJECT, &ret);
			break;
		default:
			ret.voidValue = VoidConstant(env);
	}
	return ret;
}

RetFactFrameGetSlot CLIPSValue_Frame_get_slot(Environment* env, CLIPSValue cv){
	RetFactFrameGetSlot ret;
	switch(cv.header->type){
		case FACT_ADDRESS_TYPE:
			GetFactSlot(cv.factValue, FRAMESLOTSLOTKEY, &(ret.key));
			GetFactSlot(cv.factValue, FRAMESLOTSLOTVALUE, &(ret.value));
			break;
		default:
			ret.key.voidValue = VoidConstant(env);
			ret.value.voidValue = VoidConstant(env);
	}
	return ret;
}
