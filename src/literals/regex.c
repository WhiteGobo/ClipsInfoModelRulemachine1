#include "literals.h"
#include "regex.h"

bool Literal_check_value_against_regex(Literal* x, const char* regstring){
	int err;
	regex_t reg;
	const char *val = Literal_get_value(x);
	if(val == NULL){
		return false;
	}
	err = regcomp(&reg, regstring, REG_EXTENDED);
	if (err != 0){
		fprintf(stderr, "ERROR REGEX failed\n");
		return false;
	}
	err = regexec(&reg, val, 0, NULL, 0);
	regfree(&reg);
	return err == 0;
}
