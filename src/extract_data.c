#include "ClipsInfoModelRulemachine1.h"
#include <RIFImporter.h>
#include <Mime2Rdf4C.h>
#include <RIFImporterTermGenerator.h>
#include "extractor.h"
#include "shared_information.h"

#include <RIFImporterDebug.h>

static RIFIData* get_all_data(Environment *env);
static RIFIData* get_frame_data(Environment *env);
static int add_frame_data(Environment *env, RIFIFormulas*);
static int add_equal_data(Environment *env, RIFIFormulas* formulas);
static int add_member_data(Environment *env, RIFIFormulas* formulas);
static int add_subclass_data(Environment *env, RIFIFormulas* formulas);
static int add_atom_data(Environment *env, RIFIFormulas* formulas);
static RIFIFrame* Fact_to_RIFIFrame(Environment* env, Fact*);
static RIFIAtom* Fact_to_RIFIAtom(Environment* env, Fact*);
static RIFISubclass* Fact_to_RIFISubclass(Environment* env, Fact*);
static RIFIMember* Fact_to_RIFIMember(Environment* env, Fact*);
static RIFIEqual* Fact_to_RIFIEqual(Environment* env, Fact*);

char* InfoModelRulemachine1Data_export_rif_data(Environment *env, const char* format){
	int err;
	char* ret;
	RIFIData* data;
	Mime2Rdf4C_SerializerConfig* serializer;

	data = get_all_data(env);
	if (data == NULL){
		fprintf(stderr, "Couldnt extract RIF data from model\n");
		return NULL;
	}

	serializer = Mime2Rdf4C_get_serializer_from_mediatype(format);
	if (serializer == NULL){
		serializer = Mime2Rdf4C_get_serializer_from_ext(format);
		if (serializer == NULL){
			fprintf(stderr, "Failed to find serializer "
					"for format \"%s\"\n", format);
			return NULL;
		}
	}
	err = RIFIData_send_as_rdf(data,
			(TripleHandler*) Mime2Rdf4C_add, serializer);
	ret = Mime2Rdf4C_finish(serializer);
	return ret;
}

char* InfoModelRulemachine1Data_export_rdf_data(Environment *env, const char* format){
	fprintf(stderr, "extract data\n");
	return NULL;
}


static RIFIData* get_all_data(Environment *env){
	fprintf(stderr, "get_all_data\n");
	RIFIFormulas* formulas = RIFIFormulas_new();
	if(0 != add_frame_data(env, formulas)){
		return NULL;
	}
	if(0 != add_atom_data(env, formulas)){
		return NULL;
	}
	if(0 != add_subclass_data(env, formulas)){
		return NULL;
	}
	if(0 != add_member_data(env, formulas)){
		return NULL;
	}
	if(0 != add_equal_data(env, formulas)){
		return NULL;
	}
	return RIFIFormulas_to_RIFIData(formulas);
}

static RIFIData* get_frame_data(Environment *env){
	RIFIFormulas* formulas = RIFIFormulas_new();
	if(0 != add_frame_data(env, formulas)){
		return NULL;
	}
	return RIFIFormulas_to_RIFIData(formulas);
}

static RIFIFrame* Fact_to_RIFIFrame(Environment* env, Fact* fact){
	RIFIFrame* ret;
	RIFITerm *object, *slotkey, *slotvalue;
	CLIPSValue tmpValue;
	GetFactSlot(fact, FRAMESLOTOBJECT, &tmpValue);
	object = RIFITerm_from_CLIPSValue(env, &tmpValue);
	GetFactSlot(fact, FRAMESLOTSLOTKEY, &tmpValue);
	slotkey = RIFITerm_from_CLIPSValue(env, &tmpValue);
	GetFactSlot(fact, FRAMESLOTSLOTVALUE, &tmpValue);
	slotvalue = RIFITerm_from_CLIPSValue(env, &tmpValue);
	if(object == NULL || slotkey == NULL || slotvalue == NULL){
		free_RIFITerm(object);
		free_RIFITerm(slotkey);
		free_RIFITerm(slotvalue);
		return NULL;
	}
	ret = malloc(sizeof(RIFIFrame));
	ret->object = object;
	ret->slotkey = slotkey;
	ret->slotvalue = slotvalue;
	return ret;
}

static RIFIAtom* Fact_to_RIFIAtom(Environment* env, Fact* fact){
	RIFIAtom* ret;
	RIFITerm *op;
	RIFITermList *args = NULL;
	CLIPSValue tmpValue;
	GetFactSlot(fact, ATOMSLOTOP, &tmpValue);

	op = RIFITerm_from_CLIPSValue(env, &tmpValue);
	if (op == NULL){
		fprintf(stderr, "Failed to get op from Atom"
				"(Fact_to_RIFIAtom)\n");
		return NULL;
	}
	GetFactSlot(fact, ATOMSLOTARGS, &tmpValue);
	if (tmpValue.header->type == MULTIFIELD_TYPE){
		args = RIFITermList_from_CLIPSMultifield(env, tmpValue.multifieldValue);
	} else {
		fprintf(stderr, "ClipsInfoModelRulemachine1 internal error; "
				"Atom args didnt returned multifield\n");
		return NULL;
	}

	ret = malloc(sizeof(RIFIAtom));
	ret->op = op;
	ret->args = args;
	return ret;
}

