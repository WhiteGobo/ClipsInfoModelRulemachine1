#include "data.h"

int CLIPSValue_cmp(CLIPSValue x, CLIPSValue y){
	if(x.header->type != y.header->type){
		return x.header->type - y.header->type;
	}
	switch(x.header->type){
		case VOID_TYPE:
			return 0;
		case STRING_TYPE:
		case SYMBOL_TYPE:
			return strcmp(x.lexemeValue->contents, y.lexemeValue->contents);
		case FLOAT_TYPE:
			double xd = x.floatValue->contents;
			double yd = y.floatValue->contents;
			if(xd < yd){
				return -1;
			} else if (xd > yd){
				return 1;
			}
			return 0;
		case INTEGER_TYPE:
			long xi = x.floatValue->contents;
			long yi = y.floatValue->contents;
			if(xi < yi){
				return -1;
			} else if (xi > yi){
				return 1;
			}
			return 0;
		case FACT_ADDRESS_TYPE:
		case INSTANCE_ADDRESS_TYPE:
		case INSTANCE_NAME_TYPE:
		case MULTIFIELD_TYPE:
		case EXTERNAL_ADDRESS_TYPE:
	}
	fprintf(stderr, "WARNING CLIPSValue_cmp not fully implemented\n");
	return 0;
}
