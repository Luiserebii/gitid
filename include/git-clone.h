#ifndef GIT_CLONE_H
#define GIT_CLONE_H

#define GIT_CLONE_OPTS_MAXSTRING 1000

#include "../include/struct.h"

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
 * void git_clone_opts_set_template(git_clone_opts* opts, const char* tmpl);
 */
declare_struct_set_string(git_clone_opts, template, opts, tmpl)
declare_struct_set_string(git_clone_opts, reference, opts, ref)
declare_struct_set_string(git_clone_opts, origin, opts, orig)
declare_struct_set_string(git_clone_opts, branch, opts, brnch)
declare_struct_set_string(git_clone_opts, upload_pack, opts, up_pck)
declare_struct_set_string(git_clone_opts, depth, opts, dpth)
declare_struct_set_string(git_clone_opts, seperate_git_dir, opts, sep_gd)
declare_struct_set_string(git_clone_opts, config, opts, conf)

/**
 * Frees git_clone_opts struct.
 */
void git_clone_opts_free(git_clone_opts* opts);


#endif
