#include "../../include/git.h"
#include "../../include/git-user.h"
#include "../../include/gitid-id.h"

#include <stdio.h>

int main() {

    git_user* user = git_user_init();
    git_get_user_global(user);

    printf("User obtained:\n name: %s | email: %s | signingKey: %s\n", user->name, user->email, user->signing_key);

    git_user_free(user);

    gitid_id* id = gitid_id_init();
    gitid_id_set_id_name(id, "Luiserebii");
    gitid_id_set_name(id, "Luiserebii");
    gitid_id_set_email(id, "luis@serebii.io");
    gitid_id_set_signing_key(id, "SIGNING_KEY");

    gitid_id_write(id, stdout);
    gitid_id_min_write(id, stdout);
    //Attempt read
    gitid_id_min_read(id, stdin);
    //Print read
    gitid_id_min_write(id, stdout);
}

