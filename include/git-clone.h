#ifndef GIT_CLONE_H
#define GIT_CLONE_H

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

#endif
