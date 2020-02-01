#include "../include/git-user.h"
#include "../include/git.h"
#include "../include/gitid.h"
#include "../include/util.h"
#include "../include/vector-gitid-id.h"
#include "../lib/argtable3/argtable3.h"
#include "../lib/c-stl/include/algorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PRG_NAME "gitid"
#define PRG_VERSION "0.1.0-alpha"

#define clean(m_argtable, c_argtable, exitcode)                            \
    arg_freetable(m_argtable, sizeof(m_argtable) / sizeof(m_argtable[0])); \
    arg_freetable(c_argtable, sizeof(c_argtable) / sizeof(c_argtable[0])); \
    return exitcode;

typedef enum { MODE_MAIN, MODE_CLONE } CLI_MODE;

void write_glossary(FILE* stream, void** argtable);
int process_main(void** argtable, struct arg_lit* version, struct arg_lit* about, struct arg_lit* list,
                 struct arg_str* new, struct arg_str* update, struct arg_str* delete, struct arg_str* shift,
                 struct arg_lit* current, struct arg_lit* global, struct arg_lit* local, struct arg_str* user,
                 struct arg_str* email, struct arg_str* sigkey, struct arg_end* end);
int process_clone(void** argtable, struct arg_rex* clone, struct arg_str* repo, struct arg_str* clone_shift,
                  struct arg_end* end);
