#ifndef CSTL_CUSTOM_MEMORY

#include <stdlib.h>

void* cstl_malloc(size_t sz) {
    return malloc(sz);
}

void* cstl_realloc(void* ptr, size_t sz) {
    return realloc(ptr, sz);
}

void cstl_free(void* ptr) {
    free(ptr);
}

#endif
