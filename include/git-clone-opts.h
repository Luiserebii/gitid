#ifndef GIT_CLONE_OPTS_H
#define GIT_CLONE_OPTS_H

#define GIT_CLONE_OPTS_BUFFER_MAX 1000

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
 *
 * Please note that these options are according to the git 2.7.x API.
 */
// clang-format off
#define GIT_CLONE_OPTS_VERBOSE              (1 << 0)
#define GIT_CLONE_OPTS_QUIET                (1 << 1)
#define GIT_CLONE_OPTS_PROGRESS             (1 << 2)
#define GIT_CLONE_OPTS_NO_CHECKOUT          (1 << 3)
#define GIT_CLONE_OPTS_BARE                 (1 << 4)
#define GIT_CLONE_OPTS_MIRROR               (1 << 5)
#define GIT_CLONE_OPTS_LOCAL                (1 << 6)
#define GIT_CLONE_OPTS_NO_HARDLINKS         (1 << 7)
#define GIT_CLONE_OPTS_SHARED               (1 << 8)
#define GIT_CLONE_OPTS_RECURSIVE            (1 << 9)
#define GIT_CLONE_OPTS_RECURSE_SUBMODULES   (1 << 10)
#define GIT_CLONE_OPTS_DISSOCIATE           (1 << 11)
#define GIT_CLONE_OPTS_SINGLE_BRANCH        (1 << 12)
// clang-format on

typedef struct {
    char* repo;
    int flags;
    char* template;
    char* reference;
    char* origin;
    char* branch;
    char* upload_pack;
    char* depth;
    char* seperate_git_dir;
    char* config;
} git_clone_opts;

/**
 * Initializes a git_clone_opts struct.
 */
void git_clone_opts_init(git_clone_opts* opts);

/**
 * Initializes a git_clone_opts struct, with an argument to protect an invariant.
 * (git clone requires a repo)
 */
void git_clone_opts_safe_init(git_clone_opts* opts, const char* rp);

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
declare_struct_set_string(git_clone_opts, repo, opts, rp);
declare_struct_set_string(git_clone_opts, template, opts, tmpl);
declare_struct_set_string(git_clone_opts, reference, opts, ref);
declare_struct_set_string(git_clone_opts, origin, opts, orig);
declare_struct_set_string(git_clone_opts, branch, opts, brnch);
declare_struct_set_string(git_clone_opts, upload_pack, opts, up_pck);
declare_struct_set_string(git_clone_opts, depth, opts, dpth);
declare_struct_set_string(git_clone_opts, seperate_git_dir, opts, sep_gd);
declare_struct_set_string(git_clone_opts, config, opts, conf);

/**
 * Deinitializes git_clone_opts struct.
 */
void git_clone_opts_deinit(git_clone_opts* opts);

#endif
