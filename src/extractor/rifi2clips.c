#include "extractor.h"
#include "shared_information.h"
#include "terms.h"
#include "ClipsInfoModelRulemachine1_localnode.h"


typedef struct imr1_import_context {
	LocalTermMap* map;
	CLIPSValueMap* cvmap;
} IMR1ImportContext;

IMR1ImportContext* IMR1ImportContext_new(Environment* env){
	IMR1ImportContext* ret = malloc(sizeof(IMR1ImportContext));
	if (ret == NULL) return NULL;
	ret->map = LocalTermMap_new(env);
	ret->cvmap = CLIPSValueMap_new(env);
	return ret;
}

void free_IMR1ImportContext(IMR1ImportContext* x){
	if (x == NULL) return;
	free_LocalTermMap(x->map);
	free_CLIPSValueMap(x->cvmap);
	free(x);
}


static Multifield* generate_clipsmultifield_from_termlist(Environment* env, IMR1ImportContext* cntxt, RIFITermList* list);


CLIPSValue CLIPSValue_from_RIFITerm(Environment* env, IMR1ImportContext* cntxt, const RIFITerm* term){
	CLIPSValue retvoid, tmprest;
	retvoid.voidValue = VoidConstant(env);
	if (term == NULL){
		return retvoid;
	}
	Multifield* tmpitems;
	switch (term->type){
		case RIF_IRI:
			return generate_clipssymbol_from_iri(env, term->value);
		case RIF_TypedLiteral:
			return generate_clipsvalue_from_typedliteral(env, term->value, term->suffix);
		case RIF_LangLiteral:
			return generate_clipsvalue_from_langliteral(env, term->value, term->suffix);
		case RIF_List:
			tmprest = CLIPSValue_from_RIFITerm(env, cntxt, term->rest);
			if (tmprest.header->type == VOID_TYPE){
				return retvoid;
			}
			tmpitems = generate_clipsmultifield_from_termlist(env, cntxt, term->list);
			if (tmpitems == NULL){
				return retvoid;
			}
			return generate_clipsvalue_from_termlist(env, cntxt->map, tmpitems, tmprest);
		case RIF_Local:
			//return CLIPSValueMap_get_localnode(cntxt->cvmap, term->value);
			return generate_clipssymbol_from_local(env, cntxt->map, term->value);
		case RIF_Variable:
			fprintf(stderr, "Cant translate RIFITerm Variable "
					"to CLIPS value.\n");
		default:
			fprintf(stderr, "ClipsInfoModelRulemachine1: internal "
					"error CLIPSValue_from_RIFITerm\n");
			return retvoid;
	}
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
