#include "udfdescription.h"
#include "literals.h"
#include <AdvancedCDatatypesTime.h>
#include "ClipsInfoModelRulemachine1_number.h"
#include "data.h"
#include "ClipsInfoModelRulemachine1_time.h"

#include "namespace_XS.h"
#include "namespace_FUNC.h"
#include "namespace_PRED.h"

const UDFDescription builtinFunctionList_Formula[];

static void assert_atom(Environment *env, UDFContext *udfc, UDFValue *out);
static void assert_frame(Environment *env, UDFContext *udfc, UDFValue *out);
static void assert_equal(Environment *env, UDFContext *udfc, UDFValue *out);
static void assert_member(Environment *env, UDFContext *udfc, UDFValue *out);
static void assert_subclass(Environment *env, UDFContext *udfc, UDFValue *out);


const UDFDescription builtinFunctionList_Formula[] = {
	{"AssertAtom", "f", 1, UNBOUNDED, "*",
		assert_atom, "assert_atom"},
	{"AssertFrame", "f", 3, 3, "*",
		assert_frame, "assert_frame"},
	{"AssertEqual", "f", 2, 2, "*",
		assert_equal, "assert_equal"},
	{"AssertMember", "f", 2, 2, "*",
		assert_member, "assert_member"},
	{"AssertSubclass", "f", 2, 2, "*",
		assert_subclass, "assert_subclass"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};


static void assert_atom(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact* ret;
	CLIPSValue op_cv;
	unsigned int argcount = UDFArgumentCount(udfc);
	UDFValue tmpudf;
	Multifield* args_mf;
	MultifieldBuilder *mb;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	op_cv.value = tmpudf.value;
	mb = CreateMultifieldBuilder(env, argcount - 1);
	for(unsigned int i = 1; i< argcount; i++){
		if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
			return;
		}
		MBAppendUDFValue(mb, &tmpudf);
	}
	args_mf = MBCreate(mb);
	MBDispose(mb);
	if(args_mf == NULL){
		return;
	}
	ret = Fact_new_asserted_atom(env, op_cv, args_mf);
	if (ret != NULL){
		out->factValue = ret;
	} else {
		fprintf(stderr, "ERROR AssertAtom\n");
		out->voidValue = VoidConstant(env);
	}
}


static void assert_frame(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact* ret;
	CLIPSValue obj_cv, slotkey_cv, slotvalue_cv;
	UDFValue tmpudf;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	obj_cv.value = tmpudf.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	slotkey_cv.value = tmpudf.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	slotvalue_cv.value = tmpudf.value;
	ret = Fact_new_asserted_frame(env, obj_cv, slotkey_cv, slotvalue_cv);
	if (ret != NULL){
		out->factValue = ret;
	} else {
		fprintf(stderr, "ERROR AssertFrame\n");
		out->voidValue = VoidConstant(env);
	}
}


static void assert_equal(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact* ret;
	CLIPSValue left_cv, right_cv;
	UDFValue tmpudf;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	left_cv.value = tmpudf.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	right_cv.value = tmpudf.value;
	ret = Fact_new_asserted_equal(env, left_cv, right_cv);
	if (ret != NULL){
		out->factValue = ret;
	} else {
		fprintf(stderr, "ERROR AssertEqual\n");
		out->voidValue = VoidConstant(env);
	}
}


static void assert_member(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact* ret;
	CLIPSValue instance_cv, class_cv;
	UDFValue tmpudf;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	instance_cv.value = tmpudf.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	class_cv.value = tmpudf.value;
	ret = Fact_new_asserted_member(env, instance_cv, class_cv);
	if (ret != NULL){
		out->factValue = ret;
	} else {
		fprintf(stderr, "ERROR AssertMember\n");
		out->voidValue = VoidConstant(env);
	}
}


static void assert_subclass(Environment *env, UDFContext *udfc, UDFValue *out){
	Fact* ret;
	CLIPSValue sub_cv, super_cv;
	UDFValue tmpudf;
	if(!UDFFirstArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	sub_cv.value = tmpudf.value;
	if(!UDFNextArgument(udfc, ANY_TYPE_BITS, &tmpudf)){
		return;
	}
	super_cv.value = tmpudf.value;
	ret = Fact_new_asserted_subclass(env, sub_cv, super_cv);
	if (ret != NULL){
		out->factValue = ret;
	} else {
		fprintf(stderr, "ERROR AssertSubclass\n");
		out->voidValue = VoidConstant(env);
	}
}
