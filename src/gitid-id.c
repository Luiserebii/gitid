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
    fprintf(stream, "| %s\n| %s\n| %s\n", id->id_name, id->name, id->email);
    if(id->signing_key) {
        fprintf(stream, "| %s\n", id->signing_key);
    }
    //Close with ending ___
    fprintf(stream, GITID_ID_ENDING_DELIMITER "\n");
}

void gitid_id_min_read(gitid_id* id, FILE* stream) {
    char buffer1[GITID_ID_BUFFER_MAX];
    char buffer2[GITID_ID_BUFFER_MAX];
    char buffer3[GITID_ID_BUFFER_MAX];

    //Load into buffers
    int res;
    if((res = fscanf(stream, "| %s\n| %s\n| %s\n", buffer1, buffer2, buffer3)) != 3) {
        fprintf(stderr, "error reading file stream: only %d arguments found\n", res);
        fprintf(stderr, "Dumping buffer contents:\n1: %s\n2: %s\n3: %s\n", buffer1, buffer2, buffer3);
        exit(1);
    }
    
    //Set into struct
    gitid_id_set_id_name(id, buffer1);
    gitid_id_set_name(id, buffer1);
    gitid_id_set_email(id, buffer1);
    
    //Test to see if next is ending, or not
    if(fgets(buffer1, GITID_ID_BUFFER_MAX, stream) == NULL) {
        fprintf(stderr, "error reading file stream: potential unexpected EOF or other error\n");
        fprintf(stderr, "Dumping buffer contents:\n1: %s\n", buffer1);
        exit(1);
    }
    //Check if ending delimiter
    if(strncmp(buffer1, GITID_ID_ENDING_DELIMITER, sizeof(GITID_ID_ENDING_DELIMITER) - 1) == 0) {
        return;
    }
    //Otherwise, continue to parse the signing key
    if(sscanf(buffer1, "| %s\n", buffer1) != 1) {
        fprintf(stderr, "error reading file stream: expected signing key not found\n");
        fprintf(stderr, "Dumping buffer contents:\n1: %s\n", buffer1);
        exit(1);
    }

    //Finally, set signing key into struct
    gitid_id_set_signing_key(id, buffer1);

    //Read ending delimiter so as to complete read of one entity
    while((res = getc(stream)) != '\n' && res != EOF)
        ;

    //NOTE: For the time being, I suppose EOF is "ok", we don't need to enforce an ending delim/newline to read,
    //but it could perhaps be a source of trouble for the function calling this one...? Consider throwing on EOF,
    //or returning EOF from this function if it happens
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
