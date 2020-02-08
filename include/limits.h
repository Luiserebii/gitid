#ifndef LIMITS_H
#define LIMITS_H

#include <limits.h>

/**
 * FILEPATH_MAX is meant to represent the maximum size in an array
 * or buffer containing chars, so we allocate 1 more for '\0'.
 */
#define FILEPATH_MAX PATH_MAX + 1

#endif
