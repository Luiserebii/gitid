#include "../include/gitid.h"
#include "../include/gitid-id.h"
#include "../include/limits.h"
#include "../include/vector-gitid-id.h"

#include <cstl/string.h>

#include <stdlib.h>
#include <string.h>

char GITID_SYSTEM_DATA_FILE[FILEPATH_MAX];
char GITID_SYSTEM_FOLDER[FILEPATH_MAX];

void gitid_get_system_gitid_ids_file(vector_gitid_id* v, const char* fn) {
    //Declare gitid_id for use
    gitid_id id;

    //Open file stream to system file
    FILE* sys_gitids = fopen(fn, "r");

    int c;
    while((c = fgetc(sys_gitids)) != EOF) {
        //Attempt ungetc, now that we know we haven't
        //hit the end
        ungetc(c, sys_gitids);

        //Initialize and attempt a read into an id
        gitid_id_init(&id);
        gitid_id_min_read(&id, sys_gitids);

        //Finally, push onto vector
        vector_gitid_id_push_back_r(v, &id);
    }

    //Close stream
    fclose(sys_gitids);
}

void gitid_set_system_gitid_ids_file(const vector_gitid_id* v, const char* fn) {
    //Open file stream to system file in write mode
    FILE* sys_gitids = fopen(fn, "w");

    //Iterate through vector and write each one
    for(gitid_id* it = v->head; it != v->avail; ++it) {
        gitid_id_min_write(it, sys_gitids);
    }

    //Close stream
    fclose(sys_gitids);
}

void gitid_get_system_gitid_id(const char* id_name, gitid_id* id) {
    //Initialize new vector and attempt a load
    vector_gitid_id v;
    vector_gitid_id_init(&v);
    gitid_get_system_gitid_ids(&v);

    //Look for matching
    gitid_id* match = vector_gitid_id_get_id(&v, id_name);

    //If nothing found, print error and break
    if(match == NULL) {
        fprintf(stderr, "Error: No git id found under the name \"%s\"\n", id_name);
        exit(1);
    }

    //Set ID to found one
    gitid_id_set(id, match);

    //Finally, deinit vector elements, and vector itself
    vector_gitid_id_deinit_r(&v);
    vector_gitid_id_deinit(&v);
}

void gitid_new_system_gitid_id(const gitid_id* id) {
    //Initialize new vector and attempt a load
    vector_gitid_id v;
    vector_gitid_id_init(&v);
    gitid_get_system_gitid_ids(&v);

    //Look for the id_name to determine uniqueness
    int unique = 1;
    for(gitid_id* it = v->head; it != v->avail; ++it) {
        if(string_cmp(&it->id_name, &id->id_name) == 0) {
            unique = 0;
            break;
        }
    }

    //Throw error and break if not unique
    if(!unique) {
        fprintf(stderr, "Error: git id already exists under the name \"%s\"\n", string_cstr(&id->id_name));
        exit(1);
    }

    //Add the new identity to be added
    //(for const-correctness, we create a kind of copy here to push)
    gitid_id copy_id;
    gitid_id_init(&copy_id);
    gitid_id_set(&copy_id, id);
    vector_gitid_id_push_back_r(&v, &copy_id);

    //Set
    gitid_set_system_gitid_ids(&v);

    //Finally, free all elements and vector
    vector_gitid_id_deinit_r(&v);
    vector_gitid_id_deinit(&v);
}

void gitid_update_system_gitid_id(const gitid_id* id, const char* id_name) {
    //Initialize new vector and attempt a load
    vector_gitid_id v;
    vector_gitid_id_init(&v);
    gitid_get_system_gitid_ids(&v);

    //Look for the id_name, and set
    gitid_id* upd_id = NULL;
    for(gitid_id* it = v->head; it != v->avail; ++it) {
        if(string_cmp(&it->id_name, &id->id_name) == 0) {
            upd_id = it;
            break;
        }
    }

    //If nothing found, print error and break
    if(upd_id == NULL) {
        fprintf(stderr, "Error: No git id found under the name \"%s\"\n", id_name);
        exit(1);
    }

    //Update, write, and free vector
    gitid_id_set(upd_id, id);
    gitid_set_system_gitid_ids(&v);

    vector_gitid_id_deinit_r(&v);
    vector_gitid_id_deinit(&v);
}

void gitid_delete_system_gitid_id(const char* id_name) {
    //Initialize new vector and attempt a load
    vector_gitid_id v;
    vector_gitid_id_init(&v);
    gitid_get_system_gitid_ids(&v);

    //Look for the id to delete
    gitid_id* del_id = NULL;
    for(gitid_id* it = v->head; it != v->avail; ++it) {
        if(string_cmp_cstr(&it->id_name, id_name) == 0) {
            del_id = it;
            break;
        }
    }

    //If nothing found, print error and break
    if(del_id == NULL) {
        fprintf(stderr, "Error: No git id found under the name \"%s\"\n", id_name);
        exit(1);
    }

    //Erase and free element, write, and free vector
    vector_gitid_id_erase_deinit(&v, del_id);
    gitid_set_system_gitid_ids(&v);

    vector_gitid_id_deinit_r(&v);
    vector_gitid_id_deinit(&v);
}
