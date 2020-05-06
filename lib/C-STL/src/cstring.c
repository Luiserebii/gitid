#include "../include/cstl/cstring.h"
#include <string.h>
#include "../include/cstl/memory.h"

void cstring_init_(char** s) {
    *s = NULL;
}

char* cstring_create(const char* s) {
    char* st = cstl_malloc(strlen(s) + 1);
    strcpy(st, s);
    return st;
}

void cstring_asn_(char** s1, const char* s2) {
    cstl_free(*s1);
    if(s2) {
        *s1 = cstring_create(s2);
    } else {
        *s1 = NULL;
    }
}

void cstring_destroy(char* s) {
    cstl_free(s);
}

void safestrcpy(char* dest, const char* src, size_t lim) {
    //Minor dev-note; *dest++ = *src++ can resolve to '\0'
    //being set, rendering the final statement potentially pointless
    while(--lim && (*dest++ = *src++))
        ;
    *dest = '\0';
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
