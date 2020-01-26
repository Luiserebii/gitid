#ifndef GIT_H
#define GIT_H

typedef struct {
    char* name;
    char* email;
    char* signing_key;
} git_user;

git_user* git_user_init();
void git_user_set_signing_key(git_user* user, const char* sk);
void git_get_user_global(git_user* user);
void git_get_user_local(git_user* user);
void git_user_free(git_user* user);

#endif
