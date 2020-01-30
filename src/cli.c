#include "../include/gitid.h"
#include "../include/vector-gitid-id.h"
#include "../lib/argtable3/argtable3.h"

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define PRG_NAME "gitid"
#define PRG_VERSION "0.1.0-alpha"

#define clean(argtable, exitcode)                                    \
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0])); \
    return exitcode;

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
                        new = arg_strn("n", "new", "<id-name>", 0, 1, "add new identity"),
                        update = arg_strn("u", "update", "<id-name>", 0, 1, "update registered identity"),
                        delete = arg_strn("d", "delete", "<id-name>", 0, 1, "delete registered identity"),
                        shift = arg_strn("s", "shift", "<id-name>", 0, 1, "shift git identity to registered identity (global by default)"),
                        current = arg_litn("c", "current", 0, 1, "current global git identity"),
                        global = arg_litn(NULL, "global", 0, 1, /*"global (option for -s and -c)"*/ NULL),
                        local = arg_litn(NULL, "local", 0, 1, /*"local (option for -s and -c)"*/ NULL),
                        user = arg_strn(NULL, "user", "<username>", 0, 1, /*specify username*/ NULL),
                        email = arg_strn(NULL, "email", "<email>", 0, 1, /*specify email*/ NULL),
                        sigkey = arg_strn(NULL, "sigkey", "<sigkey>", 0, 1, /*specify signing key*/ NULL),
                        help = arg_litn("h", "help", 0, 1, "display this help and exit"),
                        end = arg_end(20)};

    //Parse, and capture errors from parsing
    int nerrors = arg_parse(argc, argv, argtable);

    //Check for --help as a special case, before checking for errors
    if(help->count) {
        printf("Usage: %s", PRG_NAME);
        //Print one-line syntax for main argtable
        arg_print_syntax(stdout, argtable, "\n");
        printf(
            "A command line tool allowing for easy shifting between git identities (username, email, and signing "
            "key).\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
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
    }

    if(about->count != 0) {
        printf(PRG_NAME "\n");
        printf(
            "A command line tool allowing for easy shifting between git identities (username, email, and signing "
            "key).\n");
        printf("Version: %s\n", PRG_VERSION);
        printf("Author: Luiserebii\nCheck me out on GitHub at: https://github.com/Luiserebii!\n");
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
    }

    //if()

    //Exit
    clean(argtable, 0);
}
