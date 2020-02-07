#include "../include/cli.h"
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

/**
 * arg_xxx* for main_argtable
 */
static struct arg_lit* version;
static struct arg_lit* about;
static struct arg_lit* list;
static struct arg_str* new;
static struct arg_str* update;
static struct arg_str* delete;
static struct arg_str* shift;
static struct arg_lit* current;
static struct arg_lit* global;
static struct arg_lit* local;
static struct arg_str* user;
static struct arg_str* email;
static struct arg_str* sigkey;
static struct arg_lit* help;
static struct arg_end* end;

/**
 * arg_xxx* for clone_argtable
 */
static struct arg_rex* clone_cmd;
static struct arg_str* clone_repo;
static struct arg_str* clone_shift;
static struct arg_lit* clone_verbose;
static struct arg_lit* clone_quiet;
static struct arg_lit* clone_progress;
static struct arg_lit* clone_no_checkout;
static struct arg_lit* clone_bare;
static struct arg_lit* clone_mirror;
static struct arg_lit* clone_local;
static struct arg_lit* clone_no_hardlinks;
static struct arg_lit* clone_shared;
static struct arg_lit* clone_recursive;
static struct arg_lit* clone_recurse_submodules;

static struct arg_str* clone_template;
static struct arg_str* clone_reference;
static struct arg_lit* clone_dissociate;
static struct arg_str* clone_origin;
static struct arg_str* clone_branch;
static struct arg_str* clone_upload_pack;
static struct arg_str* clone_depth;
static struct arg_lit* clone_single_branch;
static struct arg_str* clone_seperate_git_dir;
static struct arg_str* clone_config;

static struct arg_lit* clone_help;
static struct arg_end* clone_end;

