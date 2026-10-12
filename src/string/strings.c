#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "ClipsInfoModelRulemachine1_string.h"
#include <regex.h>

static int normalize_index(int index, int length);
static int CIMR1_string_position(const char* source, const char* query);
extern char* my_percent_decode(const char *src, const size_t len);
extern char* percent_encode_type1(const char *src, const size_t len);

char* CIMR1_string_string_cut(const char* string, int start){
	int ret_length;
	char* ret;
	size_t length = strlen(string);
	if (start < 1){
		start = 1;
	}
	ret_length = length-start;
	if (ret_length >= 0){
		ret = malloc(ret_length + 1);
	} else {
		ret_length = 0;
		ret = malloc(1);
	}
	memcpy(ret, string+start, ret_length);
	ret[ret_length] = '\0';
	return ret;
}

char* CIMR1_string_substring(const char* string, int start, int end){
	int ret_length;
	char* ret;
	size_t length = strlen(string);
	if (start < 1){
		start = 1;
	}
	if (end > length){
		end = length;
	}
	ret_length = end-start;
	if (ret_length >= 0){
		ret = malloc(ret_length + 1);
	} else {
		ret_length = 0;
		ret = malloc(1);
	}
	memcpy(ret, string+start-1, ret_length);
	ret[ret_length] = '\0';
	return ret;
}

static int normalize_index(int index, int length){
	if (length < 0){
		return -1;
	}
	if (index<0){
		index += length;
	}
	if (index < 0 || index >= length){
		return -1;
	}
	return index;
}


char* CIMR1_string_uppercase(const char* input){
	size_t length = strlen(input);
	char* ret = malloc(length+1);
	for(size_t i=0; i<length; i++){
		ret[i] = toupper(input[i]);
	}
	ret[length] = '\0';
	return ret;
}


char* CIMR1_string_lowercase(const char* input){
	size_t length = strlen(input);
	char* ret = malloc(length + 1);
	for(size_t i=0; i<length; i++){
		ret[i] = tolower(input[i]);
	}
	ret[length] = '\0';
	return ret;
}


char* CIMR1_string_substring_after(const char* source, const char* query){
	char* ret;
	size_t ls, lq, length;
	const int pos = CIMR1_string_position(source, query);
	if (pos < 0){
		return NULL;
	}
	ls = strlen(source);
	lq = strlen(query);
	length = ls - pos - lq;
	ret = malloc(length + 1);
	memcpy(ret, source + pos + lq, length);
	ret[length] = '\0';
	return ret;
}


char* CIMR1_string_substring_before(const char* source, const char* query){
	char* ret;
	const int pos = CIMR1_string_position(source, query);
	fprintf(stderr, "substring before: %d src %s query %s\n", pos, source, query);
	if (pos < 0){
		return NULL;
	}
	ret = malloc(pos + 1);
	memcpy(ret, source, pos);
	ret[pos] = '\0';
	return ret;
}

bool CIMR1_string_contains(const char* source, const char* query){
	if (0 <= CIMR1_string_position(source, query)){
		return true;
	} else {
		return false;
	}
}

static int CIMR1_string_position(const char* source, const char* query){
	int diff;
	const size_t source_length = strlen(source);
	const size_t query_length = strlen(query);
	for (int i = 0; i<source_length - query_length +1; i++){
		fprintf(stderr, "qq %s\n", source + i);
		diff = memcmp(source + i, query, query_length);
		if(diff == 0){
			return i;
		}
	}
	return -1;
}


bool CIMR1_string_matches(const char* source, const char* query){
	int err;
	regex_t reegex;
	if(0 != regcomp(&reegex, query, REG_EXTENDED)){
		return false;
	}
	err = regexec(&reegex, source, 0, NULL, 0);
	regfree(&reegex);
	if(0 == err){
		return true;
	} else {
		return false;
	}
}


bool CIMR1_string_starts_with(const char* source, const char* query){
	int diff;
	size_t source_length = strlen(source);
	size_t query_length = strlen(query);
	if (query_length <= source_length){
		diff = memcmp(source, query, query_length);
		return diff == 0;
	}
	return false;
}


bool CIMR1_string_ends_with(const char* source, const char* query){
	int diff;
	size_t source_length = strlen(source);
	size_t query_length = strlen(query);
	if (query_length <= source_length){
		diff = memcmp(source + source_length - query_length,
					query, query_length);
		return diff == 0;
	}
	return false;
}
