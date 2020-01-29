/**
 * vector.h of the C STL.
 *
 * Copyright (C) 2020 Luiserebii
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include "algorithm.h"

/**
 * MACRO: declare_vector(vector_type)
 *
 * Declares an entire set of vector declarations for a specific type.
 *
 * Ex: declare_vector(int)
 *
 * Whenever a vector is needed to be declared, this is probably what you want!
 **/
#define declare_vector(vector_type)                                                                               \
    typedef struct {                                                                                              \
        vector_type* head;                                                                                        \
        vector_type* avail;                                                                                       \
        vector_type* tail;                                                                                        \
    } vector_##vector_type;                                                                                       \
                                                                                                                  \
    /*                                                                                                            \
     * Initializes an empty vector within the vector* passed.                                                     \
     *                                                                                                            \
     * Note that although this data structure is completely empty, and has                                        \
     * no elements allocated, the struct itself is, so vector_free is necessary                                   \
     * for cleanup afterwards.                                                                                    \
     */                                                                                                           \
    vector_##vector_type* vector_init_##vector_type();                                                            \
                                                                                                                  \
    /*                                                                                                            \
     * Initializes an empty vector with the size passed.                                                          \
     * Memory will be allocated under the size given, so vector_free                                              \
     * is required.                                                                                               \
     */                                                                                                           \
    vector_##vector_type* vector_init_size_##vector_type(size_t s);                                               \
                                                                                                                  \
    /*                                                                                                            \
     * Intiailizes an empty vector with the size passed.                                                          \
     * Unlike vector_init_size, this function will fill the capacity.                                             \
     */                                                                                                           \
    vector_##vector_type* vector_init_capacity_##vector_type(size_t s);                                           \
                                                                                                                  \
    /*                                                                                                            \
     * Creates a fresh copy of a vector. If the dest contains a pre-existing vector,                              \
     * it will not be freed, so please release if not empty.                                                      \
     */                                                                                                           \
    vector_##vector_type* vector_copy_##vector_type(vector_##vector_type* src);                                   \
                                                                                                                  \
    /*                                                                                                            \
     * Sets an element of the vector to the value passed.                                                         \
     */                                                                                                           \
    void vector_set_##vector_type(vector_##vector_type* v, size_t pos, vector_type val);                          \
                                                                                                                  \
    /*                                                                                                            \
     * Pushes a new element onto the vector.                                                                      \
     */                                                                                                           \
    void vector_push_back_##vector_type(vector_##vector_type* v, vector_type e);                                  \
                                                                                                                  \
    /*                                                                                                            \
     * Erases an element at the pointer passed from the vector. Returns a pointer to the                          \
     * new end of the vector.                                                                                     \
     */                                                                                                           \
    vector_type* vector_erase_##vector_type(vector_##vector_type* v, vector_type* pos);                           \
                                                                                                                  \
    /*                                                                                                            \
     * Erases a range of elements [begin, end) from the vector. Returns a pointer to the                          \
     * new end of the vector.                                                                                     \
     */                                                                                                           \
    vector_type* vector_erase_range_##vector_type(vector_##vector_type* v, vector_type* begin, vector_type* end); \
                                                                                                                  \
    /*                                                                                                            \
     * Returns the first pointer in the vector's sequence.                                                        \
     */                                                                                                           \
    vector_type* vector_begin_##vector_type(vector_##vector_type* v);                                             \
                                                                                                                  \
    /*                                                                                                            \
     * Returns the last pointer in the vector's sequence.                                                         \
     */                                                                                                           \
    vector_type* vector_end_##vector_type(vector_##vector_type* v);                                               \
                                                                                                                  \
    /*                                                                                                            \
     * Returns the current size of the vector.                                                                    \
     */                                                                                                           \
    size_t vector_size_##vector_type(vector_##vector_type* v);                                                    \
                                                                                                                  \
    /*                                                                                                            \
     * Returns the current total capacity of the vector,                                                          \
     * which encompasses the total amount allocated.                                                              \
     */                                                                                                           \
    size_t vector_capacity_##vector_type(vector_##vector_type* v);                                                \
                                                                                                                  \
    /*                                                                                                            \
     * Returns the element found at the specified location passed.                                                \
     */                                                                                                           \
    vector_type vector_at_##vector_type(vector_##vector_type* v, size_t n);                                       \
                                                                                                                  \
    /*                                                                                                            \
     * Clears all elements allocated to the vector, but does not deallocate                                       \
     * the vector itself.                                                                                         \
     */                                                                                                           \
    void vector_clear_##vector_type(vector_##vector_type* v);                                                     \
                                                                                                                  \
    /*                                                                                                            \
     * Frees the resources allocated to the vector, including the vector itself.                                  \
     */                                                                                                           \
    void vector_free_##vector_type(vector_##vector_type* v);

/**
 * MACRO: define_vector(vector_type)
 *
 * Generates an entire set of definitions for a specific vector type.
 *
 * Ex: define_vector(int)
 */