CLI_MODE identifyMode(struct arg_rex* clone);
void parseGitURLName(char* url);

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

    void* main_argtable[] = {version = arg_litn("v", "version", 0, 1, "output the version number"),
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

    struct arg_rex* clone_cmd;
    struct arg_str* repo;
    struct arg_str* clone_shift;
    struct arg_lit* clone_help;
    struct arg_end* clone_end;

    void* clone_argtable[] = {
        clone_cmd = arg_rex1(NULL, NULL, "clone", NULL, 2, NULL), repo = arg_strn(NULL, NULL, "<repo>", 1, 1, NULL),
        clone_shift =
            arg_strn("s", "shift", "<id-name>", 0, 1, "set git identity of repo to registered identity post-clone"),
        clone_help = arg_litn("h", "help", 0, 1, "display this help and exit"), clone_end = arg_end(20)};

    if(arg_nullcheck(main_argtable) != 0 || arg_nullcheck(clone_argtable) != 0) {
        fprintf(stderr, "%s: insufficient memory\n", PRG_NAME);
        exit(1);
    }

    //Parse, and capture errors from parsing
    int nerrors_main = arg_parse(argc, argv, main_argtable);
    int nerrors_clone = arg_parse(argc, argv, clone_argtable);

    //Identify mode post-parsing
    CLI_MODE mode = identifyMode(clone_cmd);

    //Check for --help early so as to not get caught up in errors (e.g. git clone --help)
    //would break otherwise, since <repo> is required
    if(help->count && mode == MODE_MAIN) {
        write_glossary(stdout, main_argtable);
        clean(main_argtable, clone_argtable, 0);
    } else if(clone_help->count && mode == MODE_CLONE) {
        fprintf(stdout, "Usage: %s clone", PRG_NAME);
        //Print one-line syntax for main argtable
        arg_print_syntax(stdout, clone_argtable, "\n");
        fprintf(stdout,
                "A command line tool allowing for easy shifting between git identities (username, email, and signing "
                "key).\n\n");
        arg_print_glossary(stdout, clone_argtable, "  %-25s %s\n");
        return 0;
    }

    //If there are errors, print them!
    if(nerrors_main && nerrors_clone) {
        if(mode == MODE_MAIN) {
            arg_print_errors(stderr, end, PRG_NAME);
            clean(main_argtable, clone_argtable, 1);
        } else {
            arg_print_errors(stderr, clone_end, PRG_NAME "-clone");
            clean(main_argtable, clone_argtable, 1);
        }
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

    //Finally, process options passed
    int ret_code;
    if(mode == MODE_MAIN) {
        ret_code = process_main(main_argtable, version, about, list, new, update, delete, shift, current, global, local,
                                user, email, sigkey, end);
    } else {
        ret_code = process_clone(clone_argtable, clone_cmd, repo, clone_shift, clone_end);
    }
    clean(main_argtable, clone_argtable, ret_code);
}

CLI_MODE identifyMode(struct arg_rex* clone) {
    if(clone->count) {
        return MODE_CLONE;
    } else {
        return MODE_MAIN;
    }
}

int process_clone(void** argtable, struct arg_rex* clone, struct arg_str* repo, struct arg_str* clone_shift,
                  struct arg_end* end) {
    /**
     * Process flags
     */
    //Initialize a new git_clone_opts and set repo
    git_clone_opts* opts = git_clone_opts_init();
    git_clone_opts_set_repo(opts, *(repo->sval));

    git_clone(opts);

    //If shift, cd into cloned dir and set identity
    //Note that if --directory is specified, this can really change things
    if(clone_shift->count) {
        //Parse repo out into "humanish" part
        //TODO: Acquire advice on whether malloc may be better
        char name[1000];
        strcpy(name, *(repo->sval));
        parseGitURLName(name);
        
        char buffer[1000];
        strcpy(buffer, "cd ");
        strcat(buffer, name);
        printf("Runningfre: %s", buffer);

        //Look for matching git_id
        gitid_id* id = gitid_id_init();
        gitid_get_system_gitid_id(*(clone_shift->sval), id);

        //Attempt to cd and set
        git_set_user_local_prefix(id->user, buffer);
        //Finally, free
        gitid_id_free(id);
        exit(0);
    }

    //Free
    git_clone_opts_free(opts);
    return 0;
}

int process_main(void** argtable, struct arg_lit* version, struct arg_lit* about, struct arg_lit* list,
                 struct arg_str* new, struct arg_str* update, struct arg_str* delete, struct arg_str* shift,
                 struct arg_lit* current, struct arg_lit* global, struct arg_lit* local, struct arg_str* user,
                 struct arg_str* email, struct arg_str* sigkey, struct arg_end* end) {

    /**
     * Process flags
     */
    if(version->count != 0) {
        printf(PRG_VERSION "\n");
        return 0;
    }

    if(about->count != 0) {
        printf(PRG_NAME "\n");
        printf(
            "A command line tool allowing for easy shifting between git identities (username, email, and signing "
            "key).\n");
        printf("Version: %s\n", PRG_VERSION);
        printf("Author: Luiserebii\nCheck me out on GitHub at: https://github.com/Luiserebii!\n");
        return 0;
    }

    if(list->count != 0) {
        fputs("All registered identities:\n", stdout);
        //Intialize a vector, and grab all system gitids
        vector_gitid_id* v = vector_init_gitid_id();
        gitid_get_system_gitid_ids(v);
        //Write to stdout
        for(gitid_id** it = v->head; it != v->avail; ++it) {
            putc('\n', stdout);
            gitid_id_write(*it, stdout);
        }
        //Free
        vector_free_gitid_id(v);
        return 0;
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
        return 0;
    }

    if(shift->count != 0) {
        //Assert not both --global and --local
        if(global->count && local->count) {
            fputs("Error: --global and --local both specified\n", stderr);
            exit(1);
        }

        //Look for matching git_id
        gitid_id* id = gitid_id_init();
        gitid_get_system_gitid_id(*(shift->sval), id);

        //Finally, set
        if(!local->count) {
            gitid_shift_gitid_id_global(id);
        } else {
            gitid_shift_gitid_id_local(id);
        }

        //And, finally, free id
        gitid_id_free(id);
        return 0;
    }

    if(new->count != 0) {
        //Assert all flags needed
        if(!user->count || !email->count) {
            fputs("Error: minimum --user and --email must be specified.\n", stderr);
            exit(1);
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
        return 0;
    }

    if(update->count != 0) {
        //NOTE: This function will not change the ID, due to the way the flags are
        //currently set up.

        //Assert all flags needed
        if(!user->count && !email->count) {
            fputs("Error: minimum --user and --email must be specified.\n", stderr);
            exit(1);
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
        return 0;
    }

    if(delete->count != 0) {
        //Attempt a delete
        gitid_delete_system_gitid_id(*(delete->sval));
        return 0;
    }

    //If we reached here, nothing was passed, so show glossary
    write_glossary(stdout, argtable);
    //Exit
    return 0;
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
