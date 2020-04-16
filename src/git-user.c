#include "../include/git-user.h"
#include "../include/struct.h"
#include "../include/util.h"

#define CSTL_MALLOC safemalloc
#define CSTL_REALLOC saferealloc
#include <cstl/string.h>

#include <stdio.h>
#include <stdlib.h>

git_user* git_user_init(void) {
    //Allocate for struct
    git_user* user = safemalloc(sizeof(git_user));

    //Initialize all values
    user->name = string_init();
    user->email = string_init();
    user->signing_key = string_init();

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

    user->name = string_init_cstr(n);
    user->email = string_init_cstr(e);

    //Initialize other values
    user->signing_key = NULL;

    return user;
}

void git_user_set(git_user* dest, const git_user* src) {
    dest->name = 
    git_user_set_name(dest, src->name);
    git_user_set_email(dest, src->email);
    if(src->signing_key) {
        git_user_set_signing_key(dest, src->signing_key);
    }
}

void git_user_write(const git_user* user, FILE* stream) {
    fprintf(stream, "Name: %s\nEmail: %s\n", user->name, user->email);
    if(user->signing_key) {
        fprintf(stream, "Signing Key: %s\n", user->signing_key);
    }
}

void git_user_clear(git_user* user) {
    //Free members
    free(user->name);
    free(user->email);
    free(user->signing_key);

    //Reset to NULL
    user->name = user->email = user->signing_key = NULL;
}

void git_user_free(git_user* user) {
    //Free members
    free(user->name);
    free(user->email);
    free(user->signing_key);

    //Free struct
    free(user);
}
