#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Escapes any ' by replacing with '\'', wrapping the entire
 * string in '' to treat as a literal.
 *
 * Assumes the string has enough space to handle 2 additional characters
 * plus 3 characters for each ' the string contains. Otherwise, undefined
 * behavior can arise.
 */
void escapesh(char* str);

/**
 * A wrapped call of the popen() function. Prints any error to the standard 
 * error stream and exits.
 *
 * Writes the command's output to out if successful.
 */
void runcmd(const char* command, int maxline, char* out);

/**
 * A wrapped call of the stdlib int system() function. Prints any error
 * to the standard error stream and exits.
 *
 * Returns the exit code of the command run if successful.
 */
int minsystem(const char* str);

/**
 * A wrapped call of the fgets() function. Prints any error to the standard
 * error stream and exits.
 *
 * Returns the char* returned by fgets otherwise.
 */
char* minfgets(char* s, int n, FILE* stream);

/**
 * Trims the string at the first newline character found.
 */
void trimNewline(char* str);

/**
 * Wrapper function to handle all malloc() cases of failure.
 */
void* safemalloc(size_t size);

/**
 * Parses out the name of the repository from a git repository URL.
 */
void parseGitURLName(char* url);

#endif
