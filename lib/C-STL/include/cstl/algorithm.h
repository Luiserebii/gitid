/**
 * algorithm.h of the C STL.
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

#ifndef CSTL_ALGORITHM_H
#define CSTL_ALGORITHM_H

/**
 * algorithm_copy(type, begin, end, dest, res)
 *
 * Takes a pointer type as the first parameter, which is to be substituted as a generic for the values
 * of begin and dest. Essentially, the range [begin, end) is copied into dest. The new end of the range
 * beginning with dest is copied into res.
 *
 * Ex: algorithm_copy(int*, months, months + 12, words, newWordsend)
 */
#define algorithm_copy(type, begin, end, dest, res)                                         \
    {                                                                                       \
        res = dest;                                                                         \
        for(const type _alg_copy_it = begin; _alg_copy_it != end; *res++ = *_alg_copy_it++) \
            ;                                                                               \
    }

/**
 * algorithm_min_copy(type, begin, end, dest)
 *
 * Takes a pointer type as the first parameter, which is to be substituted as a generic for the values
 * of begin and dest. Essentially, the range [begin, end) is copied into dest.
 *
 * Ex: algorithm_copy(int*, months, months + 12, words)
 */
#define algorithm_min_copy(type, begin, end, dest)                                                \
    {                                                                                             \
        const type _alg_copy_it = begin;                                                          \
        for(type _alg_copy_dest = dest; _alg_copy_it != end; *_alg_copy_dest++ = *_alg_copy_it++) \
            ;                                                                                     \
    }

/**
 * algorithm_fill(type, begin, end, val)
 *
 * Takes a pointer type as the first parameter, which is to be substituted as a generic for the value
 * of begin. Essentially, the value val is copied into the range [begin, end).
 *
 * Ex: algorithm_fill(int*, months, months + 12, words)
 */
#define algorithm_fill(type, begin, end, val)                                      \
    {                                                                              \
        for(type _alg_copy_it = begin; _alg_copy_it != end; *_alg_copy_it++ = val) \
            ;                                                                      \
    }

/**
 * algorithm_find(begin, end, val, res)
 *
 * Searches through [begin, end) for val. Returns a pointer to the found value through
 * res, or end if nothing found. 
 *
 * Ex: algorithm_find(nums, nums + sz, 100, first100);
 */
#define algorithm_find(begin, end, val, res) \
    {                                        \
        res = begin;                         \
        while(res != end && *res != val) {   \
            ++res;                           \
        }                                    \
    }

/**
 * algorithm_find_last(begin, end, val, res)
 *
 * Searches through [begin, end) for val. Returns a pointer to the last found value through
 * res, or end if nothing found. 
 *
 * Ex: algorithm_find_last(nums, nums + sz, 100, last100);
 */
#define algorithm_find_last(begin, end, val, res) \
    {                                             \
        res = end - 1;                            \
        while(res != begin - 1 && *res != val) {  \
            --res;                                \
        }                                         \
    }

/**
 * algorithm_equal(type, begin, end, begin2, res)
 *
 * Searches and compares [begin, end) to [begin2, x), where x is end - begin. 
 * Returns a boolean value into res representing the equivalence of the range.
 *
 * Ex: algorithm_equal(char*, word, word + sz, word2, res);
 */
#define algorithm_equal(type, begin, end, begin2, res)                                     \
    {                                                                                      \
        res = 1;                                                                           \
        const type _alg_eq_b = begin;                                                      \
        for(const type _alg_eq_b2 = begin2; _alg_eq_b != end; ++_alg_eq_b, ++_alg_eq_b2) { \
            if(*_alg_eq_b != *_alg_eq_b2) {                                                \
                res = 0;                                                                   \
                break;                                                                     \
            }                                                                              \
        }                                                                                  \
    }

/**
 * algorithm_max(a, b)
 *
 * Returns the greater of the two values by resolving into an expression.
 */
#define algorithm_max(a, b) (a > b) ? a : b

/**
 * algorithm_min(a, b)
 *
 * Returns the lesser of the two values by resolving into an expression.
 */
#define algorithm_min(a, b) (a < b) ? a : b

