#ifndef CSTL_MEMORY
#define CSTL_MEMORY

#include <stdlib.h>

void* cstl_malloc(size_t sz);
void* cstl_realloc(void* ptr, size_t sz);
void cstl_free(void* ptr);

#endif
