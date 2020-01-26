#ifndef GIT_CLONE_OPTS_H
#define GIT_CLONE_OPTS_H

#define GIT_CLONE_OPTS_MAXSTRING 1000

#include "../include/struct.h"

/**
 * Type struct git_clone_opts based on the following options:
 *
 * git clone [<options>] [--] <repo> [<dir>]
 *
 * 
 * -v, --verbose         be more verbose
 * -q, --quiet           be more quiet
 * --progress            force progress reporting
 * -n, --no-checkout     don't create a checkout
 * --bare                create a bare repository
 * --mirror              create a mirror repository (implies bare)
 * -l, --local           to clone from a local repository
 * --no-hardlinks        don't use local hardlinks, always copy
 * -s, --shared          setup as shared repository
 * --recursive           initialize submodules in the clone
 * --recurse-submodules  initialize submodules in the clone
 * --template <template-directory>
 * directory from which templates will be used
 * --reference <repo>    reference repository
 * --dissociate          use --reference only while cloning
 * -o, --origin <name>   use <name> instead of 'origin' to track upstream
 * -b, --branch <branch>
 * checkout <branch> instead of the remote's HEAD
 * -u, --upload-pack <path>
 * path to git-upload-pack on the remote
 * --depth <depth>       create a shallow clone of that depth
 * --single-branch       clone only one branch, HEAD or --branch
 * --separate-git-dir <gitdir>
 * separate git dir from working tree
 * -c, --config <key=value>
 * set config inside the new repository
 */
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
 * MACRO use: Declares the following functions:
 *
 * void git_clone_opts_set_template(git_clone_opts* opts, const char* tmpl);
 * void git_clone_opts_set_reference(git_clone_opts* opts, const char* ref);
 * void git_clone_opts_set_origin(git_clone_opts* opts, const char* orig);
 * void git_clone_opts_set_branch(git_clone_opts* opts, const char* brnch);
 * void git_clone_opts_set_upload_pack(git_clone_opts* opts, const char* up_pck);
 * void git_clone_opts_set_depth(git_clone_opts* opts, const char* dpth);
 * void git_clone_opts_set_seperate_git_dir(git_clone_opts* opts, const char* sep_gd);
 * void git_clone_opts_set_config(git_clone_opts* opts, const char* conf);
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
