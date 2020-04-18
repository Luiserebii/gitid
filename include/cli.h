#ifndef CLI_H
#define CLI_H

#include "../lib/argtable3/argtable3.h"

#define PRG_NAME "gitid"
#define PRG_VERSION "0.3.0-alpha"
#define PRG_DESCRIPTION \
    "A command line tool allowing for easy shifting between git identities (username, email, and signing key)."

#define clean(m_argtable, c_argtable, exitcode)                            \
    arg_freetable(m_argtable, sizeof(m_argtable) / sizeof(m_argtable[0])); \
    arg_freetable(c_argtable, sizeof(c_argtable) / sizeof(c_argtable[0])); \
    return exitcode;

typedef enum { MODE_MAIN, MODE_CLONE } CLI_MODE;

/**
 * Processes the parsed main_argtable arg_xxx structs, containing most of the control flow logic.
 */
int process_main(void** argtable);

/**
 * Processes the parsed clone_argtable arg_xxx structs, containing most of the control flow logic.
 */
int process_clone(void);

/**
 * Writes the main_argtable glossary to the stream passed.
 */
void write_main_glossary(FILE* stream, void** argtable);

/**
 * Uses argtable arg_xxx structs to determine and return current mode of program.
 */
CLI_MODE identifyMode(struct arg_rex* clone);

/**
 * Function meant to run before all else; populates constants, particularly filepaths based on $HOME.
 */
void setup_constants(void);

#endif
