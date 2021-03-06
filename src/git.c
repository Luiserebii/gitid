#include "../include/git.h"
#include "../include/git-clone-opts.h"
#include "../include/git-user.h"
#include "../include/util.h"

#include <cstl/cstring.h>
#include <cstl/string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void git_get_user_global(git_user* user) {
    //String buffer to hold char results from commands temporarily, so they can be
    //dynamically allocated and fit to size afterwards
    string buf;
    string_init_capacity(&buf, GIT_USER_BUFFER_MIN);

    //Note the -1, for trimming off the '\n'
    runcmd("git config --global user.name", &buf);
    string_assign(&user->name, string_begin(&buf), string_end(&buf) - 1);
    string_clear(&buf);

    runcmd("git config --global user.email", &buf);
    string_assign(&user->email, string_begin(&buf), string_end(&buf) - 1);
    string_clear(&buf);

    runcmd("git config --global user.signingkey", &buf);
    //Check if we obtained something
    if(string_size(&buf)) {
        string_assign(&user->signing_key, string_begin(&buf), string_end(&buf) - 1);
    }

    string_deinit(&buf);
}

void git_get_user_local(git_user* user) {
    string buf;
    string_init_capacity(&buf, GIT_USER_BUFFER_MIN);

    runcmd("git config --local user.name", &buf);
    string_assign(&user->name, string_begin(&buf), string_end(&buf) - 1);
    string_clear(&buf);

    runcmd("git config --local user.email", &buf);
    string_assign(&user->email, string_begin(&buf), string_end(&buf) - 1);
    string_clear(&buf);

    runcmd("git config --local user.signingkey", &buf);
    //Check if we obtained something
    if(string_size(&buf)) {
        string_assign(&user->signing_key, string_begin(&buf), string_end(&buf) - 1);
    }

    string_deinit(&buf);
}

int git_set_user_global(const git_user* user) {
    string escbuf, cmd;

    string_init_capacity(&escbuf, GIT_USER_BUFFER_MIN);
    string_init_cstr(&cmd, "git config --global user.name ");

    //Copy to buffer, escape, and finally, concatenate the result
    string_asn(&escbuf, &user->name);
    escapesh(&escbuf);
    string_cat(&cmd, &escbuf);
    string_clear(&escbuf);

    string_cat_cstr(&cmd, " && git config --global user.email ");
    string_asn(&escbuf, &user->email);
    escapesh(&escbuf);
    string_cat(&cmd, &escbuf);
    string_clear(&escbuf);

    //Logic with setting signing key will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existent
    string_cat_cstr(&cmd, " && git config --global user.signingkey ");
    if(string_size(&user->signing_key)) {
        string_asn(&escbuf, &user->signing_key);
        escapesh(&escbuf);
        string_cat(&cmd, &escbuf);
    } else {
        char blank[] = "\"\"";
        string_insert_range(&cmd, string_end(&cmd), blank, blank + 2);
    }

    int suc = minsystem(string_cstr(&cmd));

    string_deinit(&escbuf);
    string_deinit(&cmd);

    //Return success based on exit code
    return suc ? 0 : 1;
}

int git_set_user_local(const git_user* user) {
    string escbuf, cmd;

    string_init_capacity(&escbuf, GIT_USER_BUFFER_MIN);
    string_init_cstr(&cmd, "git config --local user.name ");

    //Copy to buffer, escape, and finally, concatenate the result
    string_asn(&escbuf, &user->name);
    escapesh(&escbuf);
    string_cat(&cmd, &escbuf);
    string_clear(&escbuf);

    string_cat_cstr(&cmd, " && git config --local user.email ");
    string_asn(&escbuf, &user->email);
    escapesh(&escbuf);
    string_cat(&cmd, &escbuf);
    string_clear(&escbuf);

    //Logic with setting signing key will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existent
    string_cat_cstr(&cmd, " && git config --local user.signingkey ");
    if(string_size(&user->signing_key)) {
        string_asn(&escbuf, &user->signing_key);
        escapesh(&escbuf);
        string_cat(&cmd, &escbuf);
    } else {
        char blank[] = "\"\"";
        string_insert_range(&cmd, string_end(&cmd), blank, blank + 2);
    }

    int suc = minsystem(string_cstr(&cmd));

    string_deinit(&escbuf);
    string_deinit(&cmd);

    //Return success based on exit code
    return suc ? 0 : 1;
}

int git_set_user_local_prefix(const git_user* user, const char* prefix) {
    string escbuf, cmd;

    string_init_capacity(&escbuf, GIT_USER_BUFFER_MIN);
    string_init_cstr(&cmd, prefix);

    string_cat_cstr(&cmd, " && git config --local user.name ");
    string_asn(&escbuf, &user->name);
    escapesh(&escbuf);
    string_cat(&cmd, &escbuf);
    string_clear(&escbuf);

    string_cat_cstr(&cmd, " && git config --local user.email ");
    string_asn(&escbuf, &user->email);
    escapesh(&escbuf);
    string_cat(&cmd, &escbuf);
    string_clear(&escbuf);

    //Logic with setting signing key will depend on whether it exists or not, but will
    //happen regardless so as to clear if non-existent
    string_cat_cstr(&cmd, " && git config --local user.signingkey ");
    if(string_size(&user->signing_key)) {
        string_asn(&escbuf, &user->signing_key);
        escapesh(&escbuf);
        string_cat(&cmd, &escbuf);
    } else {
        char blank[] = "\"\"";
        string_insert_range(&cmd, string_end(&cmd), blank, blank + 2);
    }

    int suc = minsystem(string_cstr(&cmd));

    string_deinit(&escbuf);
    string_deinit(&cmd);

    //Return success based on exit code
    return suc ? 0 : 1;
}

int git_clone(const git_clone_opts* opts) {
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
