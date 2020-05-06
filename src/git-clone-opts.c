#include "../include/git-clone-opts.h"
#include "../include/util.h"

#include <cstl/cstring.h>

#include <stdio.h>
#include <string.h>

void git_clone_opts_init(git_clone_opts* opts) {
    //Initialize fields
    opts->flags = 0;
    opts->repo = opts->template = opts->reference = opts->origin = opts->branch = opts->upload_pack = opts->depth =
        opts->seperate_git_dir = opts->config = NULL;
}

void git_clone_opts_safe_init(git_clone_opts* opts, const char* rp) {
    //Throw in the event that param is null
    if(!rp) {
        fprintf(stderr, "logic error: git_user_safe_init received a NULL argument\n");
        exit(1);
    }

    //Set repo in parameter
    cstring_asn(opts->repo, rp);

    //Initialize rest of fields
    opts->flags = 0;
    opts->template = opts->reference = opts->origin = opts->branch = opts->upload_pack = opts->depth =
        opts->seperate_git_dir = opts->config = NULL;
}

void git_clone_opts_deinit(git_clone_opts* opts) {
    //Free members
    free(opts->repo);
    cstring_destroy(opts->template), cstring_destroy(opts->reference), cstring_destroy(opts->origin),
        cstring_destroy(opts->branch), cstring_destroy(opts->upload_pack), cstring_destroy(opts->depth),
        cstring_destroy(opts->seperate_git_dir), cstring_destroy(opts->config);
}
