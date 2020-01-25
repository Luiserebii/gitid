#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    //Write escaped values to str
    for(char* it = buffer; *it; ++it, ++str) {
        if(*it == ''') {
            //Write '\''

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
        fprintf("Internal error: Failure to execute \"%s\"\n", str);
        exit(1);
    }
}
