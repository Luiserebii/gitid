/**
 * string.h of the C STL.
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

#ifndef STRING_H
#define STRING_H

#include "vector.h"

/**
 * Generate a set of vector functions for our string
 */
// clang-format off
declare_vector_class(string, char);
// clang-format on

/**
 * Intiailizes an empty string with the contents of the char* passed. 
 * It is assumed that that char* is valid.
 */
string* string_init_cstr(const char* s);

/**
 * Sets the contents of the string to the char* passed. If there is not enough space,
 * the string will expand to fit the string.
 */
void string_set_cstr(string* str, const char* s);

/**
 * Concatenates the string src to the end of the string dest.
 */
#define string_cat(dest, src) string_insert_range(dest, dest->avail, src->head, src->avail)

/**
 * Concatenates the char* string s to the end of the string str.
 */
void string_cat_cstr(string* str, const char* s);

/**
 * Returns a pointer to the contents of the string as a null-terminated char.
 * 
 * Note that if any of the elements of the string is a null-terminator, this will
 * result in a "chopped" c-string.
 *
 * Note that this function may increase the capacity of the string if needed.
 * 
 * The pointer returned by this function may also become invalidated if any mutations
 * to the string occur - best to call once and use quickly before performing
 * any modifications.
 */
const char* string_cstr(string* str);

#endif
