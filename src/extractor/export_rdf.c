#include "ClipsInfoModelRulemachine1_extractor.h"
#include <Mime2Rdf4C.h>
#include "literals.h"
#include "data.h"
#include "ClipsInfoModelRulemachine1_list.h"

#include "namespace_RDF.h"

//TODO this list is just so that clipsvalues are save. replace to clipsvalue list
typedef struct s_ListLiteral {
	Literal* first;
	struct s_ListLiteral* rest;
} ListLiteral;

typedef struct s_ExportRDFData {
	Environment* env;
	int err;
	Mime2Rdf4C_SerializerConfig* serializer;
	ListLiteral* tmpliterals;
} ExportRDFData;

static void fprintf_ListLiteral(FILE* f, ListLiteral* list);
static ListLiteral* ListLiteral_insert(ListLiteral*, const Literal*);
static void free_ListLiteral(ListLiteral*);
static int send_literal_triple(ExportRDFData *cntxt, Literal* lit_obj, Literal* lit_skey, Literal* lit_sval);
static ExportRDFData send_frames(ExportRDFData);
static ExportRDFData send_single_frame(ExportRDFData cntxt, CLIPSValue cv);
static ExportRDFData send_members(ExportRDFData);
static ExportRDFData send_single_member(ExportRDFData cntxt, CLIPSValue cv);

static Literal* get_literal_from_object_and_process(ExportRDFData*, CLIPSValue cv);
static Literal* process_list_and_return_base(ExportRDFData*, CLIPSValue cv);

char* Environment_export_rdf_data(Environment *env, const char* format){
	ExportRDFData cntxt = {
		.env = env,
		.err = 0,
	};

	cntxt.serializer = Mime2Rdf4C_get_serializer_from_mediatype(format);
	if (cntxt.serializer == NULL){
		cntxt.serializer = Mime2Rdf4C_get_serializer_from_ext(format);
	}
	if (cntxt.serializer == NULL){
		fprintf(stderr, "ERROR Failed to find RDF serializer for "
				"format '%s'\n", format);
		return NULL;
	}

	cntxt = send_frames(cntxt);
	if (cntxt.err != 0){
		return NULL;
	}
	cntxt = send_members(cntxt);
	if (cntxt.err != 0){
		return NULL;
	}
	fprintf(stderr, "extract data\n");
	return Mime2Rdf4C_finish(cntxt.serializer);
}

static Literal* get_literal_from_object_and_process(ExportRDFData *cntxt, CLIPSValue cv)
{
	Literal* ret;
	ret = Literal_from_CLIPSValue(cntxt->env, cv);
	if(ret != NULL){
		return ret;
	}
	if(CLIPSValue_is_list(cntxt->env, cv)){
		return process_list_and_return_base(cntxt, cv);
	}
	return NULL;
}

