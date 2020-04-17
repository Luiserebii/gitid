#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#include <cstl/string.h>

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
 * string-like version of fgets(). Error-checked.
 *
 * Reads characters into the string until either a newline
 * or EOF is encountered. If a newline is encountered, it is
 * included with the string.
 */
void string_fgets(string* s, FILE* stream);

/**
 * string-like version of fgets(). Error-checked.
 *  
 * Reads characters into the string until either a newline
 * or EOF is encountered. If a newline is encountered, it is
 * NOT included with the string.
 */
void string_fgets_min(string* s, FILE* stream);

/**
 * Trims the string at the first newline character found.
 */
void trimNewline(char* str);

/**
 * Guarantees copying lim-1 chars to the destination string, reserving at least
 * one for a null character ('\0'). Strings copied are thus guaranteed to be
 * null-terminated, and provides safety by truncating silently.
 */
void safestrcpy(char* dest, const char* src, size_t lim);

/**
 * Guarantees concatenating as many characters as possible from src to dest.
 * This is intended to act as a convenience macro, to mimic safestrcpy's usage.
 */
#define safestrcat(dest, src, dest_lim) strncat(dest, src, dest_lim - strlen(dest) - 1)

/**
 * Wrapper function to handle all malloc() cases of failure.
 */
void* safemalloc(size_t size);

/**
 * Wrapper function to handle all realloc() cases of failure.
 */
void* saferealloc(void* p, size_t size);

/**
 * Generates a filepath relative to the HOME environment variable. Simply put,
 * if HOME=/home/usr1, and path is .gitid/gitid, the returned path within
 * the buffer will be /home/usr1/.gitid/gitid.
 *
 * The buffer is suggested to use PATH_MAX + 1 limit.
 */
void generate_path_home(char* buffer, const char* path, size_t buffer_lim);

/**
 * Parses out the name of the repository from a git repository URL.
 */
void parseGitURLName(char* url);

#endif
