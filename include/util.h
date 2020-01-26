#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

void escapesh(char* str);
void runcmd(const char* command, int maxline, char* out);
int minsystem(const char* str);
void trimNewline(char* str);
void* safemalloc(size_t size);

#endif