static Literal* process_list_and_return_base(ExportRDFData* cntxt, CLIPSValue cv){
	int err;
	Literal *ret, *nil, *first, *rest, *tmplast, *tmplit, *tmpfirst;
	const char* basename = "local";
	Multifield* mf = CLIPSValue_get_termlist(cntxt->env, cv);
	if(mf == NULL){
		WriteString(cntxt->env, STDERR, "ERROR CLIPSValue_get_termlist "
				"failed on list\n");
		cntxt->err = 1;
		return NULL;
	}
	nil = Literal_new_iri(_RDF_nil_, sizeof(_RDF_nil_));
	first = Literal_new_iri(_RDF_first_, sizeof(_RDF_first_));
	rest = Literal_new_iri(_RDF_rest_, sizeof(_RDF_rest_));
	if(nil == NULL || first == NULL || rest == NULL){
		WriteString(cntxt->env, STDERR,"ERROR Literal_new_iri failed\n");
		cntxt->err = 1;
		free_Literal(nil); free_Literal(first); free_Literal(rest);
		return NULL;
	}
	if(mf->length == 0){
		free_Literal(first); free_Literal(rest);
		return nil;
	}
	ret = Literal_new_localnode(cntxt->env, basename);
	if(ret == NULL){
		WriteString(cntxt->env, STDERR,
				"ERROR Literal_new_localnode failed\n");
		cntxt->err = 1;
		return NULL;
	}
	cntxt->tmpliterals = ListLiteral_insert(cntxt->tmpliterals, ret);
	tmpfirst = get_literal_from_object_and_process(cntxt, mf->contents[0]);
	err = send_literal_triple(cntxt, ret, first, tmpfirst);
	//TODO check err
	tmplast = ret;
	for(size_t i = 1; i < mf->length; i++){
		tmplit = Literal_new_localnode(cntxt->env, basename);
		cntxt->tmpliterals = ListLiteral_insert(cntxt->tmpliterals, tmplit);
		err = send_literal_triple(cntxt, tmplast, rest, tmplit);
		tmpfirst = get_literal_from_object_and_process(cntxt, mf->contents[i]);
		err = send_literal_triple(cntxt, tmplit, first, tmpfirst);
		//TODO check err
		tmplast = tmplit;
	}
	err = send_literal_triple(cntxt, tmplast, rest, nil);
	free_Literal(nil);
	free_Literal(first);
	free_Literal(rest);
	return ret;
}


static int send_literal_triple(ExportRDFData *cntxt, Literal* lit_obj, Literal* lit_skey, Literal* lit_sval){
	int64_t err;
	const char* subject;
	uint8_t subject_type;
	const char* predicate;
	const char* object;
	const char* object_suffix;
	uint8_t object_type;
	subject_type = Literal_get_type(lit_obj);
	switch(subject_type){
		case URI:
		case BNODE:
			subject = Literal_get_value(lit_obj);
			break;
		default: //Skip typed and lang literals
			return 0;
	}
	switch(Literal_get_type(lit_skey)){
		case URI:
			predicate = Literal_get_value(lit_skey);
			break;
		default: //Skip non uri predicates
			return 0;
	}
	object_type = Literal_get_type(lit_sval);
	object = Literal_get_value(lit_sval);
	switch(object_type){
		case TYPEDLITERAL:
			object_suffix = Literal_get_datatype(lit_sval);
			break;
		case LANGLITERAL:
			object_suffix = Literal_get_lang(lit_sval);
			break;
		case URI:
		case BNODE:
			object_suffix = NULL;
			break;
		default:
			return 0;
	}
	err = Mime2Rdf4C_add(subject, subject_type,
			predicate,
			object, object_suffix,
			object_type,
			NULL, BNODE, cntxt->serializer);
	if(err != 0){
		WriteString(cntxt->env, STDERR, "Failed to send triple: (");
		WriteLiteral(cntxt->env, STDERR, lit_obj);
		WriteString(cntxt->env, STDERR, ", ");
		WriteLiteral(cntxt->env, STDERR, lit_skey);
		WriteString(cntxt->env, STDERR, ", ");
		WriteLiteral(cntxt->env, STDERR, lit_sval);
		WriteString(cntxt->env, STDERR, ")\n");
		return 1;
	}
	return 0;
}


static ExportRDFData send_members(ExportRDFData cntxt){
	Multifield* members = Environment_get_members(cntxt.env);
	if (members == NULL){
		return cntxt;
	}
	RetainMultifield(cntxt.env, members);
	for (size_t i = 0; i<members->length; i++){
		cntxt = send_single_member(cntxt, members->contents[i]);
	}
	ReleaseMultifield(cntxt.env, members);
	return cntxt;
}