int main(int argc, char** argv) {

    setup_constants();

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

    void* clone_argtable[] = {
        clone_cmd = arg_rex1(NULL, NULL, "clone", NULL, 2, NULL),
        clone_repo = arg_strn(NULL, NULL, "<repo>", 1, 1, NULL),
        clone_shift =
            arg_strn("s", "shift", "<id-name>", 0, 1, "set git identity of repo to registered identity post-clone"),
        clone_verbose = arg_litn("v", "verbose", 0, 1, "be more verbose"),
        clone_quiet = arg_litn("q", "quiet", 0, 1, "be more quiet"),
        clone_progress = arg_litn(NULL, "progress", 0, 1, "force progress reporting"),
        clone_no_checkout = arg_litn("n", "no-checkout", 0, 1, "don't create a checkout"),
        clone_bare = arg_litn(NULL, "bare", 0, 1, "create a bare repository"),
        clone_mirror = arg_litn(NULL, "mirror", 0, 1, "create a mirror repository (implies bare)"),
        clone_local = arg_litn("l", "local", 0, 1, "to clone from a local repository"),
        clone_no_hardlinks = arg_litn(NULL, "no-hardlinks", 0, 1, "don't use local hardlinks, always copy"),
        clone_shared = arg_litn("s", "shared", 0, 1, "setup as shared repository"),
        clone_recursive = arg_litn(NULL, "recursive", 0, 1, "initialize submodules in the clone"),
        clone_recurse_submodules = arg_litn(NULL, "recurse-submodules", 0, 1, "initialize submodules in the clone"),
        clone_template =
            arg_strn(NULL, "template", "<template-directory>", 0, 1, "directory from which templates will be used"),
        clone_reference = arg_strn(NULL, "reference", "<repo>", 0, 1, "reference repository"),
        clone_dissociate = arg_litn(NULL, "dissociate", 0, 1, "use --reference only while cloning"),
        clone_origin = arg_strn("o", "origin", "<name>", 0, 1, "use <name> instead of 'origin' to track upstream"),
        clone_branch = arg_strn("b", "branch", "<branch>", 0, 1, "checkout <branch> instead of the remote's HEAD"),
        clone_upload_pack = arg_strn("u", "upload-pack", "<path>", 0, 1, "path to git-upload-pack on the remote"),
        clone_depth = arg_strn(NULL, "depth", "<depth>", 0, 1, "create a shallow clone of that depth"),
        clone_single_branch = arg_litn(NULL, "single-branch", 0, 1, "clone only one branch, HEAD or --branch"),
        clone_seperate_git_dir =
            arg_strn(NULL, "seperate-git-dir", "<gitdir>", 0, 1, "separate git dir from working tree"),
        clone_config = arg_strn("c", "config", "<key=value>", 0, 1, "set config inside the new repository"),
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
        write_main_glossary(stdout, main_argtable);
        clean(main_argtable, clone_argtable, 0);
    } else if(clone_help->count && mode == MODE_CLONE) {
        fprintf(stdout, "Usage: %s clone", PRG_NAME);
        //Print one-line syntax for main argtable
        arg_print_syntax(stdout, clone_argtable, "\n");
        fprintf(stdout, PRG_DESCRIPTION "\n\n");
        arg_print_glossary(stdout, clone_argtable, "  %-35s %s\n");
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
    mkdir(GITID_SYSTEM_FOLDER, 0775);
    int status = access(GITID_SYSTEM_DATA_FILE, F_OK);
    if(status == -1) {
        FILE* sys_gitids = fopen(GITID_SYSTEM_DATA_FILE, "w");
        fclose(sys_gitids);
    }

    //Finally, process options passed
    int ret_code;
    if(mode == MODE_MAIN) {
        ret_code = process_main(main_argtable);
    } else {
        ret_code = process_clone();
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

int process_clone(void) {

    //Initialize a new git_clone_opts and set repo
    git_clone_opts* opts = git_clone_opts_init();
    git_clone_opts_set_repo(opts, *(clone_repo->sval));

    /**
     * Process flags
     */
    if(clone_verbose->count) {
        opts->flags |= GIT_CLONE_OPTS_VERBOSE;
    }

    if(clone_quiet->count) {
        opts->flags |= GIT_CLONE_OPTS_QUIET;
    }

    if(clone_progress->count) {
        opts->flags |= GIT_CLONE_OPTS_PROGRESS;
    }

    if(clone_no_checkout->count) {
        opts->flags |= GIT_CLONE_OPTS_NO_CHECKOUT;
    }

    if(clone_bare->count) {
        opts->flags |= GIT_CLONE_OPTS_BARE;
    }

    if(clone_mirror->count) {
        opts->flags |= GIT_CLONE_OPTS_MIRROR;
    }

    if(clone_local->count) {
        opts->flags |= GIT_CLONE_OPTS_LOCAL;
    }

    if(clone_no_hardlinks->count) {
        opts->flags |= GIT_CLONE_OPTS_NO_HARDLINKS;
    }

    if(clone_shared->count) {
        opts->flags |= GIT_CLONE_OPTS_SHARED;
    }

    if(clone_recursive->count) {
        opts->flags |= GIT_CLONE_OPTS_RECURSIVE;
    }

    if(clone_recurse_submodules->count) {
        opts->flags |= GIT_CLONE_OPTS_RECURSE_SUBMODULES;
    }

    if(clone_template->count) {
        git_clone_opts_set_template(opts, *(clone_template->sval));
    }

    if(clone_reference->count) {
        git_clone_opts_set_reference(opts, *(clone_reference->sval));
    }

    if(clone_dissociate->count) {
        opts->flags |= GIT_CLONE_OPTS_DISSOCIATE;
    }

    if(clone_origin->count) {
        git_clone_opts_set_origin(opts, *(clone_origin->sval));
    }

    if(clone_branch->count) {
        git_clone_opts_set_branch(opts, *(clone_branch->sval));
    }

    if(clone_upload_pack->count) {
        git_clone_opts_set_upload_pack(opts, *(clone_upload_pack->sval));
    }

    if(clone_depth->count) {
        git_clone_opts_set_depth(opts, *(clone_depth->sval));
    }

    if(clone_single_branch->count) {
        opts->flags |= GIT_CLONE_OPTS_SINGLE_BRANCH;
    }

    if(clone_seperate_git_dir->count) {
        git_clone_opts_set_seperate_git_dir(opts, *(clone_seperate_git_dir->sval));
    }

    if(clone_config->count) {
        git_clone_opts_set_config(opts, *(clone_config->sval));
    }

    /**
     * Run git_clone with opts
     */
    if(!git_clone(opts)) {
        exit(1);
    }

    //If shift, cd into cloned dir and set identity
    //Note that if --directory is specified, this can really change things
    if(clone_shift->count) {
        //Parse repo out into "humanish" part
        //TODO: Acquire advice on whether malloc may be better
        char name[1000];
        strcpy(name, opts->repo);
        parseGitURLName(name);

        char buffer[1000];
        strcpy(buffer, "cd ");
        strcat(buffer, name);

        //Look for matching git_id
        gitid_id* id = gitid_id_init();
        gitid_get_system_gitid_id(*(clone_shift->sval), id);

        //Attempt to cd and set
        git_set_user_local_prefix(id->user, buffer);
        printf("Set newly cloned repo to ID \"%s\"!\n", *(clone_shift->sval));
        //Finally, free
        gitid_id_free(id);
    }

    //Free
    git_clone_opts_free(opts);
    return 0;
}

int process_main(void** argtable) {

    /**
     * Process flags
     */
    if(version->count != 0) {
        printf(PRG_VERSION "\n");
        return 0;
    }

    if(about->count != 0) {
        printf(PRG_NAME "\n");
        printf(PRG_DESCRIPTION "\n");
        printf("Version: %s\n", PRG_VERSION);
        printf("Author: Luiserebii\nCheck me out on GitHub at: https://github.com/Luiserebii!\n");
        return 0;
    }

    if(list->count != 0) {
        //Intialize a vector, and grab all system gitids
        vector_gitid_id* v = vector_init_gitid_id();
        gitid_get_system_gitid_ids(v);
        if(vector_size_gitid_id(v)) {
            //Write to stdout
            fputs("All registered identities:\n", stdout);
            for(gitid_id** it = v->head; it != v->avail; ++it) {
                putc('\n', stdout);
                gitid_id_write(*it, stdout);
            }
        } else {
            fputs("No identities registered yet!\n", stdout);
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
            fputs("Current global git identity:\n\n", stdout);
        } else {
            git_get_user_local(user);
            fputs("Current local git identity:\n\n", stdout);
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
            printf("Shifted global git identity to: %s\n", id->id_name);
        } else {
            gitid_shift_gitid_id_local(id);
            printf("Shifted local git identity to: %s\n", id->id_name);
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
    write_main_glossary(stdout, argtable);
    //Exit
    return 0;
}

void write_main_glossary(FILE* stream, void** argtable) {
    fprintf(stream, "Usage: %s", PRG_NAME);
    //Print one-line syntax for main argtable
    arg_print_syntax(stream, argtable, "\n");
    fprintf(stream, PRG_DESCRIPTION "\n\n");
    arg_print_glossary(stream, argtable, "  %-25s %s\n");
    fputs("\nAdditional flags:\n\n-c, --current, --s, --shift:\n", stream);
    fprintf(stream, "  %-25s %s\n", "--global", "refer to global git config");
    fprintf(stream, "  %-25s %s\n", "--local", "refer to local git config (repository-level)");
    fputs("\n-n, --new, -u, --update:\n", stream);
    fprintf(stream, "  %-25s %s\n", "--user=<username>", "specify username");
    fprintf(stream, "  %-25s %s\n", "--email=<email>", "specify email");
    fprintf(stream, "  %-25s %s\n", "--sigkey=<sigkey>", "specify signing key (key-id format: LONG)");
}

void setup_constants(void) {
    generate_path_home(GITID_SYSTEM_DATA_FILE, GITID_SYSTEM_DATA_REL_FILE);
    generate_path_home(GITID_SYSTEM_FOLDER, GITID_SYSTEM_REL_FOLDER);
}
