#ifndef GIT_USER_H
#define GIT_USER_H

#include "../include/struct.h"

#define CSTL_MALLOC safemalloc
#define CSTL_REALLOC saferealloc
#include <cstl/string.h>

#include <stdio.h>

typedef struct {
    string* name;
    string* email;
    string* signing_key;
} git_user;

/**
 * Allocates space for a new git_user struct.
 */
git_user* git_user_init(void);

/**
 * This is meant to provide a more OOP constructor, where the invariant
 * of the struct containing a name and email is satisfied. The struct-object
 * is therefore a little more guaranteed to never be left incomplete.
 *
 * In the event that NULL is passed in either parameter, an error is thrown
 * and the application ends.
 */
git_user* git_user_safe_init(const char* n, const char* e);

/**
 * Set the values of dest to the values of src. Note that the function
 * does not disrupt any pointers; the git_user struct pointer 
 * is guaranteed to stay. 
 *
 * The only pointers which may change may be values such as strings, 
 * which are freed and re-allocated using the set_string macro.
 */
void git_user_set(git_user* dest, const git_user* src);

/**
 * Writes git_user to FILE* stream.
 */
void git_user_write(const git_user* user, FILE* stream);

/**
 * Clears all members, clearing recursively (in this case, by calling string_free) 
 * but does not deallocate the struct.
 */
void git_user_clear(git_user* user);

/**
 * Frees git_user struct.
 */
void git_user_free(git_user* user);

#endif
