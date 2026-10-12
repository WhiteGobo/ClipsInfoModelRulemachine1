#pragma once

#include <stddef.h>

/*
 * ensure string doesnt contains following symbols and can be decoded with
 * percent_decode:
 * "^@"
 */
char* percent_encode(const char *src, const size_t len);
char* percent_decode(const char *src, const size_t len);
