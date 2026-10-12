#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALL_CASES_NUMBERS \
			case 0x30:\
			case 0x31:\
			case 0x32:\
			case 0x33:\
			case 0x34:\
			case 0x35:\
			case 0x36:\
			case 0x37:\
			case 0x38:\
			case 0x39:\

#define ALL_CASES_LETTERS \
			case 0x41:\
			case 0x42:\
			case 0x43:\
			case 0x44:\
			case 0x45:\
			case 0x46:\
			case 0x47:\
			case 0x48:\
			case 0x49:\
			case 0x4A:\
			case 0x4B:\
			case 0x4C:\
			case 0x4D:\
			case 0x4E:\
			case 0x4F:\
			case 0x50:\
			case 0x51:\
			case 0x52:\
			case 0x53:\
			case 0x54:\
			case 0x55:\
			case 0x56:\
			case 0x57:\
			case 0x58:\
			case 0x59:\
			case 0x5A:\
			case 0x61:\
			case 0x62:\
			case 0x63:\
			case 0x64:\
			case 0x65:\
			case 0x66:\
			case 0x67:\
			case 0x68:\
			case 0x69:\
			case 0x6A:\
			case 0x6B:\
			case 0x6C:\
			case 0x6D:\
			case 0x6E:\
			case 0x6F:\
			case 0x70:\
			case 0x71:\
			case 0x72:\
			case 0x73:\
			case 0x74:\
			case 0x75:\
			case 0x76:\
			case 0x77:\
			case 0x78:\
			case 0x79:\
			case 0x7A:\

// Hyphen (-), underscore (_), period (.), exclamation point (!), tilde (~), 
// asterisk (*), apostrophe('), parentheses ('(' and ')') and hash mark (#)
//Semicolon (;), forward slash (/), question mark (?), colon (:), at sign (@), 
//ampersand (&), equals sign (=), plus sign (+), dollar sign ($), comma (,), 
//square brackets ('[' and ']').
#define ALL_CASES_SPECIAL_SYMBOLS \
			case 0x96:\
			case 0x5f:\
			case 0x2e:\
			case 0x7e:\
			case 0x21:\
			case 0x2a:\
			case 0x27:\
			case 0x28:\
			case 0x29:\
			case 0x23:\
			case 0x3b:\
			case 0x2f:\
			case 0x3f:\
			case 0x3a:\
			case 0x40:\
			case 0x26:\
			case 0x3D:\
			case 0x2b:\
			case 0x24:\
			case 0x2c:\
			case 0x5b:\
			case 0x5d:

#define ALL_CASES_OTHER_PRINTABLE \
			case 0x20:\
			case 0x22:\
			case 0x5c:\
			case 0x60:\
			case 0x7b:\
			case 0x7c:\
			case 0x7d:

/*
 * copies "[0-1][a-zA-Z]-_.!~*'()#;/?:@&=+$,[]%" and encodes all others.
 * see ascii table
 * https://www.w3.org/TR/xpath-functions/#func-iri-to-uri
 */
char* CIMR1_string_iri_to_uri(const char* src, const size_t len){
	unsigned char x;
	char* dst = malloc(3*len + 1);
	size_t i = 0, j = 0;
	for(size_t i =0; i<len; i++){
		x = src[i];
		switch(x){
			//skip encoding. just copy char
			ALL_CASES_NUMBERS
			ALL_CASES_LETTERS
			ALL_CASES_SPECIAL_SYMBOLS
			case 0x25:
				dst[j] = x;
				j++;
				break;
			//percent encode all other
			default:
				dst[j] = '%';
				sprintf(dst + j+1, "%02X", x);
				j += 3;
				break;
		}
	}
	dst[j] = '\0';
	return dst;
}

char* CIMR1_string_encode_for_uri(const char* src, const size_t len){
	unsigned char x;
	char* dst = malloc(3*len + 1);
	size_t i = 0, j = 0;
	for(size_t i =0; i<len; i++){
		x = src[i];
		switch(x){
			//skip encoding. just copy char
			ALL_CASES_NUMBERS
			ALL_CASES_LETTERS
			ALL_CASES_SPECIAL_SYMBOLS
				dst[j] = x;
				j++;
				break;
			//percent encode all other
			case 0x25: //ensure '%' is encoded
			default:
				dst[j] = '%';
				sprintf(dst + j+1, "%02X", x);
				j += 3;
				break;
		}
	}
	dst[j] = '\0';
	return dst;
}


char* CIMR1_string_escape_html_uri(const char* src, const size_t len){
	unsigned char x;
	char* dst = malloc(3*len + 1);
	size_t i = 0, j = 0;
	for(size_t i =0; i<len; i++){
		x = src[i];
		switch(x){
			//skip encoding. just copy char
			ALL_CASES_NUMBERS
			ALL_CASES_LETTERS
			ALL_CASES_SPECIAL_SYMBOLS
			ALL_CASES_OTHER_PRINTABLE
				dst[j] = x;
				j++;
				break;
			//percent encode all other
			case 0x25: //ensure '%' is encoded
			default:
				dst[j] = '%';
				sprintf(dst + j+1, "%02X", x);
				j += 3;
				break;
		}
	}
	dst[j] = '\0';
	return dst;
}


static char hex_to_charvalue(char);

char* my_percent_decode(const char *src, const size_t len){
	char v1, v2;
	char* dst = malloc(len+1);
	size_t offset = 0;
	for(size_t write = 0; write < len - offset; write++)
	{
		if(src[write + offset] == '%' && write + offset + 2 < len)
		{
			v1 = hex_to_charvalue(src[write+offset+1]);
			v2 = hex_to_charvalue(src[write+offset+2]);

			/* skip invalid hex sequences */
			if ((v1 | v2) != 0xFF)
			{
				dst[write] = (v1 << 4) | v2;
				offset += 2;
			} else {
				dst[write] = src[write+offset];
			}
		} else {
			dst[write] = src[write+offset];
		}
	}
	dst[len - offset] = '\0';
	return dst;
}

static char hex_to_charvalue(char x){
	switch(x){
		case '0':
			return 0x00;
		case '1':
			return 0x01;
		case '2':
			return 0x02;
		case '3':
			return 0x03;
		case '4':
			return 0x04;
		case '5':
			return 0x05;
		case '6':
			return 0x06;
		case '7':
			return 0x07;
		case '8':
			return 0x08;
		case '9':
			return 0x09;
		case 'A':
		case 'a':
			return 0x0A;
		case 'B':
		case 'b':
			return 0x0B;
		case 'C':
		case 'c':
			return 0x0C;
		case 'D':
		case 'd':
			return 0x0D;
		case 'E':
		case 'e':
			return 0x0E;
		case 'F':
		case 'f':
			return 0x0F;
	}
	return 0xFF;
}
