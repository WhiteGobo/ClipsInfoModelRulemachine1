#pragma once

char* CIMR1_string_substring(const char*, int start, int end);
char* CIMR1_string_string_cut(const char*, int start);
char* CIMR1_string_uppercase(const char*);
char* CIMR1_string_lowercase(const char*);
char* CIMR1_string_encode_for_uri(const char*, const size_t len);
char* CIMR1_string_iri_to_uri(const char*, const size_t len);
char* CIMR1_string_escape_html_uri(const char*, const size_t len);
char* CIMR1_string_replace(const char* source, const char* pattern, const char* replacement, const char* flags);
char* CIMR1_string_substring_after(const char* source, const char* query);
char* CIMR1_string_substring_before(const char* source, const char* query);

bool CIMR1_string_contains(const char* source, const char* query);
bool CIMR1_string_matches(const char*, const char*);
bool CIMR1_string_starts_with(const char* source, const char* query);
bool CIMR1_string_ends_with(const char* source, const char* query);
