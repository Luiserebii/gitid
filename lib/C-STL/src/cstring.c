#include "../include/cstl/cstring.h"
#include <string.h>

void safestrcpy(char* dest, const char* src, size_t lim) {
    while(--lim && (*dest++ = *src++))
        ;
}

char* fstrcat(char* dest, const char* src) {
    while(*dest) {
        ++dest;
    }
    for(; (*dest = *src); ++dest, ++src)
        ;
    return dest;
}

char* sfstrcat(char* dest, const char* src, size_t lim) {
    while(*dest) {
        ++dest;
    }
    for(; --lim && (*dest = *src); ++dest, ++src)
        ;
    return dest;
}

void cstring_init(char** s) {
    *s = NULL;
}

char* cstring_create(const char* s) {
    char* st = CSTL_MALLOC(strlen(s) + 1);
    strcpy(st, s);
    return st;
}

void cstring_asn(char** s1, const char* s2) {
    CSTL_FREE(*s1);
    if(s2) {
        *s1 = cstring_create(s2);
    } else {
        *s1 = NULL;
    }
}

void cstring_destroy(char* s) {
    CSTL_FREE(s);
}
