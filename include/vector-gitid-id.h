#ifndef VECTOR_GITID_ID_H
#define VECTOR_GITID_ID_H

#include "gitid-id.h"
#include <cstl/vector.h>

declare_vector_type(gitid_id);

/**
 * Returns a pointer to a gitid_id by searching for the first with the name passed.
 * If nothing was found, NULL is returned.
 */
gitid_id* vector_gitid_id_get_id(vector_gitid_id* v, const char* id_name);

/**
 * Frees the resources allocated to all vector elements through a kind of recursive
 * deinit.
 *
 * deinit_r frees the vector's elements of all resources, but not the vector itself.
 */
void vector_gitid_id_deinit_r(vector_gitid_id* v);

#endif
