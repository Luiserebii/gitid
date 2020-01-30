#include "../lib/argtable3/argtable3.h"
#include "../include/gitid.h"
#include "../include/vector-gitid-id.h"

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define PRG_NAME "gitid"
#define PRG_VERSION "0.1.0"

#define clean(argtable, exitcode) \
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0])); \
    return exitcode;

int main(int argc, char** argv) {

    struct arg_lit* version;
    struct arg_lit* about;
    struct arg_lit* list;
    
    struct arg_lit* global;
    struct arg_lit* local;
    
    struct arg_lit* help;
    struct arg_end* end;
    

    void* argtable[] = {
        version = arg_litn("v", "version", 0, 1, "output the version number"),
        about = arg_litn("a", "about", 0, 1, "about this tool"),
        list = arg_litn("l", "list", 0, 1, "list all registered identities"),
        global = arg_litn(NULL, "global", 0, 1, "global (option for -s and -c)"),
        local = arg_litn(NULL, "local", 0, 1, "local (option for -s and -c)"),
        help = arg_litn("h", "help", 0, 1, "display this help and exit"),
        end = arg_end(20)
    };

    //Parse, and capture errors from parsing
    int nerrors = arg_parse(argc, argv, argtable);

    //Check for --help as a special case, before checking for errors
    if(help->count) {
        printf("Usage: %s", PRG_NAME);
        //Print one-line syntax for main argtable
        arg_print_syntax(stdout, argtable, "\n");
        printf("A command line tool allowing for easy shifting between git identities (username, email, and signing key).\n\n");
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
        printf("A command line tool allowing for easy shifting between git identities (username, email, and signing key).\n");
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

    //Exit
    clean(argtable, 0);
}
