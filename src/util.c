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
        fprintf(stderr, "Internal error: Failure to execute \"%s\"\n", str);
        exit(1);
    }
}
