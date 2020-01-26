#ifndef GITID_ID_H
#define GITID_ID_H

#include "../include/struct.h"

#define GITID_ID_MAXSTRING 1000

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
 * Frees gitid_id struct.
 */
void gitid_id_free(gitid_id* id);

#endif
