#include "../include/gitid.h"
#include "../include/vector-gitid-id.h"
#include "../include/gitid-id.h"

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
}
/*
void gitid_set_system_gitid_ids(vector_gitid_id* v) {

}*/

