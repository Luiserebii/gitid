#include "../include/git-clone.h"
#include "../include/util.h"
#include "../include/struct.h"

#include <string.h>

git_clone_opts* git_clone_opts_init() {
    //Allocate git_clone_opts
    git_clone_opts* opts = safemalloc(sizeof(git_clone_opts));

    //Allocate for expected fields
    opts->repo = safemalloc(GIT_CLONE_OPTS_MAXSTRING);

    //Initialize rest of fields
    opts->verbose = opts->quiet = opts->progress = opts->no_checkout
        = opts->bare = opts->mirror = opts->local = opts->no_hardlinks 
        = opts->shared = opts->recursive = opts->recurse_submodules
        = opts->dissociate = opts->single_branch = 0;
    opts->template = opts->reference = opts->origin = opts->branch
        = opts->upload_pack = opts->depth = opts->seperate_git_dir
        = opts->config = NULL;

    return opts;
}
/*
void git_clone_opts_set_template(git_clone_opts* opts, const char* tmpl) {
    free(opts->template);
    opts->template = safemalloc(strlen(tmpl) + 1);
    if(tmpl) {
        strcpy(opts->template, tmpl);
    }
}*/

define_struct_set_string(git_clone_opts, template, opts, tmpl)

void git_clone_opts_free(git_clone_opts* opts) {
    //Free members
    free(opts->repo);
    free(opts->template), free(opts->reference), free(opts->origin), free(opts->branch),
        free(opts->upload_pack), free(opts->depth), free(opts->seperate_git_dir),
        free(opts->config);

    //Free struct
    free(opts);
}

