#include "../include/git.h"
#include "../include/util.h"

#include <stdlib.h>

#define MAXLINE 1000

/**
 *
 */
void git_user_init(git_user* user) {
    //Allocate for struct
    user = malloc(sizeof(git_user));

    //Allocate each string
    user->name = malloc(sizeof(char))
}

void git_get_user_global(git_user* user) {
    runcmd("git config --global user.name", MAXLINE, user->name);
    runcmd("git config --global user.email", MAXLINE, user->email);
    runcmd("git config --global user.signing_key", MAXLINE, user->signing_key);
}
