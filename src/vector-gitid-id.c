#include "../include/vector-gitid-id.h"
#include "../include/gitid-id.h"

vector_gitid_id* vector_init_gitid_id() {
    vector_gitid_id* v = (vector_gitid_id*) malloc(sizeof(vector_gitid_id));
    v->head = v->avail = v->tail = ((void*) 0);
    return v;
}

vector_gitid_id* vector_init_size_gitid_id(size_t s) {
    vector_gitid_id* v = (vector_gitid_id*) malloc(sizeof(vector_gitid_id));
    v->head = (gitid_id*) malloc(sizeof(gitid_id) * s);
    v->tail = v->avail = v->head + s;
    return v;
}

vector_gitid_id* vector_init_capacity_gitid_id(size_t s) {
    vector_gitid_id* v = (vector_gitid_id*) malloc(sizeof(vector_gitid_id));
    v->head = v->avail = (gitid_id*) malloc(sizeof(gitid_id) * s);
    v->tail = v->head + s;
    return v;
}

vector_gitid_id* vector_copy_gitid_id(vector_gitid_id* src) {
    if(src->head == ((void*) 0)) {
        return vector_init_gitid_id();
    }
    vector_gitid_id* copy = vector_init_size_gitid_id(vector_size_gitid_id(src));
    {
        const gitid_id* _alg_copy_it = src->head;
        for(gitid_id* _alg_copy_dest = copy->head; _alg_copy_it != src->avail; *_alg_copy_dest++ = *_alg_copy_it++)
            ;
    };
    return copy;
}

void vector_set_gitid_id(vector_gitid_id* v, size_t pos, gitid_id val) {
    v->head[pos] = val;
}

void vector_push_back_gitid_id(vector_gitid_id* v, gitid_id e) {
    if(v->avail == v->tail) {
        vector_grow_gitid_id(v);
    }
    *(v->avail++) = e;
}

gitid_id* vector_erase_gitid_id(vector_gitid_id* v, gitid_id* pos) {
    for(; pos + 1 != v->avail; ++pos) {
        *pos = *(pos + 1);
    }
    return --v->avail;
}

gitid_id* vector_erase_range_gitid_id(vector_gitid_id* v, gitid_id* begin, gitid_id* end) {
    size_t diff = end - begin;
    for(; begin + diff != v->avail; ++begin) {
        *begin = *(begin + diff);
    }
    return v->avail -= diff;
}

gitid_id* vector_begin_gitid_id(vector_gitid_id* v) {
    return v->head;
}

gitid_id* vector_end_gitid_id(vector_gitid_id* v) {
    return v->avail;
}

void vector_grow_gitid_id(vector_gitid_id* v) {
    size_t old_size = vector_size_gitid_id(v);
    size_t n_size = v->head ? old_size * 2 : 1;
    v->head = (gitid_id*) realloc(v->head, sizeof(gitid_id) * n_size);
    v->avail = v->head + old_size;
    v->tail = v->head + n_size;
}

size_t vector_size_gitid_id(vector_gitid_id* v) {
    return v->avail - v->head;
}

size_t vector_capacity_gitid_id(vector_gitid_id* v) {
    return v->tail - v->head;
}

gitid_id vector_at_gitid_id(vector_gitid_id* v, size_t n) {
    return *(v->head + n);
}

void vector_clear_gitid_id(vector_gitid_id* v) {
    free(v->head);
    v->head = v->avail = v->tail = ((void*) 0);
}

void vector_free_gitid_id(vector_gitid_id* v) {
    free(v->head);
    free(v);
}

