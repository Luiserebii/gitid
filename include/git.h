#ifndef GIT_H
#define GIT_H

#include "../include/git-clone-opts.h"
#include "../include/git-user.h"

#define GIT_CMD_MAXSTRING (GIT_USER_BUFFER_MAX * 3) + 100
#define GIT_CLONE_CMD_MAXSTRING 10000

/**
 * Obtains the global git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_global(git_user* user);

/**
 * Obtains the local git_user config and saves it into the 
 * git_user struct passed.
 */
void git_get_user_local(git_user* user);

/**
 * Sets the global user via git
 */
void git_set_user_global(git_user* user);

/**
 * Sets the local user for a repository (therefore local)
 */
void git_set_user_local(git_user* user);

/**
 * Sets the local user for a repository, taking a prefix to use with the command.
 */
void git_set_user_local_prefix(git_user* user, char* prefix);

/**
 * Performs a git clone, using the options struct passed.
 */
void git_clone(git_clone_opts* opts);

#endif
