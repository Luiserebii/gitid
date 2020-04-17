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

#include "../include/cstl/string.h"
#include "../include/cstl/vector.h"
#include "../include/cstl/algorithm.h"

#include <string.h>

/**
 * Generate a set of vector functions for our string
 */
// clang-format off
define_vector_class(string, char)
// clang-format on

string* string_init_cstr(const char* s) {
    size_t len = strlen(s);
    string* str = string_init_size(len);
    algorithm_min_copy(char*, s, s + len, str->head);
    return str;
}

void string_set_cstr(string* str, const char* s) {
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
    for(; *it1 == *s2; ++it1, ++s2) {
        //It's possible for 0s the follow the end of a string;
        //as in, *it1 == *s2 && *it1 == '\0' is more than possible;
        //so we need to perform this check here...
        if(*s2 == '\0') {
            return 0;
        }
    }
    if(*s2 == '\0') {
        return 0;
    }
    return *it1 - *s2;
}

int string_cmp(const string* s1, const string* s2) {
    const char* it1 = string_begin(s1);
    const char* it2 = string_begin(s2);
    for(; *it1 == *it2; ++it1, ++it2) {
        if(*it1 == '\0') {
            return 0;
        }
    }
    return *it1 - *it2;
}

const char* string_cstr(string* str) {
    //Grow capacity if necessary
    if(str->avail == str->tail) {
        string_grow(str, string_capacity(str) + 1);
    }
    //Set a null-terminator at avail
    *(str->avail) = '\0';
    return str->head;
}
