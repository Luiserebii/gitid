#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/c-stl/include/algorithm.h"
#include "../include/util.h"

void escapesh(char* str) {
    //Declare and load buffer with copy of str
    char buffer[strlen(str) + 1];
    strcpy(buffer, str);

    //Escape string to write
    char escapestr[] = "'\\''";
    int escsz = sizeof(escapestr) / sizeof(char);

    //Write initial '
    *str++ = '\'';

    //Write escaped values to str
    for(char* it = buffer; *it; ++it) {
        if(*it == '\'') {
            //Write '\''
            algorithm_copy(char*, escapestr, escapestr + escsz - 1, str, str);
        } else {
            *str++ = *it;
        }
    }
    //Close with ', and finally, '\0'
    *str++ = '\'', *str = '\0';
}

void runcmd(const char* command, int maxline, char* out) {
    FILE* proc;
    //Process logic in case of failure
    if((proc = popen(command, "r")) == NULL) {
        fprintf(stderr, "Internal error: Failure to execute \"%s\"\n", command);
        exit(1);
    }
    //Copy all output to string out
    int c;
    for(int i = 0; (c = getc(proc)) != EOF && i < maxline - 1; ++i) {
        *out++ = c;
    }
    //Close out
    *out = '\0';

    //Close process and return
    if(pclose(proc) == -1) {
        fprintf(stderr, "error: failure to close process from \"%s\"\n", command);
        exit(1);
    }
}

int minsystem(const char* str) {
    int code;
    if((code = system(str)) != -1) {
        return code;
    } else {
        fprintf(stderr, "error: failure to execute \"%s\"\n", str);
        exit(1);
    }
}

char* minfgets(char* s, int n, FILE* stream) {
    char* sret;
    if((sret = fgets(s, n, stream)) == NULL) {
        fprintf(stderr, "error reading file stream: potential unexpected EOF or other error");
        fprintf(stderr, "Dumping buffer contents:\n%s\n", s);
        exit(1);
    }
    return sret;
}

void trimNewline(char* str) {
    for(; *str; ++str) {
        if(*str == '\n') {
            *str = '\0';
            break;
        }
    }
}

void* safemalloc(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "error: memory allocation failed, system may be out of memory\n");
        exit(1);
    }
    return ptr;
}
