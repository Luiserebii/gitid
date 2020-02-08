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
    safestrcpy(escapebuffer, user->name, GIT_USER_BUFFER_MAX);
    escapesh(escapebuffer);
    safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);

    safestrcat(cmd, " && git config --global user.email ", GIT_CMD_MAXSTRING);
    safestrcpy(escapebuffer, user->email, GIT_USER_BUFFER_MAX);
    escapesh(escapebuffer);
    safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);

    //Logic with setting signingkey will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existent
    safestrcat(cmd, " && git config --global user.signingkey ", GIT_CMD_MAXSTRING);
    if(user->signing_key) {
        safestrcpy(escapebuffer, user->signing_key, GIT_USER_BUFFER_MAX);
        escapesh(escapebuffer);
        safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);
    } else {
        safestrcat(cmd, "\"\"", GIT_CMD_MAXSTRING);
    }

    //Return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}

int git_set_user_local(git_user* user) {
    char escapebuffer[GIT_USER_BUFFER_MAX];
    char cmd[GIT_CMD_MAXSTRING] = "git config --local user.name ";
    //Copy to buffer, escape, and finally, concatenate the result
    safestrcpy(escapebuffer, user->name, GIT_USER_BUFFER_MAX);
    escapesh(escapebuffer);
    safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);

    safestrcat(cmd, " && git config --local user.email ", GIT_CMD_MAXSTRING);
    safestrcpy(escapebuffer, user->email, GIT_USER_BUFFER_MAX);
    escapesh(escapebuffer);
    safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);

    //Logic with setting signingkey will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existent
    safestrcat(cmd, " && git config --local user.signingkey ", GIT_CMD_MAXSTRING);
    if(user->signing_key) {
        safestrcpy(escapebuffer, user->signing_key, GIT_USER_BUFFER_MAX);
        escapesh(escapebuffer);
        safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);
    } else {
        safestrcat(cmd, "\"\"", GIT_CMD_MAXSTRING);
    }

    //Return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}

int git_set_user_local_prefix(git_user* user, char* prefix) {
    char escapebuffer[GIT_USER_BUFFER_MAX];
    char cmd[GIT_CMD_MAXSTRING];

    safestrcpy(cmd, prefix, GIT_USER_BUFFER_MAX);

    safestrcat(cmd, " && git config --local user.name ", GIT_CMD_MAXSTRING);
    safestrcpy(escapebuffer, user->name, GIT_USER_BUFFER_MAX);
    escapesh(escapebuffer);
    safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);

    safestrcat(cmd, " && git config --local user.email ", GIT_CMD_MAXSTRING);
    safestrcpy(escapebuffer, user->email, GIT_USER_BUFFER_MAX);
    escapesh(escapebuffer);
    safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);

    //Logic with setting signingkey will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existent
    safestrcat(cmd, " && git config --local user.signingkey ", GIT_CMD_MAXSTRING);
    if(user->signing_key) {
        safestrcpy(escapebuffer, user->signing_key, GIT_USER_BUFFER_MAX);
        escapesh(escapebuffer);
        safestrcat(cmd, escapebuffer, GIT_CMD_MAXSTRING);
    } else {
        safestrcat(cmd, "\"\"", GIT_CMD_MAXSTRING);
    }

    //Return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}

int git_clone(git_clone_opts* opts) {
    char cmd[GIT_CLONE_CMD_MAXSTRING] = "git clone";

    //Check all of the possible options for git clone
    if(opts->repo) {
        safestrcat(cmd, " ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->repo, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_VERBOSE) {
        safestrcat(cmd, " -v", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_QUIET) {
        safestrcat(cmd, " -q", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_PROGRESS) {
        safestrcat(cmd, " --progress", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_NO_CHECKOUT) {
        safestrcat(cmd, " --no-checkout", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_BARE) {
        safestrcat(cmd, " --bare", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_MIRROR) {
        safestrcat(cmd, " --mirror", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_LOCAL) {
        safestrcat(cmd, " -l", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_NO_HARDLINKS) {
        safestrcat(cmd, " --no-hardlinks", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_SHARED) {
        safestrcat(cmd, " -s", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_RECURSIVE) {
        safestrcat(cmd, " --recursive", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_RECURSE_SUBMODULES) {
        safestrcat(cmd, " --recurse-submodules", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->template) {
        safestrcat(cmd, " --template ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->template, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->reference) {
        safestrcat(cmd, " --reference ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->reference, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_DISSOCIATE) {
        safestrcat(cmd, "--dissociate", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->origin) {
        safestrcat(cmd, " -o ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->origin, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->branch) {
        safestrcat(cmd, " -b ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->branch, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->upload_pack) {
        safestrcat(cmd, " -u ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->upload_pack, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->depth) {
        safestrcat(cmd, " --depth ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->depth, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->flags & GIT_CLONE_OPTS_SINGLE_BRANCH) {
        safestrcat(cmd, " --single-branch", GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->seperate_git_dir) {
        safestrcat(cmd, " --seperate-git-dir ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->seperate_git_dir, GIT_CLONE_CMD_MAXSTRING);
    }
    if(opts->config) {
        safestrcat(cmd, " -c ", GIT_CLONE_CMD_MAXSTRING);
        safestrcat(cmd, opts->config, GIT_CLONE_CMD_MAXSTRING);
    }

    //Finally, execute constructed command, and return success based on exit code
    return minsystem(cmd) ? 0 : 1;
}
