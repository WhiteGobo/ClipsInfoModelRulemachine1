#include "ClipsInfoModelRulemachine1_list.h"
#include "ClipsInfoModelRulemachine1_externaladdress.h"

#define get_CIMR1ListData(theEnv) \
	((CIMR1ListData *) GetEnvironmentData(theEnv, CLIPSPLUGIN_INDEX_CIMR1ListData))

/*
typedef struct s_CIMR1List {
	Environment* env;
	Multifield* items;
} CIMR1List;
*/

typedef struct s_List_CIMR1List {
	CIMR1List* first;
	struct s_List_CIMR1List* rest;
} List_CIMR1List;

typedef struct s_CIMR1ListData {
	List_CIMR1List* all_lists;
} CIMR1ListData;



static void release_all_temporary_lists(Environment*, Activation*, void*);
static void release_CIMR1ListData(Environment*);
static void reset_CIMR1ListData(Environment*);
static void free_CIMR1List(CIMR1List*);


int register_CIMR1ListData(Environment* env){
	bool success;
	success = AllocateEnvironmentData(env, CLIPSPLUGIN_INDEX_CIMR1ListData,
					sizeof(CIMR1ListData),
					release_CIMR1ListData);
	if(!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	reset_CIMR1ListData(env);

	success = AddAfterRuleFiresFunction(env, "release_all_temporary_lists",
			release_all_temporary_lists, 0, NULL);
	if (!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	return 0;
}

static void reset_CIMR1ListData(Environment* env){
	CIMR1ListData* data = get_CIMR1ListData(env);
	data->all_lists = NULL;
}

static void release_CIMR1ListData(Environment *env){
	CIMR1ListData* data = get_CIMR1ListData(env);
	release_all_temporary_lists(env, NULL, NULL);
}

static void release_all_temporary_lists(Environment* env, Activation*, void*){
	CIMR1ListData* data = get_CIMR1ListData(env);
	List_CIMR1List* current;
	List_CIMR1List* next = data->all_lists;
	while (next != NULL){
		current = next;
		next = current->rest;
		free_CIMR1List(current->first);
		free(current);
	}
}

void release_CIMR1List(CIMR1List x){
	ReleaseMultifield(x.env, x.items);
};

static void free_CIMR1List(CIMR1List* x){
	ReleaseMultifield(x->env, x->items);
	free(x);
};


/*
bool CIMR1List_equivalent(CIMR1List* self, CLIPSValue othercv){
	CIMR1List* other;
	switch(othercv.header->type){
		case EXTERNAL_ADDRESS_TYPE:
			other = CVExternalAddress_get_CIMR1List(othercv.externalAddressValue);
			if(other != NULL){
				return CIMR1List_equal(self, other);
			} else {
				return false;
			}
		case MULTIFIELD_TYPE:
		default:
			return false;
	}
}
*/

