#include "ClipsInfoModelRulemachine1_localnode.h"
#include "hashtable.h"

#define INITIAL_HASHTABLE_SIZE 30

typedef char* DKey;
typedef const char* DLookKey;
typedef Literal* DValue;

typedef struct s_CLIPSValueMap {
	Environment *env;
	HashTable map;
} CLIPSValueMap;

typedef bool (*ht_iterate_t) (void* key, void* value, void* user);


static int insert_CLIPSValueMap(CLIPSValueMap* table, const char* x, Literal* y);
static size_t hash_CLIPSValueMap(DKey*, size_t);
static int compare_CLIPSValueMap(DLookKey*, DLookKey*, size_t);


CLIPSValueMap* CLIPSValueMap_new(Environment* env){
	CLIPSValueMap *ret = malloc(sizeof(CLIPSValueMap));
	ret->env = env;
	ht_setup(&(ret->map), sizeof(DKey), sizeof(DValue), INITIAL_HASHTABLE_SIZE);
	ret->map.hash = (hash_t) hash_CLIPSValueMap;
	ret->map.compare = (comparison_t) compare_CLIPSValueMap;
	return ret;
}

CLIPSValue CLIPSValueMap_get_localnode(CLIPSValueMap* x, const char* id){
	CLIPSValue ret = {};
	DLookKey key = id;
	DValue* val;
	Literal* new_val;
	val = ht_lookup(&x->map, &key);
	if (val != NULL){
		return Literal_to_CLIPSValue(x->env, *val);
	}
	new_val = Literal_new_localnode(x->env, id);
	if (new_val == NULL){
		fprintf(stderr, "ERROR CLIPSValueMap_get_localnode\n");
		ret.voidValue = VoidConstant(x->env);
		return ret;
	}
	insert_CLIPSValueMap(x, id, new_val);
	return Literal_to_CLIPSValue(x->env, new_val);
}

static int insert_CLIPSValueMap(CLIPSValueMap* table, const char* x, Literal* y){
	int err;
	DKey key = malloc(strlen(x) + 1);
	strcpy(key, x);
	DValue value = y;
	err = ht_insert(&table->map, &key, &value);
	return err;
}

static size_t hash_CLIPSValueMap(DKey* key, size_t)
{
	size_t hash = 5381;
	for(const char*tmp = *key; tmp[0] != '\0'; tmp++){
		hash = ((hash << 5) + hash) + tmp[0];
	}
	return hash;
}

static int compare_CLIPSValueMap(DLookKey* x, DLookKey* y, size_t){
	return strcmp(*x, *y);
}

bool iter_remove(DKey* key, DValue* value, void* user){
	free_Literal(*value);
	free(*key);
	return true;
}

void free_CLIPSValueMap(CLIPSValueMap* x){
	if (ht_is_initialized(&x->map)){
		ht_iterate_remove(&(x->map), NULL,
				(ht_iterate_t) iter_remove);
	}
	ht_destroy(&x->map);
	free(x);
}

