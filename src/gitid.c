#include "../include/gitid.h"
#include "../include/gitid-id.h"
#include "../include/vector-gitid-id.h"

void gitid_get_system_gitid_ids(vector_gitid_id* v) {
    //Declare gitid_id for use
    gitid_id* id;

    //Open file stream to system file
    FILE* sys_gitids = fopen(GITID_SYSTEM_DATA_FILE, "r");

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

void gitid_set_system_gitid_ids(vector_gitid_id* v) {
    //Open file stream to system file in write mode
    FILE* sys_gitids = fopen(GITID_SYSTEM_DATA_FILE, "w");

    //Iterate through vector and write each one
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        gitid_id_min_write(*it, sys_gitids);
    }

    //Close stream
    fclose(sys_gitids);
}