/**
 * algorithm_count(type, begin, end, val, res)
 *
 * Returns the number of times val appears in [begin, end) into res.
 *
 * Ex: algorithm_count(int*, nums, nums + sz, 10, res);
 */
#define algorithm_count(type, begin, end, val, res)                                    \
    {                                                                                  \
        res = 0;                                                                       \
        for(const type _alg_count_it = begin; _alg_count_it != end; ++_alg_count_it) { \
            if(*_alg_count_it == val) {                                                \
                ++res;                                                                 \
            }                                                                          \
        }                                                                              \
    }

/**
 * algorithm_transform(type, begin, end, dest, f)
 *
 * Apply the unary function f to the range [begin, end), storing the result
 * in a range [dest, end - begin).
 *
 * Ex: algorithm_transform(int*, nums, nums + sz, doubled, doubleNum);
 * where doubleNum is a function (int doubleNum(int x) { returns x * 2; })
 */
#define algorithm_transform(type, begin, end, dest, f) \
    {                                                  \
        const type _alg_tr_it = begin;                 \
        type _alg_tr_dest = dest;                      \
        while(_alg_tr_it != end) {                     \
            *_alg_tr_dest++ = f(*_alg_tr_it++);        \
        }                                              \
    }

/**
 * algorithm_accumulate(type, begin, end, res)
 *
 * Add all values found in the range [begin, end) and return in res.
 * 
 * Aside from storing the result of the computation, the initial value of res
 * will be used within the sum. Typically, res should therefore be 0.
 *
 * Ex: algorithm_accumulate(int*, nums, nums + sz, sum);
 */
#define algorithm_accumulate(type, begin, end, res) \
    {                                               \
        const type _alg_acc_it = begin;             \
        while(_alg_acc_it != end) {                 \
            res += *_alg_acc_it++;                  \
        }                                           \
    }
/**
 * algorithm_remove_copy_if(type, begin, end, dest, f)
 *
 * Copies all values in the range [begin, end) to dest which
 * do not match the predicate f passed. 
 *
 * Alternatively, this function removes any elements which match
 * the predicate and places this new range in dest.
 *
 * Ex: algorithm_remove_copy_if(char*, a, a + sz, b, islower)
 */
#define algorithm_remove_copy_if(type, begin, end, dest, f)                         \
    {                                                                               \
        type _alg_cpif_dest = dest;                                                 \
        for(const type _alg_cpif_it = begin; _alg_cpif_it != end; ++_alg_cpif_it) { \
            if(!f(*_alg_cpif_it)) {                                                 \
                *_alg_cpif_dest++ = *_alg_cpif_it;                                  \
            }                                                                       \
        }                                                                           \
    }

/**
 * algorithm_search(type, begin, end, begin2, end2, res) 
 *
 * Searches through the range [begin, end) for [begin2, end2).
 * Returns a pointer to the first element found that matches this sequence
 * through res, or end if nothing is found.
 *
 * Ex: algorithm_search(char*, charList, charList + cLsz, word, word + wsz, res);
 */
#define algorithm_search(type, begin, end, begin2, end2, res)                               \
    {                                                                                       \
        /* Declaring local label */                                                         \
        __label__ _algorithm_search_end;                                                    \
                                                                                            \
        for(const type _alg_search_b1 = begin; _alg_search_b1 != end; ++_alg_search_b1) {   \
            /* Idea behind continue; only add names below if we snag an equal initial val*/ \
            if(*_alg_search_b1 != *begin2) {                                                \
                continue;                                                                   \
            }                                                                               \
            const type _alg_search_it1 = _alg_search_b1;                                    \
            const type _alg_search_it2 = begin2;                                            \
            for(; _alg_search_it2 != end2 && *_alg_search_it1 == *_alg_search_it2;          \
                ++_alg_search_it1, ++_alg_search_it2) {                                     \
                if(_alg_search_it1 == end) {                                                \
                    res = end;                                                              \
                    goto _algorithm_search_end;                                             \
                }                                                                           \
            }                                                                               \
            if(_alg_search_it2 == end2) {                                                   \
                res = _alg_search_b1;                                                       \
                goto _algorithm_search_end;                                                 \
            }                                                                               \
        }                                                                                   \
        res = end;                                                                          \
    _algorithm_search_end:;                                                                 \
    }

