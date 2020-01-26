#ifndef GIT_USER_H
#define GIT_USER_H

#include "../include/struct.h"

#define GIT_USER_MAXSTRING 1000

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
 * void git_user_set_signing_key(git_user* user, const char* sk);
 */
declare_struct_set_string(git_user, signing_key, user, sk)

/**
 * Frees git_user struct.
 */
void git_user_free(git_user* user);

#endif
