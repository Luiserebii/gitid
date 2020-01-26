#include "../include/gitid-id.h"
#include "../include/struct.h"
#include "../include/util.h"

#include <stdio.h>
#include <string.h>

gitid_id* gitid_id_init() {
    //Allocate gitid_id
    gitid_id* id = safemalloc(sizeof(gitid_id));

    //Initialize fields
    id->id_name = id->name = id->email = id->signing_key = NULL;

    return id;
}

gitid_id* gitid_id_safe_init(const char* id_n, const char* n, const char* e) {
    if(!id_n || !n || !e) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }
    //Allocate gitid_id
    gitid_id* id = safemalloc(sizeof(gitid_id));

    gitid_id_set_id_name(id, id_n);
    gitid_id_set_name(id, n);
    gitid_id_set_email(id, e);

    //Initialize fields
    id->signing_key = NULL;

    return id;
}

/**
 * MACRO use: Define struct functions for each char* member
 */
define_struct_set_string(gitid_id, id_name, opts, id_n);
define_struct_set_string(gitid_id, name, opts, n);
define_struct_set_string(gitid_id, email, opts, e);
define_struct_set_string(gitid_id, signing_key, opts, sk);

void gitid_id_write(gitid_id* id, FILE* stream) {
    fprintf(stream, "ID: %s\nName: %s\nEmail: %s\n", id->id_name, id->name, id->email);
    if(id->signing_key) {
        fprintf(stream, "Signing Key: %s\n", id->signing_key);
    }
}

void gitid_id_min_write(gitid_id* id, FILE* stream) {
    fprintf(stream, "| %s\n| %s\n| %s\n", id->id_name, id->name, id->email);
    if(id->signing_key) {
        fprintf(stream, "| %s\n", id->signing_key);
    }
    //Close with ending ___
    fprintf(stream, "____________\n");
}

void gitid_id_min_read(gitid_id* id, FILE* stream) {
    char buffer1[GITID_ID_BUFFER_MAX];
    char buffer2[GITID_ID_BUFFER_MAX];
    char buffer3[GITID_ID_BUFFER_MAX];
    
    //Load into buffers
    fscanf(stream, "| %s\n| %s\n| %s\n", buffer1, buffer2, buffer3);

    //Set into struct
    gitid_id_set_id_name(id, buffer1);
    gitid_id_set_name(id, buffer1);
    gitid_id_set_email(id, buffer1);
}

void gitid_id_free(gitid_id* id) {
    //Free members
    free(id->id_name);
    free(id->name);
    free(id->email);
    free(id->signing_key);

    //Free struct
    free(id);
}
