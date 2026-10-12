#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "ClipsInfoModelRulemachine1_string.h"

static size_t get_match_length(regmatch_t match){
	return match.rm_eo - match.rm_so;
}

/**
 * TODO: Missing interpretation of given flags
 */
static int get_regex_flags(const char* flags){
	int f = REG_EXTENDED;
	if (flags != NULL){
		for (const char *f =flags; *f != '\0'; f++){
		}
	}
	return f;
}

typedef struct process_replacement_helper {
	const char *prefix;
	size_t prefix_size;
	int var; //first variable is 1; var<1 is invalid and -1 is default
	struct process_replacement_helper* next;
} pr_helper;

static void free_pr_helper(pr_helper *first){
	pr_helper *x, *y;	
	x = first;
	while(x != NULL){
		y = x->next;
		free(x);
		x = y;
	}
}

static pr_helper *process_replacement(const char *replacement){
	int max_var = 0;
	int tmpn;
	const char *x;
	pr_helper *current, *tmp_helper;
	pr_helper *first = malloc(sizeof(pr_helper));
	first->next = NULL;
	current = first;
	current->prefix = replacement;
	current->var = -1;
	current->next = NULL;
	for (x=replacement; *x!= '\0'; x++){
		if (*x == '$'){
			current->prefix_size = x - current->prefix;
			tmpn = 0;
			x++;
			while (*x >= '0' && *x <= '9'){
				tmpn = 10*tmpn + (int)(*x - '0');
				x++;
			}
			x--;
			max_var = (max_var < tmpn) ? tmpn : max_var;
			if (tmpn > 0){
				current->var = tmpn;
			} else {
				current->var = -1;
			}
			current->next = malloc(sizeof(pr_helper));
			current = current->next;
			current->prefix = x+1;
			current->next = NULL;
		}
	}
	current->prefix_size = x - current->prefix;
	current->var = -1;
	current->next = NULL;
	return first;
}

struct er_helper {
	char *string;
	struct er_helper *next;
};

static void free_er_helper(struct er_helper *first){
	struct er_helper *x, *y;
	x = first;
	while (x != NULL){
		y = x->next;
		if (x->string != NULL){
			free(x->string);
		}
		free(x);
		x = y;
	}
}

static char *replace_single_find(const char *tmploc, regmatch_t *matches, int max_var_num, int *printed_var_numbers, pr_helper *replacement){
	char *ret, *x, *varPos;
	int tmps, l;
	tmps = 1 + get_match_length(matches[0]);
	for (int i=0; i < max_var_num; i++){
		if (matches[i+1].rm_so >= 0){
			tmps += printed_var_numbers[i]\
				* get_match_length(matches[i+1]);
		}
	}
	for (pr_helper *prefixVar = replacement;
			prefixVar != NULL;
			prefixVar = prefixVar->next)
	{
		tmps += prefixVar->prefix_size;
	}

	ret = malloc(tmps);
	memcpy(ret, tmploc, matches[0].rm_so);
	x = ret + matches[0].rm_so;
	for (pr_helper *prefixVar = replacement;
			prefixVar != NULL;
			prefixVar = prefixVar->next)
	{
		memcpy(x, prefixVar->prefix, prefixVar->prefix_size);
		x += prefixVar->prefix_size;
		if (
				prefixVar->var > 0
				&& matches[prefixVar->var].rm_so >= 0)
		{
			varPos = tmploc + matches[prefixVar->var].rm_so;
			l = matches[prefixVar->var].rm_eo
				- matches[prefixVar->var].rm_so;
			memcpy(x, varPos, l);
			x += l;
		}
	}
	*x = '\0';
	return ret;
}


static char *combine_er_helper(const struct er_helper *first, const char* suffix){
	char *ret, *tmpret;
	int result_length = strlen(suffix) + 1;
	for (struct er_helper *x = first; x!=NULL; x=x->next){
		if (x->string != NULL){
			result_length += strlen(x->string);
		}
	}
	ret = malloc(result_length);
	tmpret = ret;
	for (struct er_helper *x = first; x!=NULL; x=x->next){
		if (x->string != NULL){
			for (char *tmpsource = x->string; *tmpsource!='\0'; tmpsource++){
				*tmpret++ = *tmpsource;
			}
		}
	}
	strcpy(tmpret, suffix);
	return ret;
}


static char *execute_replacement(const char *src, regex_t *reg, pr_helper *repl_helper){
	struct er_helper *current, *first = NULL;
	const char *tmploc;
	char *ret = NULL;
	int err = REG_ESPACE;
	int eflags = 0;
	int max_var_num = reg->re_nsub;
	int printed_var_numbers[max_var_num];
	size_t max_matches = 2 + max_var_num;
	regmatch_t matches[max_matches];

	for (int i=0; i < max_var_num; i++){
		printed_var_numbers[i] = 0;
	}
	for (pr_helper *tmp = repl_helper; tmp != NULL; tmp=tmp->next){
		if ((tmp->var >= 0) && (tmp->var < max_var_num)){
			printed_var_numbers[tmp->var] += 1;
		}
	}

	first = malloc(sizeof(struct er_helper));
	current = first;
	current->string = NULL;
	current->next = NULL;
	tmploc = src;
	do {
		err = regexec(reg, tmploc, max_matches, matches, eflags);
		switch (err){
			case 0:
			case REG_ESPACE:
				current->string = replace_single_find(
						tmploc,
						matches, max_var_num,
						printed_var_numbers,
						repl_helper);
				current->next = malloc(sizeof(struct er_helper));
				current = current->next;
				current->string = NULL;
				current->next = NULL;
				tmploc += matches[0].rm_eo;
				break;
			default:
				free_er_helper(first);
				return NULL;
		}
	} while (err == REG_ESPACE);
	ret = combine_er_helper(first, tmploc);
	free_er_helper(first);
	return ret;
}

char* CIMR1_string_replace(const char* src, const char* pattern, const char* replacement, const char* flags){
	char *ret;
	int err;
	regex_t reg;
	if (src == NULL || pattern == NULL) return NULL;
	int regflags = get_regex_flags(flags);
	pr_helper *repl_helper = process_replacement(replacement);
	if (repl_helper == NULL){
		return NULL;
	}

	err = regcomp(&reg, pattern, regflags);
	if (err != 0){
		return NULL;
	}
	ret = execute_replacement(src, &reg, repl_helper);
	free_pr_helper(repl_helper);
	regfree(&reg);
	return ret;
}
