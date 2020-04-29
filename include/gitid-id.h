#ifndef GITID_ID_H
#define GITID_ID_H

#include "../include/git-user.h"
#include "../include/struct.h"

#include <cstl/string.h>
#include <stdio.h>

#define GITID_ID_BUFFER_MIN 20
#define GITID_ID_ENDING_DELIMITER "____________"

typedef struct {
    string id_name;
    git_user user;
} gitid_id;

/**
 * Initializes a gitid_id struct.
 */
void gitid_id_init(gitid_id* id);

/**
 * Invariant protected: name, username, and email set
 */
void gitid_id_safe_init(gitid_id* id, const char* id_n, const char* n, const char* e);

/**
 * Set the values of dest to the values of src. Note that the function
 * does not disrupt any pointers; the gitid_id struct pointer and the
 * git_user struct is guaranteed to stay.
 *
 * string member pointers do not change, as they are simply use
 * string_assign.
 */
void gitid_id_set(gitid_id* dest, const gitid_id* src);

/**
 * Writes git_id struct to a FILE* stream.
 */
void gitid_id_write(const gitid_id* id, FILE* stream);

/**
 * Writes git_id struct to a FILE* stream, in a minimal format.
 */
void gitid_id_min_write(const gitid_id* id, FILE* stream);

/**
 * Reads git_id struct from a FILE* stream, expecting the minimal format.
 * Will throw errors and exit if any errors occur. 
 *
 * This function will read under the assumption that the next characters 
 * in the stream represent a complete gitid_id; it is recommended to check for EOF
 * beforehand, if grabbing multiple of these.
 *
 * The last characters read from this function are guaranteed to include the ending
 * delimiter and following newline under a valid ending delimiter input.
 */
void gitid_id_min_read(gitid_id* id, FILE* stream);

/**
 * Clears all members, resetting them to NULL, but does not deallocate the struct.
 * Note that this function will also "recursively" clear all members, which leaves
 * the struct in a valid state (a deallocated struct member would be invalid).
 */
void gitid_id_clear(gitid_id* id);

/**
 * Deinitializes gitid_id struct.
 */
void gitid_id_deinit(gitid_id* id);

#endif
