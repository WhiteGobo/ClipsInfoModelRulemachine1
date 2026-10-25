#include "ClipsInfoModelRulemachine1_extractor.h"
#include <Mime2Rdf4C.h>
#include "literals.h"
#include "data.h"
#include "ClipsInfoModelRulemachine1_list.h"

typedef struct s_ExportRDFData {
	Environment* env;
	int err;
	Mime2Rdf4C_SerializerConfig* serializer;
} ExportRDFData;

static int send_literal_triple(ExportRDFData cntxt, Literal* lit_obj, Literal* lit_skey, Literal* lit_sval);
static ExportRDFData send_frames(ExportRDFData);
static ExportRDFData send_single_frame(ExportRDFData cntxt, CLIPSValue cv);

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
	fprintf(stderr, "extract data\n");
	return Mime2Rdf4C_finish(cntxt.serializer);
}

static Literal* process_list_and_return_base(ExportRDFData cntxt, CLIPSValue cv){
	fprintf(stderr, "ERROR process_list_and_return_base not implemented\n");
	return NULL;
}


static int send_literal_triple(ExportRDFData cntxt, Literal* lit_obj, Literal* lit_skey, Literal* lit_sval){
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
			NULL, BNODE, cntxt.serializer);
	return err;
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
	lit_sval = Literal_from_CLIPSValue(cntxt.env, slot.value);
	if(lit_sval == NULL){
		if(CLIPSValue_is_list(cntxt.env, slot.value)){
			lit_sval = process_list_and_return_base(
						cntxt, slot.value);
		}
	}
	if (lit_sval == NULL){
		fprintf(stderr, "WARNING send_frames(slotvalue)\n");
		free_Literal(lit_obj);
		free_Literal(lit_skey);
		return cntxt;
	}
	err = send_literal_triple(cntxt, lit_obj, lit_skey, lit_sval);
	free_Literal(lit_obj);
	free_Literal(lit_skey);
	free_Literal(lit_sval);
	if (err != 0){
		fprintf(stderr, "ERROR send_literal_triple\n");
	}
	return cntxt;
}
