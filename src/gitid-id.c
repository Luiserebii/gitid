#include "../include/struct.h"
#include "../include/util.h"
#include "../include/gitid-id.h"

#include <string.h>

gitid_id* gitid_id_init() {
    //Allocate gitid_id
    gitid_id* id = safemalloc(sizeof(gitid_id));

    //Initialize fields
    id->name = id->username = id->email = id->signing_key = NULL;

    return id;
}

/**
 * MACRO use: Define struct functions for each char* member
 */
define_struct_set_string(gitid_id, name, opts, n)
define_struct_set_string(gitid_id, username, opts, usrn)
define_struct_set_string(gitid_id, email, opts, e)
define_struct_set_string(gitid_id, signing_key, opts, sk)

void gitid_id_free(gitid_id* id) {
    //Free members
    free(id->name);
    free(id->username);
    free(id->email);
    free(id->signing_key);

    //Free struct
    free(id);
}

