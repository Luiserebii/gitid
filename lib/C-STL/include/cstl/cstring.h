#ifndef CSTL_CSTRING_H
#define CSTL_CSTRING_H

#include <string.h>

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

#endif
