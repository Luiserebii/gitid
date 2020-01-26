#ifndef GIT_CLONE_H
#define GIT_CLONE_H

#define GIT_CLONE_OPTS_MAXSTRING 1000

typedef struct {
    char* repo;
    int verbose;
    int quiet;
    int progress;
    int no_checkout;
    int bare;
    int mirror;
    int local;
    int no_hardlinks;
    int shared;
    int recursive;
    int recurse_submodules;
    char* template;
    char* reference;
    int dissociate;
    char* origin;
    char* branch;
    char* upload_pack;
    char* depth;
    int single_branch;
    char* seperate_git_dir;
    char* config;
} git_clone_opts;

/**
 * Allocates space for a new git_clone_opts struct.
 */
git_clone_opts* git_clone_opts_init();

/**
 * If new, allocate the signing_key field, and takes an optional char* to set the 
 * newly allocated field to. If NULL is passed, only allocation occurs.
 */
void git_clone_opts_set_template(git_clone_opts* opts, const char* tmpl);

/**
 * Frees git_clone_opts struct.
 */
void git_clone_opts_free(git_clone_opts* opts);


#endif
