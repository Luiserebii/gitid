/**
 * string.c of the C STL.
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

#define CSTL_VECTOR_ALLOC_SZ(sz) ((sz) + STRING_CAPACITY_EXTRA)
#define CSTL_VECTOR_INIT(v) string_init_capacity(v, 4)
#include "../include/cstl/string.h"
#include "../include/cstl/algorithm.h"
#include "../include/cstl/vector.h"

#include <string.h>

/**
 * Generate a set of vector functions for our string
 */
// clang-format off
define_vector_class(string, char);
// clang-format on

void string_init_cstr(string* str, const char* s) {
    size_t len = strlen(s);
    string_init_size(str, len);
    algorithm_min_copy(char*, s, s + len, str->head);
}

string* string_create_cstr(const char* s) {
    size_t len = strlen(s);
    string* str = string_create_size(len);
    algorithm_min_copy(char*, s, s + len, str->head);
    return str;
}

void string_cat(string* dest, const string* src) {
    string_insert_range(dest, dest->avail, src->head, src->avail);
}

void string_asn_cstr(string* str, const char* s) {
    const char* end = s;
    for(; *end != '\0'; ++end)
        ;
    string_assign(str, s, end);
}

void string_cat_cstr(string* str, const char* s) {
    const char* end = s;
    for(; *end != '\0'; ++end)
        ;
    string_insert_range(str, string_end(str), s, end);
}

int string_cmp_cstr(const string* s1, const char* s2) {
    const char* it1 = string_begin(s1);
    const char* end1 = string_end(s1);
    for(; it1 != end1 && *s2 != '\0'; ++it1, ++s2) {
        if(*it1 != *s2) {
            return *it1 - *s2;
        }
    }
    if(it1 == end1 && *s2 == '\0') {
        return 0;
    }
    if(it1 == end1) {
        return -1;
    }
    return 1;
}

int string_cmp(const string* s1, const string* s2) {
    const char* it1 = string_begin(s1);
    const char* it2 = string_begin(s2);
    const char* end1 = string_end(s1);
    const char* end2 = string_end(s2);
    for(; it1 != end1 && it2 != end2; ++it1, ++it2) {
        if(*it1 != *it2) {
            return *it1 - *it2;
        }
    }
    if(it1 == end1 && it2 == end2) {
        return 0;
    }
    if(it1 == end1) {
        return -1;
    }
    return 1;
}

const char* string_cstr(const string* str) {
    //Set a null-terminator at avail
    *(str->avail) = '\0';
    return str->head;
}
