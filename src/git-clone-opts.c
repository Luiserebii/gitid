#include "../include/git-clone-opts.h"
#include "../include/struct.h"
#include "../include/util.h"

#include <stdio.h>
#include <string.h>

git_clone_opts* git_clone_opts_init() {
    //Allocate git_clone_opts
    git_clone_opts* opts = safemalloc(sizeof(git_clone_opts));

    //Initialize fields
    opts->verbose = opts->quiet = opts->progress = opts->no_checkout = opts->bare = opts->mirror = opts->local =
        opts->no_hardlinks = opts->shared = opts->recursive = opts->recurse_submodules = opts->dissociate =
            opts->single_branch = 0;
    opts->repo = opts->template = opts->reference = opts->origin = opts->branch = opts->upload_pack = opts->depth =
        opts->seperate_git_dir = opts->config = NULL;

    return opts;
}

git_clone_opts* git_clone_opts_safe_init(const char* rp) {
    //Throw in the event that param is null
    if(!rp) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }
    
    //Allocate git_clone_opts
    git_clone_opts* opts = safemalloc(sizeof(git_clone_opts));

    //Set repo in parameter
    git_clone_opts_set_repo(opts, rp);

    //Initialize rest of fields
    opts->verbose = opts->quiet = opts->progress = opts->no_checkout = opts->bare = opts->mirror = opts->local =
        opts->no_hardlinks = opts->shared = opts->recursive = opts->recurse_submodules = opts->dissociate =
            opts->single_branch = 0;
    opts->template = opts->reference = opts->origin = opts->branch = opts->upload_pack = opts->depth =
        opts->seperate_git_dir = opts->config = NULL;

    return opts;
}

/**
 * MACRO use: Define struct functions for each char* member
 */
define_struct_set_string(git_clone_opts, repo, opts, rp);
define_struct_set_string(git_clone_opts, template, opts, tmpl);
define_struct_set_string(git_clone_opts, reference, opts, ref);
define_struct_set_string(git_clone_opts, origin, opts, orig);
define_struct_set_string(git_clone_opts, branch, opts, brnch);
define_struct_set_string(git_clone_opts, upload_pack, opts, up_pck);
define_struct_set_string(git_clone_opts, depth, opts, dpth);
define_struct_set_string(git_clone_opts, seperate_git_dir, opts, sep_gd);
define_struct_set_string(git_clone_opts, config, opts, conf);

void git_clone_opts_free(git_clone_opts* opts) {
    //Free members
    free(opts->repo);
    free(opts->template), free(opts->reference), free(opts->origin), free(opts->branch), free(opts->upload_pack),
        free(opts->depth), free(opts->seperate_git_dir), free(opts->config);

    //Free struct
    free(opts);
}
