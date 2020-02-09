#include "../include/git-user.h"
#include "../include/struct.h"
#include "../include/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

git_user* git_user_init(void) {
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
    //Initialize to NULL so we don't get errors by set_id_name TODO: make this... a little less hacky
    //Explanation; we will get a terrible error if we don't, as user->name currently contains garbage
    //values; free() works if the struct is in a valid state, e.g. either is a valid address currently
    //pointing to memory, or is NULL and therefore fine to use. However, if not, then we have an issue
    //of attempting to free an invalid address!!! So, as a hacky solution... simply set to NULL before
    //setting
    user->name = user->email = NULL;

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

void git_user_set(git_user* dest, const git_user* src) {
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
