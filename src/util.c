#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/util.h"
#include "../include/algorithm.h"

#define MAXLINE 1000

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
    int escsz = 5;
    char escapestr[] = "'\\''";

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
        fprintf(stderr, "Internal error: Failure to close process from \"%s\"\n", command);
        exit(1);
    }
}
