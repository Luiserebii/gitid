#ifndef GIT_USER_H
#define GIT_USER_H

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
 * If new, allocate the signing_key field, and takes an optional char* to set the 
 * newly allocated field to. If NULL is passed, only allocation occurs.
 */
void git_user_set_signing_key(git_user* user, const char* sk);

/**
 * Frees git_user struct.
 */
void git_user_free(git_user* user);

#endif
