#include "../../include/git.h"
#include "../../include/git-user.h"

#include <stdio.h>

int main() {

    git_user* user = git_user_init();
    git_get_user_global(user);

    printf("User obtained:\n name: %s | email: %s | signingKey: %s\n", user->name, user->email, user->signing_key);

    git_user_free(user);
}

