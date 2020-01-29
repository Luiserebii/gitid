#ifndef GIT_USER_H
#define GIT_USER_H

#include "../include/struct.h"

#include <stdio.h>

#define GIT_USER_BUFFER_MAX 1000

typedef struct {
    char* name;
    char* email;
    char* signing_key;
} git_user;

/**
 * Allocates space for a new git_user struct.
 */
git_user* git_user_init();

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
 * void git_user_set_name(git_user* user, const char* n);
 * void git_user_set_email(git_user* user, const char* e);
 * void git_user_set_signing_key(git_user* user, const char* sk);
 */
declare_struct_set_string(git_user, name, user, n);
declare_struct_set_string(git_user, email, user, e);
declare_struct_set_string(git_user, signing_key, user, sk);

/**
 * Writes git_user to FILE* stream.
 */
void git_user_write(git_user* user, FILE* stream);

/**
 * Clears all members, resetting them to NULL, but does not deallocate the struct.
 */
void git_user_clear(git_user* user);

/**
 * Frees git_user struct.
 */
void git_user_free(git_user* user);

#endif
