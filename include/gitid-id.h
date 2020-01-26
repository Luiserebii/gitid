#ifndef GITID_ID_H
#define GITID_ID_H

#include "../include/struct.h"

#include <stdio.h>

#define GITID_ID_BUFFER_MAX 1000

typedef struct {
    char* name;
    char* username;
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
gitid_id* gitid_id_safe_init(const char* n, const char* usrn, const char* e);

/**
 * void gitid_id_set_name(gitid_id* opts, const char* n);
 * void gitid_id_set_username(gitid_id* opts, const char* usrn);
 * void gitid_id_set_email(gitid_id* opts, const char* e);
 * void gitid_id_set_signing_key(gitid_id* opts, const char* sk);
 */
declare_struct_set_string(gitid_id, name, opts, n);
declare_struct_set_string(gitid_id, username, opts, usrn);
declare_struct_set_string(gitid_id, email, opts, e);
declare_struct_set_string(gitid_id, signing_key, opts, sk);

/**
 * Writes git_id struct to a FILE* stream.
 */
void gitid_id_write(gitid_id* id, FILE* stream);

/**
 * Frees gitid_id struct.
 */
void gitid_id_free(gitid_id* id);

#endif
