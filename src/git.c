#include "../include/git.h"
#include "../include/git-clone.h"
#include "../include/util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GIT_USER_MAXSTRING 1000
#define GIT_CMD_MAXSTRING (GIT_USER_MAXSTRING * 3) + 100
#define GIT_CLONE_CMD_MAXSTRING 10000

/**
 * Allocates space for a new git_user struct.
 */
git_user* git_user_init() {
    //Allocate for struct
    git_user* user = safemalloc(sizeof(git_user));

    //Allocate each string
    user->name = safemalloc(GIT_USER_MAXSTRING);
    user->email = safemalloc(GIT_USER_MAXSTRING);
    
    //Optional, so set to NULL by default
    user->signing_key = NULL;
}

/**
 * If new, allocate the signing_key field, and takes an optional char* to set the 
 * newly allocated field to. If NULL is passed, only allocation occurs.
 */
void git_user_set_signing_key(git_user* user, const char* sk) {
    //Free if not NULL, before allocating
    if(user->signing_key) {
        free(user->signing_key);
    }
    user->signing_key = safemalloc(GIT_USER_MAXSTRING);
    if(sk) {
        strcpy(user->signing_key, sk);
    }
}

/**
 * Obtains the global git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_global(git_user* user) {
    runcmd("git config --global user.name", GIT_USER_MAXSTRING, user->name);
    runcmd("git config --global user.email", GIT_USER_MAXSTRING, user->email);
    runcmd("git config --global user.signingkey", GIT_USER_MAXSTRING, user->signing_key);

    //Trim all inputs
    trimNewline(user->name), trimNewline(user->email), trimNewline(user->signing_key);
}

/**
 * Obtains the local git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_local(git_user* user) {
    runcmd("git config --local user.name", GIT_USER_MAXSTRING, user->name);
    runcmd("git config --local user.email", GIT_USER_MAXSTRING, user->email);
    runcmd("git config --local user.signingkey", GIT_USER_MAXSTRING, user->signing_key);
    
    //Trim all inputs
    trimNewline(user->name), trimNewline(user->email), trimNewline(user->signing_key);
}

/**
 * Sets the global user via git
 */
void git_set_user_global(git_user* user) {
    char cmd[GIT_CMD_MAXSTRING] = "git config --global user.name ";
    strcat(cmd, user->name);
    strcat(cmd, " && git config --global user.email ");
    strcat(cmd, user->email);
    if(user->signing_key) {
        strcat(cmd, " && git config --global user.signingkey ");
        strcat(cmd, user->signing_key);
    }
    printf("%s\n", cmd);
    //TODO: Figure out how to handle non-zero exit codes
    minsystem(cmd);
}

/**
 * Sets the local user for a repository (therefore local)
 */
void git_set_user_local(git_user* user) {
    char cmd[GIT_CMD_MAXSTRING] = "git config --local user.name ";
    strcat(cmd, user->name);
    strcat(cmd, " && git config --local user.email ");
    strcat(cmd, user->email);
    if(user->signing_key) {
        strcat(cmd, " && git config --local user.signingkey ");
        strcat(cmd, user->signing_key);
    }

    //TODO: Figure out how to handle non-zero exit codes
    minsystem(cmd);
}

void git_clone(git_clone_opts* opts) {
    char cmd[GIT_CLONE_CMD_MAXSTRING] = "git clone";

    //Check all of the possible options for git clone
    if(opts->repo) {
        strcat(cmd, " ");
        strcat(cmd, opts->repo);
    }
    if(opts->verbose) {
        strcat(cmd, " -v");
    }
    if(opts->quiet) {
        strcat(cmd, " -q");
    }
    if(opts->progress) {
        strcat(cmd, " --progress");
    }
    if(opts->no_checkout) {
        strcat(cmd, " --no-checkout");
    }
    if(opts->bare) {
        strcat(cmd, " --bare");
    }
    if(opts->mirror) {
        strcat(cmd, " --mirror");
    }
    if(opts->local) {
        strcat(cmd, " -l");
    }
    if(opts->no_hardlinks) {
        strcat(cmd, " --no-hardlinks");
    }
    if(opts->shared) {
        strcat(cmd, " -s");
    }
    if(opts->recursive) {
        strcat(cmd, " --recursive");
    }
    if(opts->recurse_submodules) {
        strcat(cmd, " --recurse-submodules");
    }
    if(opts->template) {
        strcat(cmd, " --template ");
        strcat(cmd, opts->template);
    }
    if(opts->reference) {
        strcat(cmd, " --reference ");
        strcat(cmd, opts->reference);
    }
    if(opts->dissociate) {
        strcat(cmd, "--dissociate");
    }
    if(opts->origin) {
        strcat(cmd, " -o ");
        strcat(cmd, opts->origin);
    }
    if(opts->branch) {
        strcat(cmd, " -b ");
        strcat(cmd, opts->branch);
    }
    if(opts->upload_pack) {
        strcat(cmd, " -u ");
        strcat(cmd, opts->upload_pack);
    }
    if(opts->depth) {
        strcat(cmd, " --depth ");
        strcat(cmd, opts->depth);
    }
    if(opts->single_branch) {
        strcat(cmd, " --single-branch");
    }
    if(opts->seperate_git_dir) {
        strcat(cmd, " --seperate-git-dir ");
        strcat(cmd, opts->seperate_git_dir);
    }
    if(opts->config) {
        strcat(cmd, " -c ");
        strcat(cmd, opts->config);
    }

    //Finally, execute constructed command
    minsystem(cmd);
}

/**
 * Frees git_user struct.
 */
void git_user_free(git_user* user) {
    //Free members
    free(user->name);
    free(user->email);
    if(user->signing_key) {
        free(user->signing_key);
    }

    //Free struct
    free(user);
}

int main() {

    git_user* user = git_user_init();
    git_get_user_global(user);

    printf("User obtained:\n name: %s | email: %s | signingKey: %s\n", user->name, user->email, user->signing_key);

    git_user_free(user);

}
