#include "../include/gitid.h"
#include "../include/gitid-id.h"
#include "../include/vector-gitid-id.h"

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

void gitid_set_system_gitid_ids_file(vector_gitid_id* v, const char* fn) {
    //Open file stream to system file in write mode
    FILE* sys_gitids = fopen(fn, "w");

    //Iterate through vector and write each one
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        gitid_id_min_write(*it, sys_gitids);
    }

    //Close stream
    fclose(sys_gitids);
}

void gitid_new_system_gitid_id(gitid_id* id) {
    
    //Initialize new vector and attempt a load
    vector_gitid_id* v = vector_init_gitid_id();
    gitid_get_system_gitid_ids(v);

    //Add the new identity to be added
    vector_push_back_gitid_id(v, id);

    //Set
    gitid_set_system_gitid_ids(v);

    //Finally, remove the last element (so we don't kill the pointer
    //when we free) and free
    vector_erase_gitid_id(v, v->head + vector_size_gitid_id(v) - 1);
    vector_free_gitid_id(v);
}

void gitid_update_system_gitid_id(gitid_id* id, char* id_name) {

}

void gitid_delete_system_gitid_id(char* id_name) {

}

