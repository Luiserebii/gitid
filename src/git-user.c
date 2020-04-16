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
    user->signing_key = string_init();

    return user;


void git_user_set(git_user* dest, const git_user* src) {
    string_assign(dest, string_begin(src->name), string_end(src->name));
    string_assign(dest, string_begin(src->email), string_end(src->email));
    string_assign(dest, string_begin(src->signing_key), string_end(src->signing_key));
}

void git_user_write(const git_user* user, FILE* stream) {
    fprintf(stream, "Name: %s\nEmail: %s\n", string_cstr(user->name), string_cstr(user->email));
    if(string_size(user->signing_key)) {
        fprintf(stream, "Signing Key: %s\n", string_cstr(user->signing_key));
    }
}

void git_user_clear(git_user* user) {
    //Clear members
    string_clear(user->name);
    string_clear(user->email);
    string_clear(user->signing_key);
}

void git_user_free(git_user* user) {
    //Free members
    string_free(user->name);
    string_free(user->email);
    string_free(user->signing_key);

    //Free struct
    free(user);
}