static RIFISubclass* Fact_to_RIFISubclass(Environment* env, Fact* fact){
	RIFISubclass *ret;
	RIFITerm *sub, *super;
	CLIPSValue tmpValue;
	GetFactSlot(fact, SUBCLASSSLOTSUB, &tmpValue);
	sub = RIFITerm_from_CLIPSValue(env, &tmpValue);
	GetFactSlot(fact, SUBCLASSSLOTSUPER, &tmpValue);
	super = RIFITerm_from_CLIPSValue(env, &tmpValue);
	if(sub == NULL || super == NULL){
		free_RIFITerm(sub);
		free_RIFITerm(super);
		return NULL;
	}
	ret = malloc(sizeof(RIFISubclass));
	ret->sub = sub;
	ret->super = super;
	return ret;
}

static RIFIMember* Fact_to_RIFIMember(Environment* env, Fact* fact){
	RIFIMember *ret;
	RIFITerm *instance, *class;
	CLIPSValue tmpValue;
	GetFactSlot(fact, MEMBERSLOTINSTANCE, &tmpValue);
	instance = RIFITerm_from_CLIPSValue(env, &tmpValue);
	GetFactSlot(fact, MEMBERSLOTCLASS, &tmpValue);
	class = RIFITerm_from_CLIPSValue(env, &tmpValue);
	if(instance == NULL || class == NULL){
		free_RIFITerm(instance);
		free_RIFITerm(class);
		return NULL;
	}
	ret = malloc(sizeof(RIFIMember));
	ret->instance = instance;
	ret->class = class;
	return ret;
}

static RIFIEqual* Fact_to_RIFIEqual(Environment* env, Fact* fact){
	RIFIEqual *ret;
	RIFITerm *left, *right;
	CLIPSValue tmpValue;
	GetFactSlot(fact, EQUALSLOTLEFT, &tmpValue);
	left = RIFITerm_from_CLIPSValue(env, &tmpValue);
	GetFactSlot(fact, EQUALSLOTRIGHT, &tmpValue);
	right = RIFITerm_from_CLIPSValue(env, &tmpValue);
	if(left == NULL || right == NULL){
		free_RIFITerm(left);
		free_RIFITerm(right);
		return NULL;
	}
	ret = malloc(sizeof(RIFIEqual));
	ret->left = left;
	ret->right = right;
	return ret;
}

static int add_frame_data(Environment *env, RIFIFormulas* formulas){
	CLIPSValue tmpValue;
	Deftemplate *tripletmplt = FindDeftemplate(env, FRAMETEMPLATE);
	RIFIFrame* tmpframe;
	for (Fact* f = GetNextFactInTemplate(tripletmplt, NULL); f!= NULL;
			f = GetNextFactInTemplate(tripletmplt, f))
	{
		tmpframe = Fact_to_RIFIFrame(env, f);
		if (tmpframe == NULL) {
			fprintf(stderr, "couldnt convert fact to frame\n");
			return 1;
		}
		RIFIFormulas_add_frame(formulas, tmpframe);
		free_RIFIFrame(tmpframe);
	}
	return 0;
}

static int add_atom_data(Environment *env, RIFIFormulas* formulas){
	CLIPSValue tmpValue;
	Deftemplate *tripletmplt = FindDeftemplate(env, ATOMTEMPLATE);
	RIFIAtom* tmpatom;
	for (Fact* f = GetNextFactInTemplate(tripletmplt, NULL); f!= NULL;
			f = GetNextFactInTemplate(tripletmplt, f))
	{
		tmpatom = Fact_to_RIFIAtom(env, f);
		if (tmpatom == NULL) {
			fprintf(stderr, "couldnt convert fact to atom\n");
			return 1;
		}
		RIFIFormulas_add_atom(formulas, tmpatom);
		free_RIFIAtom(tmpatom);
	}
	return 0;
}

static int add_subclass_data(Environment *env, RIFIFormulas* formulas){
	CLIPSValue tmpValue;
	Deftemplate *tripletmplt = FindDeftemplate(env, SUBCLASSTEMPLATE);
	RIFISubclass* tmpsubclass;
	for (Fact* f = GetNextFactInTemplate(tripletmplt, NULL); f!= NULL;
			f = GetNextFactInTemplate(tripletmplt, f))
	{
		tmpsubclass = Fact_to_RIFISubclass(env, f);
		if (tmpsubclass == NULL) {
			fprintf(stderr, "couldnt convert fact to subclass\n");
			return 1;
		}
		RIFIFormulas_add_subclass(formulas, tmpsubclass);
		free_RIFISubclass(tmpsubclass);
	}
	return 0;
}

static int add_member_data(Environment *env, RIFIFormulas* formulas){
	CLIPSValue tmpValue;
	Deftemplate *tripletmplt = FindDeftemplate(env, MEMBERTEMPLATE);
	RIFIMember* tmpmember;
	for (Fact* f = GetNextFactInTemplate(tripletmplt, NULL); f!= NULL;
			f = GetNextFactInTemplate(tripletmplt, f))
	{
		tmpmember = Fact_to_RIFIMember(env, f);
		if (tmpmember == NULL) {
			fprintf(stderr, "couldnt convert fact to member\n");
			return 1;
		}
		RIFIFormulas_add_member(formulas, tmpmember);
		free_RIFIMember(tmpmember);
	}
	return 0;
}


static int add_equal_data(Environment *env, RIFIFormulas* formulas){
	CLIPSValue tmpValue;
	Deftemplate *tripletmplt = FindDeftemplate(env, EQUALTEMPLATE);
	RIFIEqual* tmpequal;
	for (Fact* f = GetNextFactInTemplate(tripletmplt, NULL); f!= NULL;
			f = GetNextFactInTemplate(tripletmplt, f))
	{
		tmpequal = Fact_to_RIFIEqual(env, f);
		if (tmpequal == NULL) {
			fprintf(stderr, "couldnt convert fact to equal\n");
			return 1;
		}
		RIFIFormulas_add_equal(formulas, tmpequal);
		free_RIFIEqual(tmpequal);
	}
	return 0;
}
