#include "../include/gitid-id.h"
#include "../include/git-user.h"
#include "../include/struct.h"
#include "../include/util.h"

#define CSTL_MALLOC safemalloc
#define CSTL_REALLOC saferealloc
#include <cstl/string.h>

#include <stdio.h>

gitid_id* gitid_id_init(void) {
    //Allocate gitid_id
    gitid_id* id = safemalloc(sizeof(gitid_id));

    //Initialize fields
    id->id_name = string_init();
    id->user = git_user_init();

    return id;
}

gitid_id* gitid_id_safe_init(const char* id_n, const char* n, const char* e) {
    if(!id_n || !n || !e) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }
    //Allocate gitid_id and initialize members
    gitid_id* id = safemalloc(sizeof(gitid_id));
    id->id_name = string_init_cstr(id_n);

    //Initialize git-user
    id->user = git_user_safe_init(n, e);

    return id;
}

void gitid_id_set(gitid_id* dest, const gitid_id* src) {
    //Set id_name, and...
    string_assign(dest->id_name, string_begin(src->id_name), string_end(src->id_name));
    //Set the user
    git_user_set(dest->user, src->user);
}

void gitid_id_write(const gitid_id* id, FILE* stream) {
    fprintf(stream, "ID: %s\nName: %s\nEmail: %s\n", string_cstr(id->id_name), string_cstr(id->user->name), string_cstr(id->user->email));
    if(string_size(id->user->signing_key)) {
        fprintf(stream, "Signing Key: %s\n", string_cstr(id->user->signing_key));
    }
}

void gitid_id_min_write(const gitid_id* id, FILE* stream) {
    fprintf(stream, "%s\n%s\n%s\n", string_cstr(id->id_name), string_cstr(id->user->name), string_cstr(id->user->email));
    if(string_size(id->user->signing_key)) {
        fprintf(stream, "%s\n", string_cstr(id->user->signing_key));
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

    //Set into gitid_id
    gitid_id_set_id_name(id, buffer1);
    git_user_set_name(id->user, buffer2);
    git_user_set_email(id->user, buffer3);

    //Test to see if next is ending, or not
    minfgets(buffer1, GITID_ID_BUFFER_MAX, stream);

    //Check if ending delimiter
    if(strncmp(buffer1, GITID_ID_ENDING_DELIMITER, sizeof(GITID_ID_ENDING_DELIMITER) - 1) == 0) {
        return;
    }

    //Otherwise, set signing key into struct
    trimNewline(buffer1);
    git_user_set_signing_key(id->user, buffer1);

    //Read ending delimiter so as to complete read of one entity
    int res;
    while((res = getc(stream)) != '\n' && res != EOF)
        ;

    //NOTE: For the time being, I suppose EOF is "ok", we don't need to enforce an ending delim/newline to read,
    //but it could perhaps be a source of trouble for the function calling this one...? Consider throwing on EOF,
    //or returning EOF from this function if it happens
}

void gitid_id_clear(gitid_id* id) {
    //Clear members
    string_clear(id->id_name);
    git_user_clear(id->user);
}

void gitid_id_free(gitid_id* id) {
    //Free members
    string_free(id->id_name);
    git_user_free(id->user);

    //Free struct
    free(id);
}