#define define_vector(vector_type)                                                                                 \
    /*                                                                                                             \
     * Grows the vector by 2x, or 1 if empty.                                                                      \
     */                                                                                                            \
    static void vector_grow_##vector_type(vector_##vector_type* v);                                                \
                                                                                                                   \
    vector_##vector_type* vector_init_##vector_type() {                                                            \
        /* Allocate memory for vector struct */                                                                    \
        vector_##vector_type* v = (vector_##vector_type*) malloc(sizeof(vector_##vector_type));                    \
        v->head = v->avail = v->tail = NULL;                                                                       \
        return v;                                                                                                  \
    }                                                                                                              \
                                                                                                                   \
    vector_##vector_type* vector_init_size_##vector_type(size_t s) {                                               \
        vector_##vector_type* v = (vector_##vector_type*) malloc(sizeof(vector_##vector_type));                    \
        v->head = (vector_type*) malloc(sizeof(vector_type) * s);                                                  \
        v->tail = v->avail = v->head + s;                                                                          \
        return v;                                                                                                  \
    }                                                                                                              \
                                                                                                                   \
    vector_##vector_type* vector_init_capacity_##vector_type(size_t s) {                                           \
        vector_##vector_type* v = (vector_##vector_type*) malloc(sizeof(vector_##vector_type));                    \
        v->head = v->avail = (vector_type*) malloc(sizeof(vector_type) * s);                                       \
        v->tail = v->head + s;                                                                                     \
        return v;                                                                                                  \
    }                                                                                                              \
                                                                                                                   \
    vector_##vector_type* vector_copy_##vector_type(vector_##vector_type* src) {                                   \
        if(src->head == NULL) {                                                                                    \
            return vector_init_##vector_type();                                                                    \
        }                                                                                                          \
        /* Initialize a fresh vector using original's size */                                                      \
        vector_##vector_type* copy = vector_init_size_##vector_type(vector_size_##vector_type(src));               \
        /* Copy over values */                                                                                     \
        algorithm_min_copy(vector_type*, src->head, src->avail, copy->head);                                       \
        return copy;                                                                                               \
    }                                                                                                              \
                                                                                                                   \
    void vector_set_##vector_type(vector_##vector_type* v, size_t pos, vector_type val) { v->head[pos] = val; }    \
                                                                                                                   \
    void vector_push_back_##vector_type(vector_##vector_type* v, vector_type e) {                                  \
        if(v->avail == v->tail) {                                                                                  \
            vector_grow_##vector_type(v);                                                                          \
        }                                                                                                          \
        *(v->avail++) = e;                                                                                         \
    }                                                                                                              \
                                                                                                                   \
    vector_type* vector_erase_##vector_type(vector_##vector_type* v, vector_type* pos) {                           \
        for(; pos + 1 != v->avail; ++pos) {                                                                        \
            *pos = *(pos + 1);                                                                                     \
        }                                                                                                          \
        return --v->avail;                                                                                         \
    }                                                                                                              \
                                                                                                                   \
    vector_type* vector_erase_range_##vector_type(vector_##vector_type* v, vector_type* begin, vector_type* end) { \
        size_t diff = end - begin;                                                                                 \
        for(; begin + diff != v->avail; ++begin) {                                                                 \
            *begin = *(begin + diff);                                                                              \
        }                                                                                                          \
        return v->avail -= diff;                                                                                   \
    }                                                                                                              \
                                                                                                                   \
    vector_type* vector_begin_##vector_type(vector_##vector_type* v) { return v->head; }                           \
                                                                                                                   \
    vector_type* vector_end_##vector_type(vector_##vector_type* v) { return v->avail; }                            \
                                                                                                                   \
    void vector_grow_##vector_type(vector_##vector_type* v) {                                                      \
        size_t old_size = vector_size_##vector_type(v);                                                            \
        size_t n_size = v->head ? old_size * 2 : 1;                                                                \
                                                                                                                   \
        /* Realloc and set pointers as appropriate*/                                                               \
        v->head = (vector_type*) realloc(v->head, sizeof(vector_type) * n_size);                                   \
        v->avail = v->head + old_size;                                                                             \
        v->tail = v->head + n_size;                                                                                \
    }                                                                                                              \
                                                                                                                   \
    size_t vector_size_##vector_type(vector_##vector_type* v) { return v->avail - v->head; }                       \
                                                                                                                   \
    size_t vector_capacity_##vector_type(vector_##vector_type* v) { return v->tail - v->head; }                    \
                                                                                                                   \
    vector_type vector_at_##vector_type(vector_##vector_type* v, size_t n) { return *(v->head + n); }              \
                                                                                                                   \
    void vector_clear_##vector_type(vector_##vector_type* v) {                                                     \
        free(v->head);                                                                                             \
        v->head = v->avail = v->tail = NULL;                                                                       \
    }                                                                                                              \
                                                                                                                   \
    void vector_free_##vector_type(vector_##vector_type* v) {                                                      \
        free(v->head);                                                                                             \
        free(v);                                                                                                   \
    }

#endif
