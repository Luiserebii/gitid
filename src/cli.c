#include "../lib/argtable3/argtable3.h"
#include "../include/gitid.h"

#include <stdio.h>

#define PRG_NAME "gitid"
#define clean(argtable, exitcode) \
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0])); \
    return exitcode;

int main(int argc, char** argv) {

    struct arg_end* end;
    struct arg_lit* help;

    void* argtable[] = {
        help = arg_litn("h", "help", 0, 1, "display this help and exit"),
        end = arg_end(20)
    };

    //Parse, and capture errors from parsing
    int nerrors = arg_parse(argc, argv, argtable);

    //Check for --help as a special case, before checking for errors
    if(help->count) {
        printf("Usage: %s", PRG_NAME);
        //Print one-line syntax for main argtable
        arg_print_syntax(stdout, argtable, "\n");
        printf("A tool for gitid memes\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        //Exit
        clean(argtable, 0);
    }
    
    //If there are errors, print them!
    if(nerrors) {
        arg_print_errors(stderr, end, PRG_NAME);
        clean(argtable, 1);
    }


    /**
     * Process flags
     */

    //Exit
    clean(argtable, 0);
}
