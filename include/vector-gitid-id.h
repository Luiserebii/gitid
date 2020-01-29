#ifndef VECTOR_GITID_ID_H
#define VECTOR_GITID_ID_H

#include "gitid-id.h"
#include <stdlib.h>

typedef struct {
    gitid_id** head;
    gitid_id** avail;
    gitid_id** tail;
} vector_gitid_id;

vector_gitid_id* vector_init_gitid_id();
vector_gitid_id* vector_init_size_gitid_id(size_t s);
vector_gitid_id* vector_init_capacity_gitid_id(size_t s);
vector_gitid_id* vector_copy_gitid_id(vector_gitid_id* src);

void vector_set_gitid_id(vector_gitid_id* v, size_t pos, gitid_id* ptr);
//Frees the gitid_id at the position, if any, before setting
void vector_set_free_gitid_id(vector_gitid_id* v, size_t pos, gitid_id* ptr);
void vector_push_back_gitid_id(vector_gitid_id* v, gitid_id* e);

gitid_id** vector_erase_gitid_id(vector_gitid_id* v, gitid_id** pos);
gitid_id** vector_erase_range_gitid_id(vector_gitid_id* v, gitid_id** begin, gitid_id** end);
gitid_id** vector_erase_free_gitid_id(vector_gitid_id* v, gitid_id** pos);
gitid_id** vector_begin_gitid_id(vector_gitid_id* v);
gitid_id** vector_end_gitid_id(vector_gitid_id* v);
size_t vector_size_gitid_id(vector_gitid_id* v);
size_t vector_capacity_gitid_id(vector_gitid_id* v);
gitid_id* vector_at_gitid_id(vector_gitid_id* v, size_t n);

/**
 * Clear will free the vector of the elements, but not the elements themselves.
 *
 * Dangerous function to call, as you can lose references to elements which
 * cannot be deallocated afterwards.
 */
void vector_clear_gitid_id(vector_gitid_id* v);
/**
 * Free frees the vector of all resources, including the elements.
 */
void vector_free_gitid_id(vector_gitid_id* v);
static void vector_grow_gitid_id(vector_gitid_id* v);

#endif
