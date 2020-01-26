#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/util.h"
#include "../include/algorithm.h"

/**
 * Escapes any ' by replacing with '\'', wrapping the entire
 * string in '' to treat as a literal.
 *
 * Assumes the string has enough space to handle 2 additional characters
 * plus 3 characters for each ' the string contains. Otherwise, undefined
 * behavior can arise.
 */
void escapesh(char* str) {
    //Declare and load buffer with copy of str
    char buffer[strlen(str) + 1];
    strcpy(buffer, str);

    //Escape string to write
    char escapestr[] = "'\\''";
    int escsz = sizeof(escapestr) / sizeof(char);

    //Write escaped values to str
    for(char* it = buffer; *it; ++it) {
        if(*it == '\'') {
            //Write '\''
            algorithm_copy(char*, escapestr, escapestr + escsz - 1, str);
        } else {
            *str++ = *it;
        }
    }
}

/**
 * A wrapped call of the popen() function. Prints any error to the standard 
 * error stream and exits.
 *
 * Writes the command's output to out if successful.
 */
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


/**
 * A wrapped call of the stdlib int system() function. Prints any error
 * to the standard error stream and exits.
 *
 * Returns the exit code of the command run if successful.
 */
int minsystem(const char* str) {
    int code;
    if((code = system(str)) != -1) {
        return code;
    } else {
        fprintf(stderr, "error: failure to execute \"%s\"\n", str);
        exit(1);
    }
}

/**
 * Trims the string at the first newline character found.
 */
void trimNewline(char* str) {
    for(; *str; ++str) {
        if(*str == '\n') {
            *str = '\0';
            break;
        }
    }
}

/**
 * Wrapper function to handle all malloc() cases of failure.
 */
void* safemalloc(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "error: memory allocation failed, system may be out of memory\n");
        exit(1);
    }
    return ptr;
}
