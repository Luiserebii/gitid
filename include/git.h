#ifndef GIT_H
#define GIT_H

typedef struct {
    char* name;
    char* email;
    char* signing_key;
} git_user;

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

git_user* git_user_init();
void git_get_user_global(git_user* user);
void git_get_user_local(git_user* user);
void git_user_free(git_user* user);

#endif
