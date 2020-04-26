#include "../include/git-user.h"
#include "../include/struct.h"
#include "../include/util.h"

#define CSTL_MALLOC safemalloc
#define CSTL_REALLOC saferealloc
#include <cstl/string.h>

#include <stdio.h>
#include <stdlib.h>

void git_user_init(git_user* gu) {
    //Initialize all values
    string_init(&gu->name);
    string_init(&gu->email);
    string_init(&gu->signing_key);
}

void git_user_safe_init(git_user* gu, const char* n, const char* e) {
    //Throw in the event either param is null
    if(!n || !e) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }

    string_init_cstr(&gu->name, n);
    string_init_cstr(&gu->email, e);
    string_init(&gu->signing_key);
}

void git_user_set(git_user* dest, const git_user* src) {
    string_asn(&dest->name, &src->name);
    string_asn(&dest->email, &src->email);
    string_asn(&dest->signing_key, &src->signing_key);
}

void git_user_write(const git_user* gu, FILE* stream) {
    fprintf(stream, "Name: %s\nEmail: %s\n", string_cstr(&gu->name), string_cstr(&gu->email));
    if(string_size(&gu->signing_key)) {
        fprintf(stream, "Signing Key: %s\n", string_cstr(&gu->signing_key));
    }
}

void git_user_clear(git_user* gu) {
    //Clear members
    string_clear(&gu->name);
    string_clear(&gu->email);
    string_clear(&gu->signing_key);
}

void git_user_deinit(git_user* gu) {
    //Free members
    string_deinit(&gu->name);
    string_deinit(&gu->email);
    string_deinit(&gu->signing_key);
}
