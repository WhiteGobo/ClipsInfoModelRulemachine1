#include "shared_information.h"
#include "extractor.h"

size_t CIMR1_get_next_local_prefix_id(Environment* env)
{
	InfoModelRulemachine1Data* data = LoadingInfoModelRulemachine1Data(env);
	size_t ret = data->local_prefix_id++;
	return ret;
}