/**
 * algorithm_find_if(begin, end, f, res)
 *
 * Searches through [begin, end) for the first element in which the
 * predicate f returns true. Returns a pointer to the found value through
 * res, or end if nothing found.
 *
 * Ex: algorithm_find(nums, nums + sz, isEven, res);
 */
#define algorithm_find_if(begin, end, f, res) \
    {                                         \
        res = begin;                          \
        while(res != end && !f(*res)) {       \
            ++res;                            \
        }                                     \
    }

/**
 * algorithm_remove(type, begin, end, val, res)
 *
 * Iterates through [begin, end), removing any elements equal to val.
 * Elements are not truly removed; the function simply does not set elements
 * equal to val in the range [begin, res), where res is a pointer to the 
 * new end of the range.
 *
 * This function is convenient when paired with vector's erase, forming an idiom.
 *
 * Ex: algorithm_remove(int*, nums, nums + sz, 10, res);
 */
#define algorithm_remove(type, begin, end, val, res)                                \
    {                                                                               \
        res = begin;                                                                \
        for(type _alg_remove_it = begin; _alg_remove_it != end; ++_alg_remove_it) { \
            if(*_alg_remove_it != val) {                                            \
                *res++ = *_alg_remove_it;                                           \
            }                                                                       \
        }                                                                           \
    }

/**
 * algorithm_remove_if(type, begin, end, f, res)
 *
 * Iterates through [begin, end), removing any elements which return true when 
 * passed to the predicate f.
 *
 * Elements are not truly removed; the function simply does not set elements
 * which return true in the range [begin, res), where res is a pointer to the 
 * new end of the range.
 *
 * This function is convenient when paired with vector's erase, forming an idiom.
 *
 * Ex: algorithm_remove_if(int*, nums, nums + sz, isEven, res);
 */
#define algorithm_remove_if(type, begin, end, f, res)                               \
    {                                                                               \
        res = begin;                                                                \
        for(type _alg_remove_it = begin; _alg_remove_it != end; ++_alg_remove_it) { \
            if(!f(*_alg_remove_it)) {                                               \
                *res++ = *_alg_remove_it;                                           \
            }                                                                       \
        }                                                                           \
    }

/**
 * algorithm_remove_copy(type, begin, end, dest, val)
 *
 * Copies all values in the range [begin, end) to dest which
 * do not match the value val passed. 
 *
 * Alternatively, this function removes any elements which match
 * the value and places this new range in dest.
 *
 * Ex: algorithm_remove_copy(int*, nums, nums + sz, newNums, 100);
 */
#define algorithm_remove_copy(type, begin, end, dest, val)                          \
    {                                                                               \
        type _alg_rmcp_dest = dest;                                                 \
        for(const type _alg_rmcp_it = begin; _alg_rmcp_it != end; ++_alg_rmcp_it) { \
            if(*_alg_rmcp_it != val) {                                              \
                *_alg_rmcp_dest++ = *_alg_rmcp_it;                                  \
            }                                                                       \
        }                                                                           \
    }
/**
 * algorithm_partition(type, begin, end, ftype, f, res)
 *
 * Sorts the range [begin, end) where all elements for which the predicate f returns
 * true are moved to the front of the range. The end of this parititioned range is 
 * returned via res. ftype represents the type of the argument taken by the unary
 * predicate f.
 *
 * Ex: algorithm_partition(int*, nums, nums + sz, int, isEven, ptend);
 */
#define algorithm_partition(type, begin, end, predtype, f, res)        \
    res = begin;                                                       \
    for(type _alg_prt_it = begin; _alg_prt_it != end; ++_alg_prt_it) { \
        if(!f(*_alg_prt_it)) {                                         \
            predtype _alg_prt_val = *res;                              \
            *res++ = *_alg_prt_it;                                     \
            *_alg_prt_it = _alg_prt_val;                               \
        }                                                              \
    }

#endif
