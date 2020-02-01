#ifndef VECTOR_GITID_ID_H
#define VECTOR_GITID_ID_H

#include "gitid-id.h"

typedef struct {
    gitid_id** head;
    gitid_id** avail;
    gitid_id** tail;
} vector_gitid_id;

/*
 * Initializes an empty vector within the vector* passed.
 *
 * Note that although this data structure is completely empty, and has
 * no elements allocated, the struct itself is, so vector_free is necessary
 * for cleanup afterwards.
 */
vector_gitid_id* vector_init_gitid_id();

/*
 * Initializes an empty vector with the size passed.
 * Memory will be allocated under the size given, so vector_free
 * is required.
 */
vector_gitid_id* vector_init_size_gitid_id(size_t s);

/*
 * Intiailizes an empty vector with the size passed.
 * Unlike vector_init_size, this function will fill the capacity.
 */
vector_gitid_id* vector_init_capacity_gitid_id(size_t s);
/**
 * This function is a little complex at the moment, and probably not immediately
 * needed, so let's implement this down the line if necessary
 */
//vector_gitid_id* vector_copy_gitid_id(vector_gitid_id* src);

/*
 * Sets an element of the vector to the value passed.
 */
void vector_set_gitid_id(vector_gitid_id* v, size_t pos, gitid_id* ptr);
//Frees the gitid_id at the position, if any, before setting
void vector_set_free_gitid_id(vector_gitid_id* v, size_t pos, gitid_id* ptr);

/*
 * Pushes a new element onto the vector.
 */
void vector_push_back_gitid_id(vector_gitid_id* v, gitid_id* e);

/*
 * Erases an element at the pointer passed from the vector. Returns a pointer to the
 * new end of the vector.
 */
gitid_id** vector_erase_gitid_id(vector_gitid_id* v, gitid_id** pos);

/*
 * Erases a range of elements [begin, end) from the vector. Returns a pointer to the
 * new end of the vector.
 */
gitid_id** vector_erase_range_gitid_id(vector_gitid_id* v, gitid_id** begin, gitid_id** end);
gitid_id** vector_erase_free_gitid_id(vector_gitid_id* v, gitid_id** pos);

/*
 * Returns the first pointer in the vector's sequence.
 */
gitid_id** vector_begin_gitid_id(vector_gitid_id* v);

/*
 * Returns the last pointer in the vector's sequence.
 */
gitid_id** vector_end_gitid_id(vector_gitid_id* v);

/*
 * Returns the current size of the vector.
 */
size_t vector_size_gitid_id(vector_gitid_id* v);

/*
 * Returns the current total capacity of the vector,
 * which encompasses the total amount allocated.
 */
size_t vector_capacity_gitid_id(vector_gitid_id* v);

/*
 * Returns the element found at the specified location passed.
 */
gitid_id* vector_at_gitid_id(vector_gitid_id* v, size_t n);

/**
 * Returns a pointer to a gitid_id by searching for the first with the name passed.
 * If nothing was found, NULL is returned.
 */
gitid_id* vector_get_id_gitid_id(vector_gitid_id* v, const char* id_name);

/**
 * 
 * Clears all elements allocated to the vector, but does not deallocate
 * the vector itself.
 * Clear will free the vector of the elements, but not the elements themselves.
 *
 * Dangerous function to call, as you can lose references to elements which
 * cannot be deallocated afterwards.
 */
void vector_clear_gitid_id(vector_gitid_id* v);
/**
 * Frees the resources allocated to the vector, including the vector itself.
 * Free frees the vector of all resources, including the elements.
 */
void vector_free_gitid_id(vector_gitid_id* v);

#endif
