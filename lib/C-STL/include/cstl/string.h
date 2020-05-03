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

#ifndef CSTL_STRING_H
#define CSTL_STRING_H

#include "vector.h"

/**
 * Generate a set of vector functions for our string
 */
// clang-format off
declare_vector_class(string, char);
// clang-format on

/**
 * A value representing the amount of extra capacity to allocate.
 * In this case, it is meant to represent at least one for the
 * null terminator.
 *
 * Note that all allocation/reallocations therefore allocate
 * the capacity of the vector in terms of chars, + 1 (or,
 * STRING_CAPACITY_EXTRA).
 */
#define STRING_CAPACITY_EXTRA 1

/**
 * Initializes an empty string with the contents of the char* passed. 
 * It is assumed that that char* is valid.
 */
void string_init_cstr(string* str, const char* s);

/**
 * Creates (allocates and initializes) an empty string with the contents of the char* passed. 
 * It is assumed that that char* is valid.
 */
string* string_create_cstr(const char* s);

/**
 * Sets the contents of the string to the char* passed. If there is not enough space,
 * the string will expand to fit the string.
 */
void string_asn_cstr(string* str, const char* s);

/**
 * Concatenates the string src to the end of the string dest.
 */
void string_cat(string* dest, const string* src);

/**
 * Concatenates the char* string s to the end of the string str.
 */
void string_cat_cstr(string* str, const char* s);

/**
 * Compares string s1 to char* s2, and returns an integer representing
 * the result.
 *
 * If s1 < s2, then the result is a negative integer (i.e. n < 0).
 * If s1 > s2, then the result is a positive integer (i.e. n > 0).
 * If s1 == s2, then the result is 0.
 */
int string_cmp_cstr(const string* s1, const char* s2);

/**
 * Compares string s1 to string s2, and returns an integer representing
 * the result.
 *
 * If s1 < s2, then the result is a negative integer (i.e. n < 0).
 * If s1 > s2, then the result is a positive integer (i.e. n > 0).
 * If s1 == s2, then the result is 0.
 */
int string_cmp(const string* s1, const string* s2);

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
const char* string_cstr(const string* str);

#endif
