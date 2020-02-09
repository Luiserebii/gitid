#include "../include/gitid.h"
#include "../include/gitid-id.h"
#include "../include/limits.h"
#include "../include/vector-gitid-id.h"

#include <stdlib.h>
#include <string.h>

char GITID_SYSTEM_DATA_FILE[FILEPATH_MAX];
char GITID_SYSTEM_FOLDER[FILEPATH_MAX];

void gitid_get_system_gitid_ids_file(vector_gitid_id* v, const char* fn) {
    //Declare gitid_id for use
    gitid_id* id;

    //Open file stream to system file
    FILE* sys_gitids = fopen(fn, "r");

    int c;
    while((c = fgetc(sys_gitids)) != EOF) {
        //Attempt ungetc, now that we know we haven't
        //hit the end
        ungetc(c, sys_gitids);

        //Intialize and attempt a read into an id
        id = gitid_id_init();
        gitid_id_min_read(id, sys_gitids);

        //Finally, push onto vector
        vector_push_back_gitid_id(v, id);
    }

    //Close stream
    fclose(sys_gitids);
}

void gitid_set_system_gitid_ids_file(const vector_gitid_id* v, const char* fn) {
    //Open file stream to system file in write mode
    FILE* sys_gitids = fopen(fn, "w");

    //Iterate through vector and write each one
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        gitid_id_min_write(*it, sys_gitids);
    }

    //Close stream
    fclose(sys_gitids);
}

void gitid_get_system_gitid_id(const char* id_name, gitid_id* id) {
    //Initialize new vector an attempt a load
    vector_gitid_id* v = vector_init_gitid_id();
    gitid_get_system_gitid_ids(v);

    //Look for matching
    gitid_id* match;
    match = vector_get_id_gitid_id(v, id_name);

    //If nothing found, print error and break
    if(match == NULL) {
        fprintf(stderr, "Error: No git id found under the name \"%s\"\n", id_name);
        exit(1);
    }

    //Set ID to found one
    gitid_id_set(id, match);

    //Finally, free vector
    vector_free_gitid_id(v);
}

void gitid_new_system_gitid_id(const gitid_id* id) {
    //Initialize new vector and attempt a load
    vector_gitid_id* v = vector_init_gitid_id();
    gitid_get_system_gitid_ids(v);

    //Look for the id_name to determine uniqueness
    int unique = 1;
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        if(strcmp((*it)->id_name, id->id_name) == 0) {
            unique = 0;
            break;
        }
    }

    //Throw error and break if not unique
    if(!unique) {
        fprintf(stderr, "Error: git id already exists under the name \"%s\"\n", id->id_name);
        exit(1);
    }

    //Add the new identity to be added
    vector_push_back_gitid_id(v, id);

    //Set
    gitid_set_system_gitid_ids(v);

    //Finally, remove the last element (so we don't kill the pointer
    //when we free) and free
    vector_erase_gitid_id(v, v->head + vector_size_gitid_id(v) - 1);
    vector_free_gitid_id(v);
}

void gitid_update_system_gitid_id(const gitid_id* id, const char* id_name) {
    //Initialize new vector and attempt a load
    vector_gitid_id* v = vector_init_gitid_id();
    gitid_get_system_gitid_ids(v);

    //Look for the id_name, and set
    gitid_id* upd_id = NULL;
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        if(strcmp((*it)->id_name, id_name) == 0) {
            upd_id = *it;
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
    gitid_set_system_gitid_ids(v);
    vector_free_gitid_id(v);
}

void gitid_delete_system_gitid_id(const char* id_name) {
    //Initialize new vector and attempt a load
    vector_gitid_id* v = vector_init_gitid_id();
    gitid_get_system_gitid_ids(v);

    //Look for the id to delete
    gitid_id** upd_id = NULL;
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        if(strcmp((*it)->id_name, id_name) == 0) {
            upd_id = it;
            break;
        }
    }

    //If nothing found, print error and break
    if(upd_id == NULL) {
        fprintf(stderr, "Error: No git id found under the name \"%s\"\n", id_name);
        exit(1);
    }

    //Erase and free element, write, and free vector
    vector_erase_free_gitid_id(v, upd_id);
    gitid_set_system_gitid_ids(v);
    vector_free_gitid_id(v);
}
