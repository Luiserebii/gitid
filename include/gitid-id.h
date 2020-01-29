#ifndef GITID_ID_H
#define GITID_ID_H

#include "../include/struct.h"
#include "../include/git-user.h"

#include <stdio.h>

#define GITID_ID_BUFFER_MAX 1000
#define GITID_ID_ENDING_DELIMITER "____________"

typedef struct {
    char* id_name;
    git_user* user;
} gitid_id;

/**
 * Allocates space for a new git_user struct.
 */
gitid_id* gitid_id_init();

/**
 * Invariant protected: name, username, and email set
 */
gitid_id* gitid_id_safe_init(const char* id_n, const char* n, const char* e);

/**
 * void gitid_id_set_name(gitid_id* opts, const char* n);
 */
declare_struct_set_string(gitid_id, id_name, id, id_n);

/**
 * Writes git_id struct to a FILE* stream.
 */
void gitid_id_write(gitid_id* id, FILE* stream);

/**
 * Writes git_id struct to a FILE* stream, in a minimal format.
 */
void gitid_id_min_write(gitid_id* id, FILE* stream);

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
 */
void gitid_id_clear(gitid_id* id);

/**
 * Frees gitid_id struct.
 */
void gitid_id_free(gitid_id* id);

#endif
