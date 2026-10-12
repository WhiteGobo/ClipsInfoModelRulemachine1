#include <stdio.h>
#include <getopt.h>
#include <regex.h>
#include "terms.h"

const char* name;

#define _EX_ "http://example.org/example#"
#define _RDF_ "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define _XS_ "http://www.w3.org/2001/XMLSchema#"
#define _FUNC_ "http://www.w3.org/2007/rif-builtin-function#"
#define _OWL_ "http://www.w3.org/2002/07/owl#"
#define _PRED_ "http://www.w3.org/2007/rif-builtin-predicate#"
#define _RDFS_ "http://www.w3.org/2000/01/rdf-schema#"
#define _RIF_ "http://www.w3.org/2007/rif#"
#define _RIFBUILTIN_ "http://www.w3.org/2007/rif-builtin-function#"
#define _RIFENTAIL_ "http://www.w3.org/ns/entailment/"
#define _SYNTAX_ "http://www.w3.org/ns/formats/"

typedef enum {
	NT_IRI,
	NT_TYPEDLITERAL,
	NT_LANGLITERAL,
} NAMETYPE;

struct ret_PARSE_NAME {
	NAMETYPE type;
	char* value;
	char* suffix;
};

static int parse_args(int argc, char *argv[]);
static void fprintf_CLIPSValue(FILE*, CLIPSValue);
static struct ret_PARSE_NAME parse_name(const char*);
static char* parse_shortiri(const char* source, regmatch_t *pmatch, size_t pos_prefix, size_t pos_suffix);

int main(int argc, char *argv[]){
	int err;
	err = parse_args(argc, argv);
	if (err != 0){
		exit(EXIT_FAILURE);
	}
	struct ret_PARSE_NAME x = parse_name(name);
	if (x.value == NULL){
		fprintf(stderr, "Failed to parse name: %s\n", name);
		exit(EXIT_FAILURE);
	}
	Environment* env = CreateEnvironment();
	CLIPSValue cv;
	switch (x.type){
		case NT_IRI:
			cv = generate_clipssymbol_from_iri(env, x.value);
			break;
		case NT_TYPEDLITERAL:
	  		cv = generate_clipsvalue_from_typedliteral(env, x.value, x.suffix);
	 		break;
		case NT_LANGLITERAL:
	  		cv = generate_clipsvalue_from_langliteral(env, x.value, x.suffix);
			break;
	}
	//fprintf(stdout, "return:\n");
	fprintf_CLIPSValue(stdout, cv);
	fprintf(stdout, "\n");
	exit(EXIT_SUCCESS);
}

static char* parse_shortiri(const char* source, regmatch_t *pmatch, size_t pos_prefix, size_t pos_suffix)
{
	size_t len_prefix, len_suffix, len_ret;
	const char *prefix, *suffix;
	char* ret;
	suffix = source + pmatch[pos_suffix].rm_so;
	prefix = source + pmatch[pos_prefix].rm_so;
	len_prefix = pmatch[pos_prefix].rm_eo - pmatch[pos_prefix].rm_so;
	len_suffix = pmatch[pos_suffix].rm_eo - pmatch[pos_suffix].rm_so;
	fprintf(stderr, "qq %s %s\n", suffix, prefix);
	len_ret = len_suffix + 1;
#define HANDLE_CASE_PREFIX(pfx_short, pfx_long) \
	if (sizeof(pfx_short)-1 == len_prefix && 0==memcmp(prefix, pfx_short, len_prefix)){\
		len_ret += sizeof(pfx_long);\
		ret = malloc(len_ret);\
		memcpy(ret, pfx_long, sizeof(pfx_long)-1);\
		memcpy(ret + sizeof(pfx_long)-1, suffix, len_suffix);\
		ret[len_ret] = '\0';\
		return ret;\
	}
	HANDLE_CASE_PREFIX("ex", _EX_);
	HANDLE_CASE_PREFIX("rdf", _RDF_);
	HANDLE_CASE_PREFIX("xs", _XS_);
	HANDLE_CASE_PREFIX("func", _FUNC_);
	HANDLE_CASE_PREFIX("pred", _PRED_);
	return NULL;
}

static char* cpy_match(regmatch_t *pmatch, size_t pos, const char* original){
	size_t len;
	const char* x;
	char* ret;
	len = pmatch[pos].rm_eo - pmatch[pos].rm_so;
	x = original + pmatch[pos].rm_so;
	ret = malloc(len + 1);
	memcpy(ret, x, len);
	ret[len] = '\0';
	return ret;
}

