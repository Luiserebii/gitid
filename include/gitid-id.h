#ifndef GITID_ID_H
#define GITID_ID_H

#include "../include/struct.h"

#include <stdio.h>

#define GITID_ID_BUFFER_MAX 1000
#define GITID_ID_ENDING_DELIMITER "____________"

typedef struct {
    char* id_name;
    char* name;
    char* email;
    char* signing_key;
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
 * void gitid_id_set_username(gitid_id* opts, const char* usrn);
 * void gitid_id_set_email(gitid_id* opts, const char* e);
 * void gitid_id_set_signing_key(gitid_id* opts, const char* sk);
 */
declare_struct_set_string(gitid_id, id_name, id, id_n);
declare_struct_set_string(gitid_id, name, id, n);
declare_struct_set_string(gitid_id, email, id, e);
declare_struct_set_string(gitid_id, signing_key, id, sk);

/**
 * Writes git_id struct to a FILE* stream.
 */
void gitid_id_write(gitid_id* id, FILE* stream);

/**
 * Writes git_id struct to a FILE* stream, in a minimal format.
 */
void gitid_id_min_write(gitid_id* id, FILE* stream);

/**
 * Frees gitid_id struct.
 */
void gitid_id_free(gitid_id* id);

#endif
