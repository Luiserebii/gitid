#ifndef GITID_H
#define GITID_H

#define GITID_SYSTEM_DATA_FILE "./data/gitids"

//Lowest level functions
/**
 * Takes a pointer to an intialized vector_gitid_id and pushes all gitids 
 * found on the system onto it. The system's gitids are represented by a file,
 * which is held as a macro in this header file.
 */
void gitid_get_system_gitid_ids(vector_gitid_id* v);

/**
 * Takes a pointer to an intialized vector_gitid_id and writes all gitids 
 * from the vector onto the system's. This will cause an overwrite, not append.
 */
void gitid_set_system_gitid_ids(vector_gitid_id* v);

//Slightly higher level, these call the above two get/set functions; get to obtain system ids to process, and set to save to the system once more
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
 * Since these are so minor to implement, these are really better as macros
 */
void gitid_shift_gitid_id_global(gitid_id* id);

void gitid_shift_gitid_id_local(gitid_id* id);

#endif