static struct ret_PARSE_NAME parse_name(const char* x){
	int err;
	regmatch_t matches[5];
	struct ret_PARSE_NAME ret = {
		.value = NULL,
	};
	regex_t reegex;

	if(regcomp(&reegex, "^([^:<\"]+)[:](.+)$", REG_EXTENDED)){
		fprintf(stderr, "RegEx failed to compile.\n");
		return ret;
	}
	err = regexec( &reegex, x, 5, matches, 0);
	regfree(&reegex);
	if(!err){
		ret.value = parse_shortiri(x, matches, 1, 2);
		if (ret.value == NULL){
			fprintf(stderr, "Found shortiri but couldnt "
					"translate prefix\n");
			return ret;
		}
		ret.type = NT_IRI;
		ret.suffix = NULL;
		return ret;
	}

	if(regcomp(&reegex, "^<([^>]+)>$", REG_EXTENDED)){
		fprintf(stderr, "RegEx failed to compile.\n");
		return ret;
	}
	err = regexec( &reegex, x, 5, matches, 0);
	regfree(&reegex);
	if(!err){
		ret.type = NT_IRI;
		ret.value = cpy_match(matches, 1, x);
		ret.suffix = NULL;
		return ret;
	}

	if(regcomp(&reegex, "^\"([^\"]*)\"\\^\\^([^:<\"]+)[:](.+)$", REG_EXTENDED)){
		fprintf(stderr, "RegEx failed to compile.\n");
		return ret;
	}
	err = regexec( &reegex, x, 5, matches, 0);
	regfree(&reegex);
	if(!err){
		ret.suffix = parse_shortiri(x, matches, 2, 3);
		if (ret.suffix == NULL){
			fprintf(stderr, "Found shortiri but couldnt "
					"translate prefix\n");
			return ret;
		}
		ret.type = NT_TYPEDLITERAL;
		ret.value = cpy_match(matches, 1, x);
		return ret;
	}

	if(regcomp(&reegex, "^\"([^\"]*)\"\\^\\^<(.+)>$", REG_EXTENDED)){
		fprintf(stderr, "RegEx failed to compile.\n");
		return ret;
	}
	err = regexec( &reegex, x, 5, matches, 0);
	regfree(&reegex);
	if(!err){
		ret.type = NT_TYPEDLITERAL;
		ret.value = cpy_match(matches, 1, x);
		ret.suffix = cpy_match(matches, 2, x);
		return ret;
	}

	if(regcomp(&reegex, "^\"([^\"]*)\"@(.*)$", REG_EXTENDED)){
		fprintf(stderr, "RegEx failed to compile.\n");
		return ret;
	}
	err = regexec( &reegex, x, 5, matches, 0);
	regfree(&reegex);
	if(!err){
		ret.type = NT_LANGLITERAL;
		ret.value = cpy_match(matches, 1, x);
		ret.suffix = cpy_match(matches, 2, x);
		return ret;
	}

	if(regcomp(&reegex, "^\"([^\"]*)\"$", REG_EXTENDED)){
		fprintf(stderr, "RegEx failed to compile.\n");
		return ret;
	}
	err = regexec( &reegex, x, 5, matches, 0);
	regfree(&reegex);
	if(!err){
		ret.type = NT_TYPEDLITERAL;
		ret.value = cpy_match(matches, 1, x);
		ret.suffix = NULL;
		return ret;
	}

	fprintf(stderr, "Failed to parse %s\n", x);
	return ret;
}

static void print_usage(FILE* f, const char* name){
	fprintf(stderr, "Usage: %s name\n", name);
}

static int parse_args(int argc, char *argv[]){
	int opt;
	while ((opt = getopt(argc, argv, "nt:")) != -1) {
		switch (opt) {
			default: /* '?' */
				print_usage(stderr, argv[0]);
				return 1;
		}
	}
	if (optind >= argc) {
		print_usage(stderr, argv[0]);
		return 1;
	}
	name = argv[optind];
	return 0;
}

static void fprintf_CLIPSValue(FILE* f, CLIPSValue val){
	switch(val.header->type){
                case STRING_TYPE:
			fprintf(f, "\"%s\"", val.lexemeValue->contents);
			return;
                case SYMBOL_TYPE:
			fprintf(f, "%s", val.lexemeValue->contents);
			return;
                case INTEGER_TYPE:
			fprintf(f, "not implemented");
			return;
                case FLOAT_TYPE:
			fprintf(f, "not implemented");
			return;
		case VOID_TYPE:
			fprintf(f, "(ERROR)");

	}
}
