#include "../include/vector-gitid-id.h"
#include "../include/gitid-id.h"
#include "../include/util.h"

#include <cstl/vector.h>
#include <stdlib.h>
#include <string.h>

define_vector_type(gitid_id);

gitid_id* vector_gitid_id_get_id(vector_gitid_id* v, const char* id_name) {
    for(gitid_id* it = v->head; it != v->avail; ++it) {
        if(string_cmp_cstr(&it->id_name, id_name) == 0) {
            return it;
        }
    }
    //If we hit here, nothing was found
    return NULL;
}

gitid_id* vector_gitid_id_erase_deinit(vector_gitid_id* v, gitid_id* pos) {
    gitid_id_deinit(pos);
    vector_gitid_id_erase(v, pos);
}

void vector_gitid_id_deinit_r(vector_gitid_id* v) {
    //Deinitializes all gitid_ids
    for(gitid_id* it = v->head; it != v->avail; ++it) {
        gitid_id_deinit(it);
    }
}
