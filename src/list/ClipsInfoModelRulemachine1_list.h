#pragma once

#include <clips.h>

#ifndef CLIPSPLUGIN_INDEX_CIMR1ListData
#define CLIPSPLUGIN_INDEX_CIMR1ListData USER_ENVIRONMENT_DATA + 8
#endif


typedef struct s_CIMR1List {
	Environment* env;
	Multifield* items;
} CIMR1List;


int register_CIMR1ListData(Environment*);

bool CLIPSValue_is_list(Environment* env, CLIPSValue);
CLIPSValue CLIPSValue_new_termlist(Environment* env, Multifield* items, CLIPSValue rest);
Multifield* CLIPSValue_get_termlist(Environment*, CLIPSValue);
bool CLIPSValue_contains(Environment*, CLIPSValue container, CLIPSValue item);
int CLIPSValue_length(Environment*, CLIPSValue);
CLIPSValue CLIPSValue_get_item(Environment*, CLIPSValue, int);

/*
 * if length < 0 return full list starting from start.
 */
CLIPSValue CLIPSValue_sublist(Environment*, CLIPSValue, int start, int length);
CLIPSValue CLIPSValue_append(Environment*, CLIPSValue list, CLIPSValue item);
CLIPSValue CLIPSValue_concatenate(Environment*, CLIPSValue first, CLIPSValue second);
CLIPSValue CLIPSValue_insert_before(Environment*, CLIPSValue list, int position, CLIPSValue item);
CLIPSValue CLIPSValue_remove(Environment*, CLIPSValue, int);
CLIPSValue CLIPSValue_reverse(Environment*, CLIPSValue);

/*
 * The function returns a sequence of positive integers giving the positions
 * within the sequence $seq of items that are equal to $search.
 */
CLIPSValue CLIPSValue_index_of(Environment*, CLIPSValue list, CLIPSValue item);
CLIPSValue CLIPSValue_distinct_values(Environment*, CLIPSValue);
CLIPSValue CLIPSValue_intersect(Environment*, CLIPSValue, CLIPSValue);
CLIPSValue CLIPSValue_except(Environment* env, CLIPSValue first, CLIPSValue second);


//CLIPSValue generate_clipsvalue_from_termlist(Environment* env, LocalTermMap* cntxt, Multifield* items, CLIPSValue rest)

void release_CIMR1List(CIMR1List);

Multifield* CIMR1List_get_items(CIMR1List*);
//bool CIMR1List_equal(CIMR1List*, CIMR1List*);
//bool CIMR1List_equivalent(CIMR1List*, CLIPSValue);