static ExportRDFData send_single_member(ExportRDFData cntxt, CLIPSValue cv){
	int err;
	Literal *lit1, *lit2, *lit3;
	const CLIPSValue instance = CLIPSValue_Member_get_instance(cntxt.env, cv);
	const CLIPSValue class = CLIPSValue_Member_get_class(cntxt.env, cv);
	lit1 = Literal_from_CLIPSValue(cntxt.env, instance);
	if (lit1 == NULL){
		fprintf(stderr, "WARNING send_\n");
		return cntxt;
	}
	lit2 = Literal_new_iri(
		"http://www.w3.org/1999/02/22-rdf-syntax-ns#type",
		sizeof("http://www.w3.org/1999/02/22-rdf-syntax-ns#type"));
	if (lit2 == NULL){
		free_Literal(lit1);
		fprintf(stderr, "WARNING send_\n");
		return cntxt;
	}
	lit3 = get_literal_from_object_and_process(&cntxt, class);
	if (lit3 == NULL){
		fprintf(stderr, "WARNING send_\n");
		free_Literal(lit1);
		free_Literal(lit2);
		return cntxt;
	}
	err = send_literal_triple(&cntxt, lit1, lit2, lit3);
	free_Literal(lit1);
	free_Literal(lit2);
	free_Literal(lit3);
	if (err != 0){
		fprintf(stderr, "ERROR send_literal_triple\n");
	}
	return cntxt;
}


static ExportRDFData send_frames(ExportRDFData cntxt){
	Multifield* frames = Environment_get_frames(cntxt.env);
	if (frames == NULL){
		return cntxt;
	}
	RetainMultifield(cntxt.env, frames);
	for (size_t i = 0; i<frames->length; i++){
		cntxt = send_single_frame(cntxt, frames->contents[i]);
	}
	ReleaseMultifield(cntxt.env, frames);
	return cntxt;
}


static ExportRDFData send_single_frame(ExportRDFData cntxt, CLIPSValue cv){
	int err;
	Literal *lit_obj, *lit_skey, *lit_sval;
	const CLIPSValue obj = CLIPSValue_Frame_get_object(cntxt.env, cv);
	const RetFactFrameGetSlot slot = CLIPSValue_Frame_get_slot(cntxt.env, cv);
	lit_obj = Literal_from_CLIPSValue(cntxt.env, obj);
	if (lit_obj == NULL){
		fprintf(stderr, "WARNING send_frames(object)\n");
		return cntxt;
	}
	lit_skey = Literal_from_CLIPSValue(cntxt.env, slot.key);
	if (lit_skey == NULL){
		free_Literal(lit_obj);
		fprintf(stderr, "WARNING send_frames(slotkey)\n");
		return cntxt;
	}
	lit_sval = get_literal_from_object_and_process(&cntxt, slot.value);
	if (lit_sval == NULL){
		fprintf(stderr, "WARNING send_frames(slotvalue)\n");
		free_Literal(lit_obj);
		free_Literal(lit_skey);
		return cntxt;
	}
	err = send_literal_triple(&cntxt, lit_obj, lit_skey, lit_sval);
	free_Literal(lit_obj);
	free_Literal(lit_skey);
	free_Literal(lit_sval);
	if (err != 0){
		fprintf(stderr, "ERROR send_literal_triple\n");
	}
	return cntxt;
}


static ListLiteral* ListLiteral_insert(ListLiteral* oldlist, const Literal* x){
	Environment *env = Literal_get_environment(x);
	if (env == NULL){
		//Only save Literals that are environment specific
		return oldlist;
	}
	Literal* cpy = Literal_from_CLIPSValue(env, Literal_to_CLIPSValue(env, x));
	ListLiteral* ret = malloc(sizeof(ListLiteral));
	if (ret == NULL){
		fprintf(stderr, "CRITICAL ERROR malloc failed\n");
		return NULL;
	}
	ret->rest = oldlist;
	ret->first = x;
	return ret;
}

static void free_ListLiteral(ListLiteral* x){
	ListLiteral* rest;
	while(x != NULL){
		rest = x->rest;
		free_Literal(x->first);
		free(x);
		x = rest;
	}
}

static void fprintf_ListLiteral(FILE* f, ListLiteral* list){
	fprintf(f, "[");
	for(ListLiteral* x=list; x != NULL; x=x->rest){
		fprintf_Literal(f, x->first);
		fprintf(f, " ");
	}
	fprintf(f, "]");
}
