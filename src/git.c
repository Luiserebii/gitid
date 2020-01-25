#include "../include/git.h"
#include "../include/util.h"

#include <stdlib.h>
#include <stdio.h>

#define GIT_USER_MAXSTRING 1000

/**
 * Allocates space for a new git_user struct.
 */
void git_user_init(git_user* user) {
    //Allocate for struct
    user = malloc(sizeof(git_user));

    //Allocate each string
    user->name = malloc(sizeof(char) * GIT_USER_MAXSTRING);
    user->email = malloc(sizeof(char) * GIT_USER_MAXSTRING);
    user->signing_key = malloc(sizeof(char) * GIT_USER_MAXSTRING);
}

/**
 * Obtains the global git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_global(git_user* user) {
    runcmd("git config --global user.name", GIT_USER_MAXSTRING, user->name);
    runcmd("git config --global user.email", GIT_USER_MAXSTRING, user->email);
    runcmd("git config --global user.signing_key", GIT_USER_MAXSTRING, user->signing_key);
}

/**
 * Obtains the local git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_local(git_user* user) {
    runcmd("git config --local user.name", GIT_USER_MAXSTRING, user->name);
    runcmd("git config --local user.email", GIT_USER_MAXSTRING, user->email);
    runcmd("git config --local user.signing_key", GIT_USER_MAXSTRING, user->signing_key);
}

/**
 * 
 */
void git_set_user_global(git_user* user) {
    
}

/**
 * Frees git_user struct.
 */
void git_user_free(git_user* user) {
    //Free members
    free(user->name);
    free(user->email);
    free(user->signing_key);

    //Free struct
    free(user);
}

int main() {

    git_user* user;
    git_user_init(user);
    git_get_user_global(user);

    printf("User obtained:\n name: %s | email: %s | signingKey: %s", user->name, user->email, user->signing_key);

    git_user_free(user);
}
