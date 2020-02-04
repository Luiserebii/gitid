#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/util.h"
#include "../lib/c-stl/include/algorithm.h"

void escapesh(char* str) {
    //Declare and load buffer with copy of str
    char buffer[strlen(str) + 1];
    strcpy(buffer, str);

    //Escape string to write
    char escapestr[] = "'\\''";
    int escsz = sizeof(escapestr) / sizeof(char);

    //Write initial '
    *str++ = '\'';

    //Write escaped values to str
    for(char* it = buffer; *it; ++it) {
        if(*it == '\'') {
            //Write '\''
            algorithm_copy(char*, escapestr, escapestr + escsz - 1, str, str);
        } else {
            *str++ = *it;
        }
    }
    //Close with ', and finally, '\0'
    *str++ = '\'', *str = '\0';
}

void runcmd(const char* command, int maxline, char* out) {
    FILE* proc;
    //Process logic in case of failure
    if((proc = popen(command, "r")) == NULL) {
        fprintf(stderr, "Internal error: Failure to execute \"%s\"\n", command);
        exit(1);
    }
    //Copy all output to string out
    int c;
    for(int i = 0; (c = getc(proc)) != EOF && i < maxline - 1; ++i) {
        *out++ = c;
    }
    //Close out
    *out = '\0';

    //Close process and return
    if(pclose(proc) == -1) {
        fprintf(stderr, "error: failure to close process from \"%s\"\n", command);
        exit(1);
    }
}

int minsystem(const char* str) {
    int code;
    if((code = system(str)) != -1) {
        return code;
    } else {
        fprintf(stderr, "error: failure to execute \"%s\"\n", str);
        exit(1);
    }
}

char* minfgets(char* s, int n, FILE* stream) {
    char* sret;
    if((sret = fgets(s, n, stream)) == NULL) {
        fprintf(stderr, "error reading file stream: potential unexpected EOF or other error");
        fprintf(stderr, "Dumping buffer contents:\n%s\n", s);
        exit(1);
    }
    return sret;
}

void trimNewline(char* str) {
    for(; *str; ++str) {
        if(*str == '\n') {
            *str = '\0';
            break;
        }
    }
}

void* safemalloc(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL) {
        fprintf(stderr, "error: memory allocation failed, system may be out of memory\n");
        exit(1);
    }
    return ptr;
}

void generate_path_home(char* buffer, const char* path) {
    //Keep it as static to minimize grabbing of HOME, I suppose
    static char* home = NULL;
    if(home == NULL) {
        home = getenv("HOME");
    }
    //Finally, generate path in buffer
    strcpy(buffer, home);
    //If we don't have a /, add one
    if(buffer[strlen(buffer) - 1] != '/') {
        strcat(buffer, "/");
    }
    strcat(buffer, path);
}

void parseGitURLName(char* url) {
    char* rslash = strrchr(url, '/');
    //If this is the last one, remove it and find "true" one
    if(!rslash[1]) {
        *rslash = '\0';
        rslash = strrchr(url, '/');
    }
    char* last = url + strlen(url);
    //Look for the last . to see if we should perhaps truncate
    char* dot = strrchr(url, '.');
    if(dot != NULL) {
        int isDotGit;
        algorithm_equal(char*, dot, last, ".git", isDotGit);
        if(isDotGit) {
            //Check if /.git, which will require a certain kind of processing
            if(rslash + 1 == dot) {
                //Using the git-clone documentation, we are parsing for "foo" in "host.xz:foo/.git"
                //I have a feeling that "host.xz:bar/foo/.git" is also valid, so...
                char* lslash;
                algorithm_find_last(url, rslash, '/', lslash);
                last = rslash;
                //If nothing was found, then we need to look for : delimiter
                if(lslash == url - 1) {
                    char* cln = strrchr(url, ':');
                    //Semantically, this doesn't make so much sense, just now this is setting the leftmost delimiter char
                    rslash = cln;
                } else {
                    rslash = lslash;
                }
            } else {
                //Set last to dot to trucate
                last = dot;
            }
        }
    }
    //Obtain name
    char* newLast;
    algorithm_copy(char*, rslash + 1, last, url, newLast);
    //Cap off with '\0'
    *newLast = '\0';
}
