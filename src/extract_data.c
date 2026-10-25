#include "ClipsInfoModelRulemachine1.h"
#include "extractor.h"

char* InfoModelRulemachine1Data_export_rif_data(Environment *env, const char* format){
	return Environment_export_rif_data(env, format);
}

char* InfoModelRulemachine1Data_export_rdf_data(Environment *env, const char* format){
	return Environment_export_rdf_data(env, format);
}
