#include "../include/git.h"
#include "../include/git-clone-opts.h"
#include "../include/git-user.h"
#include "../include/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void git_get_user_global(git_user* user) {
    //String buffer to hold char results from commands temporarily, so they can be
    //dynamically allocated and fit to size afterwards
    char buffer[GIT_USER_BUFFER_MAX];

    runcmd("git config --global user.name", GIT_USER_BUFFER_MAX, buffer);
    git_user_set_name(user, buffer);
    runcmd("git config --global user.email", GIT_USER_BUFFER_MAX, buffer);
    git_user_set_email(user, buffer);
    runcmd("git config --global user.signingkey", GIT_USER_BUFFER_MAX, buffer);
    //Check if we obtained something
    if(*buffer) {
        git_user_set_signing_key(user, buffer);
        trimNewline(user->signing_key);
    }

    //Trim all inputs
    trimNewline(user->name), trimNewline(user->email);
}

void git_get_user_local(git_user* user) {
    //String buffer to hold char results from commands temporarily, so they can be
    //dynamically allocated and fit to size afterwards
    char buffer[GIT_USER_BUFFER_MAX];

    runcmd("git config --local user.name", GIT_USER_BUFFER_MAX, buffer);
    git_user_set_name(user, buffer);
    runcmd("git config --local user.email", GIT_USER_BUFFER_MAX, buffer);
    git_user_set_email(user, buffer);
    runcmd("git config --local user.signingkey", GIT_USER_BUFFER_MAX, buffer);
    //Check if we obtained something
    if(*buffer) {
        git_user_set_signing_key(user, buffer);
        trimNewline(user->signing_key);
    }

    //Trim all inputs
    trimNewline(user->name), trimNewline(user->email);
}

int git_set_user_global(git_user* user) {
    char escapebuffer[GIT_USER_BUFFER_MAX];
    char cmd[GIT_CMD_MAXSTRING] = "git config --global user.name ";
    //Copy to buffer, escape, and finally, concatenate the result
    strcpy(escapebuffer, user->name), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    strcat(cmd, " && git config --global user.email ");
    strcpy(escapebuffer, user->email), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    //Logic with setting signingkey will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existant
    strcat(cmd, " && git config --global user.signingkey ");
    if(user->signing_key) {
        strcpy(escapebuffer, user->signing_key), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    } else {
        strcat(cmd, "\"\"");
    }

    //Return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}

int git_set_user_local(git_user* user) {
    char escapebuffer[GIT_USER_BUFFER_MAX];
    char cmd[GIT_CMD_MAXSTRING] = "git config --local user.name ";
    strcpy(escapebuffer, user->name), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    strcat(cmd, " && git config --local user.email ");
    strcpy(escapebuffer, user->email), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    strcat(cmd, " && git config --global user.signingkey ");
    if(user->signing_key) {
        strcpy(escapebuffer, user->signing_key), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    } else {
        strcat(cmd, "\"\"");
    }

    //Return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}

int git_set_user_local_prefix(git_user* user, char* prefix) {
    char escapebuffer[GIT_USER_BUFFER_MAX];
    char cmd[GIT_CMD_MAXSTRING];
    strcpy(cmd, prefix);
    strcat(cmd, " && git config --local user.name ");
    strcpy(escapebuffer, user->name), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    strcat(cmd, " && git config --local user.email ");
    strcpy(escapebuffer, user->email), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    strcat(cmd, " && git config --global user.signingkey ");
    if(user->signing_key) {
        strcpy(escapebuffer, user->signing_key), escapesh(escapebuffer), strcat(cmd, escapebuffer);
    } else {
        strcat(cmd, "\"\"");
    }

    //Return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}

int git_clone(git_clone_opts* opts) {
    char cmd[GIT_CLONE_CMD_MAXSTRING] = "git clone";

    //Check all of the possible options for git clone
    if(opts->repo) {
        strcat(cmd, " ");
        strcat(cmd, opts->repo);
    }
    if(opts->flags & GIT_CLONE_OPTS_VERBOSE) {
        strcat(cmd, " -v");
    }
    if(opts->flags & GIT_CLONE_OPTS_QUIET) {
        strcat(cmd, " -q");
    }
    if(opts->flags & GIT_CLONE_OPTS_PROGRESS) {
        strcat(cmd, " --progress");
    }
    if(opts->flags & GIT_CLONE_OPTS_NO_CHECKOUT) {
        strcat(cmd, " --no-checkout");
    }
    if(opts->flags & GIT_CLONE_OPTS_BARE) {
        strcat(cmd, " --bare");
    }
    if(opts->flags & GIT_CLONE_OPTS_MIRROR) {
        strcat(cmd, " --mirror");
    }
    if(opts->flags & GIT_CLONE_OPTS_LOCAL) {
        strcat(cmd, " -l");
    }
    if(opts->flags & GIT_CLONE_OPTS_NO_HARDLINKS) {
        strcat(cmd, " --no-hardlinks");
    }
    if(opts->flags & GIT_CLONE_OPTS_SHARED) {
        strcat(cmd, " -s");
    }
    if(opts->flags & GIT_CLONE_OPTS_RECURSIVE) {
        strcat(cmd, " --recursive");
    }
    if(opts->flags & GIT_CLONE_OPTS_RECURSE_SUBMODULES) {
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
    if(opts->flags & GIT_CLONE_OPTS_DISSOCIATE) {
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
    if(opts->flags & GIT_CLONE_OPTS_SINGLE_BRANCH) {
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

    //Finally, execute constructed command, and return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}
