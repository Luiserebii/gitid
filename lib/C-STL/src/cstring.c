#include "../include/cstl/cstring.h"

void safestrcpy(char* dest, const char* src, size_t lim) {
    while(--lim && (*dest++ = *src++))
        ;
    *dest = '\0';
}
