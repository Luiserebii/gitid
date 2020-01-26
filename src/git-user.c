#include "../include/git-user.h"
#include "../include/util.h"

#include <stdlib.h>
#include <string.h>

git_user* git_user_init() {
    //Allocate for struct
    git_user* user = safemalloc(sizeof(git_user));

    //Allocate each string
    user->name = safemalloc(GIT_USER_MAXSTRING);
    user->email = safemalloc(GIT_USER_MAXSTRING);
    
    //Optional, so set to NULL by default
    user->signing_key = NULL;
}

void git_user_set_signing_key(git_user* user, const char* sk) {
    //Free if not NULL, before allocating
    if(user->signing_key) {
        free(user->signing_key);
    }
    user->signing_key = safemalloc(GIT_USER_MAXSTRING);
    if(sk) {
        strcpy(user->signing_key, sk);
    }
}

void git_user_free(git_user* user) {
    //Free members
    free(user->name);
    free(user->email);
    if(user->signing_key) {
        free(user->signing_key);
    }

    //Free struct
    free(user);
}
