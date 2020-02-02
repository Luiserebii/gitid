#ifndef CLI_H
#define CLI_H

#include "../lib/argtable3/argtable3.h"

#define PRG_NAME "gitid"
#define PRG_VERSION "0.1.0-alpha"

#define clean(m_argtable, c_argtable, exitcode)                            \
    arg_freetable(m_argtable, sizeof(m_argtable) / sizeof(m_argtable[0])); \
    arg_freetable(c_argtable, sizeof(c_argtable) / sizeof(c_argtable[0])); \
    return exitcode;

typedef enum { MODE_MAIN, MODE_CLONE } CLI_MODE;

/**
 * Processes the parsed main_argtable arg_xxx structs, containing most of the control flow logic.
 */
int process_main(void** argtable, struct arg_lit* version, struct arg_lit* about, struct arg_lit* list,
                 struct arg_str* new, struct arg_str* update, struct arg_str* delete, struct arg_str* shift,
                 struct arg_lit* current, struct arg_lit* global, struct arg_lit* local, struct arg_str* user,
                 struct arg_str* email, struct arg_str* sigkey, struct arg_end* end);
/**
 * Processes the parsed clone_argtable arg_xxx structs, containing most of the control flow logic.
 */
int process_clone(void** argtable, struct arg_rex* clone, struct arg_str* repo, struct arg_str* clone_shift,
                  struct arg_end* end);
/**
 * Writes the main_argtable glossary to the stream passed.
 */
void write_glossary(FILE* stream, void** argtable);

/**
 * Uses argtable arg_xxx structs to determine and return current mode of program.
 */
CLI_MODE identifyMode(struct arg_rex* clone);

#endif
