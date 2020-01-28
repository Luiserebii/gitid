#include "../include/git-user.h"
#include "../include/struct.h"
#include "../include/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

git_user* git_user_init() {
    //Allocate for struct
    git_user* user = safemalloc(sizeof(git_user));

    //Initialize all values
    user->name = user->email = user->signing_key = NULL;

    return user;
}

git_user* git_user_safe_init(const char* n, const char* e) {
    //Throw in the event either param is null
    if(!n || !e) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }

    //Allocate for struct
    git_user* user = safemalloc(sizeof(git_user));

    //Set name and email in parameter
    git_user_set_name(user, n);
    git_user_set_email(user, e);

    //Initialize other values
    user->signing_key = NULL;

    return user;
}

/**
 * void git_user_set_signing_key(git_user* user, const char* sk)
 */
define_struct_set_string(git_user, name, user, n);
define_struct_set_string(git_user, email, user, e);
define_struct_set_string(git_user, signing_key, user, sk);

void git_user_write(git_user* user, FILE* stream) {
    fprintf(stream, "Name: %s\nEmail: %s\n", user->name, user->email);
    if(user->signing_key) {
        fprintf(stream, "Signing Key: %s\n", user->signing_key);
    }
}

void git_user_free(git_user* user) {
    //Free members
    free(user->name);
    free(user->email);
    free(user->signing_key);

    //Free struct
    free(user);
}
