#ifndef CSTL_CSTRING_H
#define CSTL_CSTRING_H

#include <stdlib.h>

/**
 * String OO-like functions: cstring
 *
 * The general idea is that a heap-allocated c-string can be either NULL, or
 * filled with contents. 
 *
 * The strange part of the semantics here, is that it is valid to destroy an
 * initialized c-string, and nothing is required to de-initialize a c-string.
 *
 * A class looking to use cstring, might set all cstring (char*) members to
 * NULL, and reserve deinit/destroy for the actual calling of cstring_destroy.
 */

/**
 * Initialize a c-string to a valid state, or, NULL.
 *
 * NOTE: The true interface for this function is:
 *
 * void cstring_init(char* s)
 *
 * Macros have simply been use to unify the interface.
 */
#define cstring_init(s) cstring_init_(&s)
void cstring_init_(char** s);

/**
 * Create a new c-string, and fill it with the contents of c-string s.
 */
char* cstring_create(const char* s);

/**
 * Assign an initialized c-string s1 to a new c-string s2, where s1 is a pointer
 * to a c-string. (Yes, this interface is a little screwed.)
 *
 * This will cause a deallocation, if s1 already has been filled.
 * As NULL is a valid state for a char*, this is checked for; if s2 is NULL,
 * then s1 will simply be freed and will stay as NULL.
 * 
 * NOTE: The true interface for this function is:
 *
 * void cstring_asn(char* s1, const char* s2)
 */
#define cstring_asn(s1, s2) cstring_asn_(&s1, s2)
void cstring_asn_(char** s1, const char* s2);

/**
 * Destroys and releases the memory for a c-string.
 */
void cstring_destroy(char* s);

/**
 * Utility functions for handling c-strings
 */

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
 * fstrcat, as in, "fast" strcat.
 * Returns a pointer to the last element, to try to alleviate future O(n) calls.
 */
char* fstrcat(char* dest, const char* src);

/**
 * sfstrcat, as in, "safe-fast" strcat.
 * Guarantees concatenating as many characters as possible from src to dest.
 * Returns a pointer to the last element, to try to alleviate future O(n) calls.
 */
char* sfstrcat(char* dest, const char* src, size_t lim);

#endif
