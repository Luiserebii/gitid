#include "../include/git.h"
#include "../include/util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GIT_USER_MAXSTRING 1000

/**
 * Allocates space for a new git_user struct.
 */
git_user* git_user_init() {
    //Allocate for struct
    git_user* user = (git_user*) malloc(sizeof(git_user));

    //Allocate each string
    user->name = (char*) malloc(sizeof(char) * GIT_USER_MAXSTRING);
    user->email = (char*) malloc(sizeof(char) * GIT_USER_MAXSTRING);
    user->signing_key = (char*) malloc(sizeof(char) * GIT_USER_MAXSTRING);
}

/**
 * Obtains the global git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_global(git_user* user) {
    runcmd("git config --global user.name", GIT_USER_MAXSTRING, user->name);
    runcmd("git config --global user.email", GIT_USER_MAXSTRING, user->email);
    runcmd("git config --global user.signingkey", GIT_USER_MAXSTRING, user->signing_key);

    //Trim all inputs
    trimNewline(user->name), trimNewline(user->email), trimNewline(user->signing_key);
}

/**
 * Obtains the local git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_local(git_user* user) {
    runcmd("git config --local user.name", GIT_USER_MAXSTRING, user->name);
    runcmd("git config --local user.email", GIT_USER_MAXSTRING, user->email);
    runcmd("git config --local user.signingkey", GIT_USER_MAXSTRING, user->signing_key);
    
    //Trim all inputs
    trimNewline(user->name), trimNewline(user->email), trimNewline(user->signing_key);
}

/**
 * 
 */
void git_set_user_global(git_user* user) {
    //TODO: Generalize this size into some #define
    char cmd[10000] = "git config --global user.name ";
    strcat(cmd, user->name);
    strcat(cmd, " && git config --global user.email ");
    strcat(cmd, user->email);
    if(user->signing_key) {
        strcat(cmd, " && git config --global user.signingkey ");
        strcat(cmd, user->signing_key);
    }
    printf("%s\n", cmd);
    //TODO: Figure out how to handle non-zero exit codes
    minsystem(cmd);
}

/**
 *
 */
void git_set_user_local(git_user* user) {
    //TODO: Generalize this size into some #define
    char cmd[10000] = "git config --local user.name ";
    strcat(cmd, user->name);
    strcat(cmd, " && git config --local user.email ");
    strcat(cmd, user->email);
    if(user->signing_key) {
        strcat(cmd, " && git config --local user.signingkey ");
        strcat(cmd, user->signing_key);
    }

    //TODO: Figure out how to handle non-zero exit codes
    minsystem(cmd);
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

    git_user* user = git_user_init();
    git_get_user_global(user);

    printf("User obtained:\n name: %s | email: %s | signingKey: %s\n", user->name, user->email, user->signing_key);

    git_user_free(user);

}
