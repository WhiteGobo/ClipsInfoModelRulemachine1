#include "extractor.h"
#include "shared_information.h"
#include "ClipsInfoModelRulemachine1_localnode.h"
#include "ClipsInfoModelRulemachine1_list.h"



typedef struct imr1_import_context {
	CLIPSValueMap* cvmap;
} IMR1ImportContext;



IMR1ImportContext* IMR1ImportContext_new(Environment* env){
	IMR1ImportContext* ret = malloc(sizeof(IMR1ImportContext));
	if (ret == NULL) return NULL;
	ret->cvmap = CLIPSValueMap_new(env);
	return ret;
}

void free_IMR1ImportContext(IMR1ImportContext* x){
	if (x == NULL) return;
	free_CLIPSValueMap(x->cvmap);
	free(x);
}


static Multifield* generate_clipsmultifield_from_termlist(Environment* env, IMR1ImportContext* cntxt, RIFITermList* list);


CLIPSValue CLIPSValue_from_RIFITerm(Environment* env, IMR1ImportContext* cntxt, const RIFITerm* term){
	Literal* tmplit;
	CLIPSValue retvoid, tmprest, ret;
	retvoid.voidValue = VoidConstant(env);
	if (term == NULL){
		return retvoid;
	}
	Multifield* tmpitems;
	switch (term->type){
		case RIF_IRI:
			tmplit = Literal_new_iri(term->value, strlen(term->value));
			break;
		case RIF_TypedLiteral:
			tmplit = Literal_new(term->value, term->suffix);
			break;
		case RIF_LangLiteral:
			tmplit = Literal_new_langliteral(term->value, term->suffix);
			break;
		case RIF_List:
			tmprest = CLIPSValue_from_RIFITerm(env, cntxt, term->rest);
			//Accept void for tmprest
			tmpitems = generate_clipsmultifield_from_termlist(env, cntxt, term->list);
			if (tmpitems == NULL){
				return retvoid;
			}
			return CLIPSValue_new_termlist(env, tmpitems, tmprest);
		case RIF_Local:
			return CLIPSValueMap_get_localnode(cntxt->cvmap, term->value);
		case RIF_Variable:
			fprintf(stderr, "Cant translate RIFITerm Variable "
					"to CLIPS value.\n");
		default:
			fprintf(stderr, "ClipsInfoModelRulemachine1: internal "
					"error CLIPSValue_from_RIFITerm\n");
			return retvoid;
	}
	ret = Literal_to_CLIPSValue(env, tmplit);
	free_Literal(tmplit);
	return ret;
}


static Multifield* generate_clipsmultifield_from_termlist(Environment* env, IMR1ImportContext* cntxt, RIFITermList* list)
{
	Multifield* mf;
	MultifieldBuilder *mb;
	CLIPSValue tmp_cv;
	size_t l=0;
	for(RIFITermList* x = list; x!=NULL; x=x->rest){
		l++;
	}
	mb = CreateMultifieldBuilder(env, l);
	for(RIFITermList* x = list; x!=NULL; x=x->rest){
		tmp_cv = CLIPSValue_from_RIFITerm(env, cntxt, x->first);
		if (tmp_cv.header->type == VOID_TYPE) return NULL;
		MBAppend(mb, &tmp_cv);
	}
	mf = MBCreate(mb);
	MBDispose(mb);
	return mf;
}
