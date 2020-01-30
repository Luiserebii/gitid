#ifndef GITID_H
#define GITID_H

#include "git-user.h"
#include "gitid-id.h"
#include "vector-gitid-id.h"

#define GITID_SYSTEM_DATA_FILE "./data/gitids"

//Lowest level functions
/**
 * Takes a pointer to an intialized vector_gitid_id and pushes all gitids 
 * found on the system onto it. The system's gitids are represented by a file,
 * which is held as a macro in this header file.
 *
 * In order to allow for a "testable interface", the innermost logic of the
 * below two functions operating on the system data file have been refactored
 * into one that takes a filename, which allows us to swap something in for
 * the macro. The only small risk is perhaps making the interface look
 * slightly more complex, but I don't think it's so bad.
 *
 * As a final note, note that this function will segfault if a file is not found,
 * please ensure that you check for the existence of the file beforehand.
 */
#define gitid_get_system_gitid_ids(v_gitid_id) gitid_get_system_gitid_ids_file(v_gitid_id, GITID_SYSTEM_DATA_FILE)
void gitid_get_system_gitid_ids_file(vector_gitid_id* v, const char* fn);

/**
 * Takes a pointer to an intialized vector_gitid_id and writes all gitids 
 * from the vector onto the system's. This will cause an overwrite, not append.
 */
#define gitid_set_system_gitid_ids(v_gitid_id) gitid_set_system_gitid_ids_file(v_gitid_id, GITID_SYSTEM_DATA_FILE)
void gitid_set_system_gitid_ids_file(vector_gitid_id* v, const char* fn);

//Slightly higher level, these call the above two get/set functions; get to obtain system ids to process, and set to save to the system once more
//A minor note about these functions: they similarly will segfault if a file is not found,
//please create one ahead of time.
/**
 * Adds a new gitid represented by the pointer passed onto the system.
 * This can be seen as an "append" operation. Should break if an already existing
 * gitid by the name specified is found (we want to prevent duplicates).
 */
void gitid_new_system_gitid_id(gitid_id* git_id);

/**
 * Updates a system gitid of the ID id_name and replaces it with the details
 * found in the gitid_id pointer passed. Should break if the gitid is not found
 * on the system by printing an error and exiting.
 */
void gitid_update_system_gitid_id(gitid_id* id, char* id_name);

/**
 * Deletes a system gitid of the ID id_name. Should break if the gitid is not found
 * on the system by printing an error and exiting.
 */
void gitid_delete_system_gitid_id(char* id_name);

//Functions dealing with the setting of identities to git b
/**
 * Sets either the local/global git users on the git application.
 * Since these are so trivial to implement, these are really better as macros,
 * if they should be used at all
 */
#define gitid_shift_gitid_id_global(id) git_set_user_global(id->user)
#define gitid_shift_gitid_id_local(id) git_set_user_local(id->user)

#endif
