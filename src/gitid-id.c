#include "../include/gitid-id.h"
#include "../include/struct.h"
#include "../include/util.h"

#include <stdio.h>
#include <string.h>

gitid_id* gitid_id_init() {
    //Allocate gitid_id
    gitid_id* id = safemalloc(sizeof(gitid_id));

    //Initialize fields
    id->id_name = id->name = id->email = id->signing_key = NULL;

    return id;
}

gitid_id* gitid_id_safe_init(const char* id_n, const char* n, const char* e) {
    if(!id_n || !n || !e) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }
    //Allocate gitid_id
    gitid_id* id = safemalloc(sizeof(gitid_id));

    gitid_id_set_id_name(id, id_n);
    gitid_id_set_name(id, n);
    gitid_id_set_email(id, e);

    //Initialize fields
    id->signing_key = NULL;

    return id;
}

/**
 * MACRO use: Define struct functions for each char* member
 */
define_struct_set_string(gitid_id, id_name, opts, id_n);
define_struct_set_string(gitid_id, name, opts, n);
define_struct_set_string(gitid_id, email, opts, e);
define_struct_set_string(gitid_id, signing_key, opts, sk);

void gitid_id_write(gitid_id* id, FILE* stream) {
    fprintf(stream, "ID: %s\nName: %s\nEmail: %s\n", id->id_name, id->name, id->email);
    if(id->signing_key) {
        fprintf(stream, "Signing Key: %s\n", id->signing_key);
    }
}

void gitid_id_min_write(gitid_id* id, FILE* stream) {
    fprintf(stream, "%s\n%s\n%s\n", id->id_name, id->name, id->email);
    if(id->signing_key) {
        fprintf(stream, "%s\n", id->signing_key);
    }
    //Close with ending ___
    fprintf(stream, GITID_ID_ENDING_DELIMITER "\n");
}

void gitid_id_min_read(gitid_id* id, FILE* stream) {
    char buffer1[GITID_ID_BUFFER_MAX];
    char buffer2[GITID_ID_BUFFER_MAX];
    char buffer3[GITID_ID_BUFFER_MAX];

    //Load into buffers
    minfgets(buffer1, GITID_ID_BUFFER_MAX, stream);
    minfgets(buffer2, GITID_ID_BUFFER_MAX, stream);
    minfgets(buffer3, GITID_ID_BUFFER_MAX, stream);

    //Trim newlines off
    trimNewline(buffer1), trimNewline(buffer2), trimNewline(buffer3);

    //Set into struct
    gitid_id_set_id_name(id, buffer1);
    gitid_id_set_name(id, buffer2);
    gitid_id_set_email(id, buffer3);

    //Test to see if next is ending, or not
    minfgets(buffer1, GITID_ID_BUFFER_MAX, stream);

    //Check if ending delimiter
    if(strncmp(buffer1, GITID_ID_ENDING_DELIMITER, sizeof(GITID_ID_ENDING_DELIMITER) - 1) == 0) {
        return;
    }

    //Otherwise, set signing key into struct
    trimNewline(buffer1);
    gitid_id_set_signing_key(id, buffer1);

    //Read ending delimiter so as to complete read of one entity
    int res;
    while((res = getc(stream)) != '\n' && res != EOF)
        ;

    //NOTE: For the time being, I suppose EOF is "ok", we don't need to enforce an ending delim/newline to read,
    //but it could perhaps be a source of trouble for the function calling this one...? Consider throwing on EOF,
    //or returning EOF from this function if it happens
}

void gitid_id_clear(gitid_id* id) {
    //Free members
    free(id->id_name);
    free(id->name);
    free(id->email);
    free(id->signing_key);

    //Reset to NULL
    id->id_name = id->name = id->email = id->signing_key = NULL;
}

void gitid_id_free(gitid_id* id) {
    //Free members
    free(id->id_name);
    free(id->name);
    free(id->email);
    free(id->signing_key);

    //Free struct
    free(id);
}
