#include "../include/util.h"

void* cstl_malloc(size_t sz) {
    return safemalloc(sz);
}

void* cstl_realloc(void* ptr, size_t sz) {
    return saferealloc(ptr, sz);
}

void cstl_free(void* ptr) {
    free(ptr);
}
