#include "../include/gitid-id.h"
#include "../include/git-user.h"
#include "../include/struct.h"
#include "../include/util.h"

#include <cstl/algorithm.h>
#include <cstl/string.h>

#include <stdio.h>

void gitid_id_init(gitid_id* id) {
    //Initialize fields
    string_init(&id->id_name);
    git_user_init(&id->user);
}

void gitid_id_safe_init(gitid_id* id, const char* id_n, const char* n, const char* e) {
    if(!id_n || !n || !e) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }

    string_init_cstr(&id->id_name, id_n);
    git_user_safe_init(&id->user, n, e);
}

void gitid_id_set(gitid_id* dest, const gitid_id* src) {
    //Set id_name, and...
    string_asn(&dest->id_name, &src->id_name);
    //Set the user
    git_user_set(&dest->user, &src->user);
}

void gitid_id_write(const gitid_id* id, FILE* stream) {
    fprintf(stream, "ID: %s\nName: %s\nEmail: %s\n", string_cstr(&id->id_name), string_cstr(&id->user.name),
            string_cstr(&id->user.email));
    if(string_size(&id->user.signing_key)) {
        fprintf(stream, "Signing Key: %s\n", string_cstr(&id->user.signing_key));
    }
}

void gitid_id_min_write(const gitid_id* id, FILE* stream) {
    fprintf(stream, "%s\n%s\n%s\n", string_cstr(&id->id_name), string_cstr(&id->user.name),
            string_cstr(&id->user.email));
    if(string_size(&id->user.signing_key)) {
        fprintf(stream, "%s\n", string_cstr(&id->user.signing_key));
    }
    //Close with ending ___
    fprintf(stream, GITID_ID_ENDING_DELIMITER "\n");
}

void gitid_id_min_read(gitid_id* id, FILE* stream) {
    string buf1, buf2, buf3;

    string_init_capacity(&buf1, GITID_ID_BUFFER_MIN);
    string_init_capacity(&buf2, GITID_ID_BUFFER_MIN);
    string_init_capacity(&buf3, GITID_ID_BUFFER_MIN);

    //Load into buffers
    string_fgets_min(&buf1, stream);
    string_fgets_min(&buf2, stream);
    string_fgets_min(&buf3, stream);

    //Set into gitid_id
    string_asn(&id->id_name, &buf1);
    string_asn(&id->user.name, &buf2);
    string_asn(&id->user.email, &buf3);

    //Test to see if next is ending, or not
    string_clear(&buf1);
    string_fgets_min(&buf1, stream);

    //Check if ending delimiter
    if(string_cmp_cstr(&buf1, GITID_ID_ENDING_DELIMITER) == 0) {
        string_deinit(&buf1), string_deinit(&buf2), string_deinit(&buf3);
        return;
    }

    //Otherwise, set signing key into struct
    string_asn(&id->user.signing_key, &buf1);

    //Read ending delimiter so as to complete read of one entity
    int res;
    while((res = getc(stream)) != '\n' && res != EOF)
        ;

    string_deinit(&buf1), string_deinit(&buf2), string_deinit(&buf3);

    //NOTE: For the time being, I suppose EOF is "ok", we don't need to enforce an ending delim/newline to read,
    //but it could perhaps be a source of trouble for the function calling this one...? Consider throwing on EOF,
    //or returning EOF from this function if it happens
}

void gitid_id_clear(gitid_id* id) {
    //Clear members
    string_clear(&id->id_name);
    git_user_clear(&id->user);
}

void gitid_id_deinit(gitid_id* id) {
    //Deinit members
    string_deinit(&id->id_name);
    git_user_deinit(&id->user);
}
