#include "ClipsInfoModelRulemachine1_externaladdress.h"

#define get_CIMR1ExternalAddressData(theEnv) \
	((CIMR1ExternalAddressData *) GetEnvironmentData(theEnv, CLIPSPLUGIN_INDEX_CIMR1ExternalAddress))


typedef enum {
	CIMR1LIST_ID,
} CVEXTERNALADDRESS_ID;

/*
 * Every external data ist on of this
 */
typedef struct s_CIMR1ExternalAddress {
	CVEXTERNALADDRESS_ID type;
	Environment* env;
	union {
		CIMR1List list;
	};
} CIMR1ExternalAddress;

typedef struct s_CVList {
	CLIPSExternalAddress *first;
	struct s_CVList *rest;
} CVList;

/*
 * Plugin data saved in Environment
 */
typedef struct s_CIMR1ExternalAddressData {
	CVList* cvlist_release_after_rulerun;
} CIMR1ExternalAddressData;


static void release_CIMR1ExternalAddressData(Environment*);
static void reset_CIMR1ExternalAddressData(Environment*);
static void release_after_rulerun(Environment*, Activation*, void*);
static void force_release_cvlist(CVList*);
static CVList* try_release_cvlist(CVList*);


int register_CIMR1ExternalAddressData(Environment* env){
	bool success;
	success = AllocateEnvironmentData(env,
					CLIPSPLUGIN_INDEX_CIMR1ExternalAddress,
					sizeof(CIMR1ExternalAddressData),
					release_CIMR1ExternalAddressData);
	if(!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	reset_CIMR1ExternalAddressData(env);
	
	success = AddAfterRuleFiresFunction(env, "release_after_rulerun",
			release_after_rulerun, 0, NULL);
	if (!success){
		ExitRouter(env, EXIT_FAILURE);
		return 1;
	}
	
	return 0;
}


static void reset_CIMR1ExternalAddressData(Environment* env){
	CIMR1ExternalAddressData* data = get_CIMR1ExternalAddressData(env);
	data->cvlist_release_after_rulerun = NULL;
}


static void release_CIMR1ExternalAddressData(Environment *env){
	CIMR1ExternalAddressData* data = get_CIMR1ExternalAddressData(env);
	//force_release_cvlist(data->cvlist_release_after_rulerun);
}

static bool CVList_cv_used(CVList* x){
	return x->first->count != 1;
}

static void free_CVList(CVList* x){
	CIMR1ExternalAddress* addr = (CIMR1ExternalAddress*) x->first->contents;

	switch(addr->type){
		case CIMR1LIST_ID:
			release_CIMR1List(addr->list);
			break;
		default:
			fprintf(stderr, "ERROR free_CVList\n");
			return;
	}
	ReleaseExternalAddress(addr->env, x->first);
	free(x);
}

static CVList* try_release_cvlist(CVList* start){
	CVList *tmpcvlist, *current, *next;
	if (start == NULL) return NULL;
	while (!CVList_cv_used(start)){
		tmpcvlist = start->rest;
		free_CVList(start);
		if (tmpcvlist == NULL){
			return NULL;
		}
		start = tmpcvlist;
	}
	start->rest = try_release_cvlist(start->rest);
	return start;
}

static void release_after_rulerun(Environment* env, Activation*, void*){
	CIMR1ExternalAddressData* data = get_CIMR1ExternalAddressData(env);
	data->cvlist_release_after_rulerun
		= try_release_cvlist(data->cvlist_release_after_rulerun);
}


CIMR1List* CVExternalAddress_get_CIMR1List(CLIPSExternalAddress* x){
	CLIPSExternalAddress *ret;
	if (x->type != CIMR1LIST_ID){
		return NULL;
	}
	fprintf(stderr, "%d\n", ret->count);
	return NULL;
}
