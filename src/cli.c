#include "../include/git-user.h"
#include "../include/git.h"
#include "../include/gitid.h"
#include "../include/vector-gitid-id.h"
#include "../lib/argtable3/argtable3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PRG_NAME "gitid"
#define PRG_VERSION "0.1.0-alpha"

#define clean(argtable, exitcode)                                    \
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0])); \
    return exitcode;

void write_glossary(FILE* stream, void** argtable);

int main(int argc, char** argv) {

    struct arg_lit* version;
    struct arg_lit* about;
    struct arg_lit* list;

    struct arg_str* new;
    struct arg_str* update;
    struct arg_str* delete;
    struct arg_str* shift;

    struct arg_lit* current;

    struct arg_lit* global;
    struct arg_lit* local;
    struct arg_str* user;
    struct arg_str* email;
    struct arg_str* sigkey;

    struct arg_lit* help;
    struct arg_end* end;

    void* argtable[] = {version = arg_litn("v", "version", 0, 1, "output the version number"),
                        about = arg_litn("a", "about", 0, 1, "about this tool"),
                        list = arg_litn("l", "list", 0, 1, "list all registered identities"),
                        current = arg_litn("c", "current", 0, 1, "current global git identity"),
                        shift = arg_strn("s", "shift", "<id-name>", 0, 1,
                                         "shift git identity to registered identity (global by default)"),
                        new = arg_strn("n", "new", "<id-name>", 0, 1, "add new identity"),
                        update = arg_strn("u", "update", "<id-name>", 0, 1, "update registered identity"),
                        delete = arg_strn("d", "delete", "<id-name>", 0, 1, "delete registered identity"),
                        global = arg_litn(NULL, "global", 0, 1, /*"global (option for -s and -c)"*/ NULL),
                        local = arg_litn(NULL, "local", 0, 1, /*"local (option for -s and -c)"*/ NULL),
                        user = arg_strn(NULL, "user", "<username>", 0, 1, /*specify username*/ NULL),
                        email = arg_strn(NULL, "email", "<email>", 0, 1, /*specify email*/ NULL),
                        sigkey = arg_strn(NULL, "sigkey", "<sigkey>", 0, 1, /*specify signing key*/ NULL),
                        help = arg_litn("h", "help", 0, 1, "display this help and exit"), end = arg_end(20)};

    //Parse, and capture errors from parsing
    int nerrors = arg_parse(argc, argv, argtable);

    //Check for --help as a special case, before checking for errors
    if(help->count) {
        write_glossary(stdout, argtable);
        //Exit
        clean(argtable, 0);
    }

    //If there are errors, print them!
    if(nerrors) {
        arg_print_errors(stderr, end, PRG_NAME);
        clean(argtable, 1);
    }

    /**
     * Setup (check if no file, if none, make a blank one)
     */
    //Attempt the creation of the data dir; if it already exists, this'll
    //fail anyways (lazy solution, perhaps has issues)
    mkdir("./data/", 0775);
    int status = access(GITID_SYSTEM_DATA_FILE, F_OK);
    if(status == -1) {
        FILE* sys_gitids = fopen(GITID_SYSTEM_DATA_FILE, "w");
        fclose(sys_gitids);
    }

    /**
     * Process flags
     */
    if(version->count != 0) {
        printf(PRG_VERSION "\n");
        clean(argtable, 1);
    }

    if(about->count != 0) {
        printf(PRG_NAME "\n");
        printf(
            "A command line tool allowing for easy shifting between git identities (username, email, and signing "
            "key).\n");
        printf("Version: %s\n", PRG_VERSION);
        printf("Author: Luiserebii\nCheck me out on GitHub at: https://github.com/Luiserebii!\n");
        clean(argtable, 1);
    }

    if(list->count != 0) {
        //Intialize a vector, and grab all system gitids
        vector_gitid_id* v = vector_init_gitid_id();
        gitid_get_system_gitid_ids(v);
        //Write to stdout
        for(gitid_id** it = v->head; it != v->avail; ++it) {
            gitid_id_write(*it, stdout);
        }
        //Free
        vector_free_gitid_id(v);
        clean(argtable, 1);
    }

    if(current->count != 0) {
        //Assert not both --global and --local
        if(global->count && local->count) {
            fputs("Error: --global and --local both specified\n", stderr);
            exit(1);
        }
        //Init git_user and obtain latest
        git_user* user = git_user_init();

        //If local not specified, global is default anyways, so print global
        if(!local->count) {
            git_get_user_global(user);
        } else {
            git_get_user_local(user);
        }
        //Print, and free
        git_user_write(user, stdout);
        git_user_free(user);
        clean(argtable, 1);
    }

    if(shift->count != 0) {
        //TODO: I just spotted an early bug here, we have a case where a gitid
        //that has no signing key that is set, will not actually clear the signing
        //key used, it'll just overwrite user.name and user.email.

        //Assert not both --global and --local
        if(global->count && local->count) {
            fputs("Error: --global and --local both specified\n", stderr);
            exit(1);
        }

        //Try to obtain all vectors
        vector_gitid_id* v = vector_init_gitid_id();
        gitid_get_system_gitid_ids(v);

        gitid_id* id;
        //Look for matching
        for(gitid_id** it = v->head; it != v->avail; ++it) {
            if(strcmp((*it)->id_name, *(shift->sval)) == 0) {
                id = *it;
                break;
            }
        }
        //If nothing found, print error and break
        if(id == NULL) {
            fprintf(stderr, "Error: No git id found under the name \"%s\"\n", *(shift->sval));
            exit(1);
        }

        //Finally, set
        if(!local->count) {
            gitid_shift_gitid_id_global(id);
        } else {
            gitid_shift_gitid_id_local(id);
        }

        //And, finally, free vector (no need to free id)
        vector_free_gitid_id(v);
        clean(argtable, 1);
    }

    if(new->count != 0) {
        //Assert all flags needed
        if(!user->count && !email->count) {
            fputs("Error: minimum --user and --email must be specified.\n", stderr);
        }

        //Construct gitid_id
        gitid_id* new_id = gitid_id_init();
        gitid_id_set_id_name(new_id, *(new->sval));
        git_user_set_name(new_id->user, *(user->sval));
        git_user_set_email(new_id->user, *(email->sval));
        if(sigkey->count) {
            git_user_set_signing_key(new_id->user, *(sigkey->sval));
        }

        //Finally, attempt to add
        gitid_new_system_gitid_id(new_id);

        //Free
        gitid_id_free(new_id);
        clean(argtable, 1);
    }

    if(update->count != 0) {
        //NOTE: This function will not change the ID, due to the way the flags are
        //currently set up.

        //Assert all flags needed
        if(!user->count && !email->count) {
            fputs("Error: minimum --user and --email must be specified.\n", stderr);
        }

        //Construct gitid_id
        gitid_id* upd_id = gitid_id_init();
        gitid_id_set_id_name(upd_id, *(update->sval));
        git_user_set_name(upd_id->user, *(user->sval));
        git_user_set_email(upd_id->user, *(email->sval));
        if(sigkey->count) {
            git_user_set_signing_key(upd_id->user, *(sigkey->sval));
        }

        //Finally, attempt to update
        gitid_update_system_gitid_id(upd_id, *(update->sval));

        //Free
        gitid_id_free(upd_id);
        clean(argtable, 1);
    }

    if(delete->count != 0) {
        //Attempt a delete
        gitid_delete_system_gitid_id(*(delete->sval));
        clean(argtable, 1);
    }

    //If we reached here, nothing was passed, so show glossary
    write_glossary(stdout, argtable);
    //Exit
    clean(argtable, 0);
}

void write_glossary(FILE* stream, void** argtable) {
    fprintf(stream, "Usage: %s", PRG_NAME);
    //Print one-line syntax for main argtable
    arg_print_syntax(stream, argtable, "\n");
    fprintf(stream,
            "A command line tool allowing for easy shifting between git identities (username, email, and signing "
            "key).\n\n");
    arg_print_glossary(stream, argtable, "  %-25s %s\n");
    fputs("\nAdditional flags:\n\n-c, --current, --s, --shift:\n", stream);
    fprintf(stream, "  %-25s %s\n", "--global", "global (option for -s and -c)");
    fprintf(stream, "  %-25s %s\n", "--local", "local (option for -s and -c)");
    fputs("\n-n, --new, -u, --update:\n", stream);
    fprintf(stream, "  %-25s %s\n", "--user=<username>", "specify username");
    fprintf(stream, "  %-25s %s\n", "--email=<email>", "specify email");
    fprintf(stream, "  %-25s %s\n", "--sigkey=<sigket>", "specify signing key (key-id format: LONG)");
}
