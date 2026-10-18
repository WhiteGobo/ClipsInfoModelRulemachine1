#include <clips.h>
#include "extractor.h"
//#include "info_query.h"
//#include "constfunctions.h"

#include "namespace_CIMR1.h"
#include "namespace_PRED.h"
#include "namespace_FUNC.h"

#include "functions_from_literals.h"
#include "udfdescription.h"


static UDFDescription builtinFunctionList[];
extern const UDFDescription builtinFunctionList_IsLiteral[];
extern const UDFDescription builtinFunctionList_List[];
extern const UDFDescription builtinFunctionList_Math[];
extern const UDFDescription builtinFunctionList_ImportExport[];
extern const UDFDescription builtinFunctionList_Literal[];
extern const UDFDescription builtinFunctionList_String[];
extern const UDFDescription builtinFunctionList_Boolean[];
extern const UDFDescription builtinFunctionList_Time[];
extern const UDFDescription builtinFunctionList_Formula[];
extern const UDFDescription_Ext builtinFunctionList_LiteralGenerator[];

static bool add_literal_user_functions_list(Environment* env, const UDFDescription* descriptions);
static bool add_literal_user_functions_list_ext(Environment* env, const UDFDescription_Ext* descriptions);

bool add_literal_user_functions(Environment* env){
	if (!add_literal_user_functions_list(env, builtinFunctionList)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_IsLiteral)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_List)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_Literal)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_Math)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_String)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_ImportExport)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_Boolean)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_Time)){
		return false;
	}
	if (!add_literal_user_functions_list(env,builtinFunctionList_Formula)){
		return false;
	}
	if (!add_literal_user_functions_list_ext(env, builtinFunctionList_LiteralGenerator)){
		return false;
	}
	return true;
}

static bool add_literal_user_functions_list_ext(Environment* env, const UDFDescription_Ext* descriptions)
{
	for (UDFDescription_Ext *x = descriptions; x->clipsName != NULL; x++){
		AddUDFError err = AddUDF(env, x->clipsName, x->returnTypes,
				x->minArgs, x->maxArgs, x->argTypes, x->cfp,
				x->cName, x->user);
		switch (err) {
			case AUE_NO_ERROR:
				break;
			case AUE_MIN_EXCEEDS_MAX_ERROR:
			case AUE_FUNCTION_NAME_IN_USE_ERROR:
			case AUE_INVALID_ARGUMENT_TYPE_ERROR:
			case AUE_INVALID_RETURN_TYPE_ERROR:
				fprintf(stderr, "Failed to register: %s\n",
						x->clipsName);
				return false;
		}
	}
	return true;
}

static bool add_literal_user_functions_list(Environment* env, const UDFDescription* descriptions)
{
	void* cntxt = NULL;
	for (UDFDescription *x = descriptions; x->clipsName != NULL; x++){
		AddUDFError err = AddUDF(env, x->clipsName, x->returnTypes,
				x->minArgs, x->maxArgs, x->argTypes, x->cfp,
				x->cName, cntxt);
		switch (err) {
			case AUE_NO_ERROR:
				break;
			case AUE_MIN_EXCEEDS_MAX_ERROR:
			case AUE_FUNCTION_NAME_IN_USE_ERROR:
			case AUE_INVALID_ARGUMENT_TYPE_ERROR:
			case AUE_INVALID_RETURN_TYPE_ERROR:
				fprintf(stderr, "Failed to register: %s\n",
						x->clipsName);
				return false;
		}
	}
	return true;
}


static UDFDescription builtinFunctionList[] = {
	{"<"_PRED_literal_not_identical_">", "*", 2, 2, NULL,
		pred_literal_not_identical, "pred_literal_not_identical"},
	{NULL, NULL, 0,0, NULL, NULL, NULL},
};
