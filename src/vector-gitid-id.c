#include "../include/vector-gitid-id.h"
#include "../include/gitid-id.h"
#include "../include/util.h"

#include <stdlib.h>
#include <string.h>

static void vector_grow_gitid_id(vector_gitid_id* v);

vector_gitid_id* vector_init_gitid_id(void) {
    vector_gitid_id* v = (vector_gitid_id*) safemalloc(sizeof(vector_gitid_id));
    v->head = v->avail = v->tail = NULL;
    return v;
}

vector_gitid_id* vector_init_size_gitid_id(size_t s) {
    vector_gitid_id* v = (vector_gitid_id*) safemalloc(sizeof(vector_gitid_id));
    v->head = (gitid_id**) safemalloc(sizeof(gitid_id*) * s);
    v->tail = v->avail = v->head + s;
    return v;
}

vector_gitid_id* vector_init_capacity_gitid_id(size_t s) {
    vector_gitid_id* v = (vector_gitid_id*) safemalloc(sizeof(vector_gitid_id));
    v->head = v->avail = (gitid_id**) safemalloc(sizeof(gitid_id*) * s);
    v->tail = v->head + s;
    return v;
}
/*
vector_gitid_id* vector_copy_gitid_id(vector_gitid_id* src) {
    if(src->head == NULL) {
        return vector_init_gitid_id();
    }
    vector_gitid_id* copy = vector_init_size_gitid_id(vector_size_gitid_id(src));
    //algorithm_min_copy(vector_type*, src->head, src->avail, copy->head);
    {
        const gitid_id* _alg_copy_it = src->head;
        for(gitid_id* _alg_copy_dest = copy->head; _alg_copy_it != src->avail; *_alg_copy_dest++ = *_alg_copy_it++)
            ;
    };
    return copy;
}
*/
void vector_set_gitid_id(vector_gitid_id* v, size_t pos, gitid_id* ptr) {
    v->head[pos] = ptr;
}

void vector_set_free_gitid_id(vector_gitid_id* v, size_t pos, gitid_id* ptr) {
    gitid_id_free(v->head[pos]);
    v->head[pos] = ptr;
}

void vector_push_back_gitid_id(vector_gitid_id* v, gitid_id* e) {
    if(v->avail == v->tail) {
        vector_grow_gitid_id(v);
    }
    *(v->avail++) = e;
}

gitid_id** vector_erase_gitid_id(vector_gitid_id* v, gitid_id** pos) {
    for(; pos + 1 != v->avail; ++pos) {
        *pos = *(pos + 1);
    }
    return --v->avail;
}

gitid_id** vector_erase_range_gitid_id(vector_gitid_id* v, gitid_id** begin, gitid_id** end) {
    size_t diff = end - begin;
    for(; begin + diff != v->avail; ++begin) {
        *begin = *(begin + diff);
    }
    return v->avail -= diff;
}

gitid_id** vector_erase_free_gitid_id(vector_gitid_id* v, gitid_id** pos) {
    gitid_id_free(*pos);
    for(; pos + 1 != v->avail; ++pos) {
        *pos = *(pos + 1);
    }
    return --v->avail;
}

gitid_id** vector_begin_gitid_id(vector_gitid_id* v) {
    return v->head;
}

gitid_id** vector_end_gitid_id(vector_gitid_id* v) {
    return v->avail;
}

void vector_grow_gitid_id(vector_gitid_id* v) {
    size_t old_size = vector_size_gitid_id(v);
    size_t n_size = v->head ? old_size * 2 : 1;
    v->head = (gitid_id**) realloc(v->head, sizeof(gitid_id*) * n_size);
    v->avail = v->head + old_size;
    v->tail = v->head + n_size;
}

size_t vector_size_gitid_id(vector_gitid_id* v) {
    return v->avail - v->head;
}

size_t vector_capacity_gitid_id(vector_gitid_id* v) {
    return v->tail - v->head;
}

gitid_id* vector_at_gitid_id(vector_gitid_id* v, size_t n) {
    return *(v->head + n);
}

gitid_id* vector_get_id_gitid_id(vector_gitid_id* v, const char* id_name) {
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        if(strcmp(id_name, (*it)->id_name) == 0) {
            return *it;
        }
    }
    //If we hit here, nothing was found
    return NULL;
}

void vector_clear_gitid_id(vector_gitid_id* v) {
    free(v->head);
    v->head = v->avail = v->tail = NULL;
}

void vector_free_gitid_id(vector_gitid_id* v) {
    //Free all gitid_ids
    for(gitid_id** it = v->head; it != v->avail; ++it) {
        gitid_id_free(*it);
    }
    free(v->head);
    free(v);
}
