#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstl/algorithm.h>
#include <cstl/string.h>
#include <cstl/cstring.h>

#include "../include/util.h"

void escapesh(string* str) {
    //Declare and load buffer with copy of str
    char* buffer = safemalloc(string_size(str) + 1);
    strcpy(buffer, string_cstr(str));

    //Clear string
    string_clear(str);

    //Escape string to write
    char escapestr[] = "'\\''";
    int escsz = sizeof(escapestr) / sizeof(char);

    //Write initial '
    string_push_back(str, '\'');

    //Write escaped values to str
    for(char* it = buffer; *it; ++it) {
        if(*it == '\'') {
            //Write '\''
            string_insert_range(str, string_end(str), escapestr, escapestr + escsz - 1);
        } else {
            string_push_back(str, *it);
        }
    }
    //Close with ', and finally, '\0'
    string_push_back(str, '\'');

    free(buffer);
}

void runcmd(const char* command, string* out) {
    FILE* proc;
    //Process logic in case of failure
    if((proc = popen(command, "r")) == NULL) {
        perror("popen");
        exit(1);
    }
    //Copy all output to string out
    int c;
    for(int i = 0; (c = getc(proc)) != EOF; ++i) {
        string_push_back(out, c);
    }

    //Close process and return
    if(pclose(proc) == -1) {
        perror("pclose");
        exit(1);
    }
}

int minsystem(const char* str) {
    int code;
    if((code = system(str)) != -1) {
        return code;
    } else {
        perror("system");
        exit(1);
    }
}

char* minfgets(char* s, int n, FILE* stream) {
    char* sret;
    if((sret = fgets(s, n, stream)) == NULL) {
        perror("fgets");
        exit(1);
    }
    return sret;
}

void string_fgets(string* s, FILE* stream) {
    int c;
    while((c = getc(stream)) != EOF) {
        string_push_back(s, c);
        if(c == '\n') {
            break;
        }
    }
    if(c == EOF && ferror(stream)) {
        perror("getc");
        exit(1);
    }
}

void string_fgets_min(string* s, FILE* stream) {
    int c;
    while((c = getc(stream)) != EOF && c != '\n') {
        string_push_back(s, c);
    }
    if(c == EOF && ferror(stream)) {
        perror("getc");
        exit(1);
    }
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
        perror("malloc");
        exit(1);
    }
    return ptr;
}

void* saferealloc(void* p, size_t size) {
    void* ptr = realloc(p, size);
    if(ptr == NULL) {
        perror("realloc");
        exit(1);
    }
    return ptr;
}

void generate_path_home(char* buffer, const char* path, size_t buffer_lim) {
    //Keep it as static to minimize grabbing of HOME, I suppose
    static char* home = NULL;
    if(home == NULL) {
        home = getenv("HOME");
    }
    //Finally, generate path in buffer
    safestrcpy(buffer, home, buffer_lim);
    //If we don't have a /, add one
    if(buffer[strlen(buffer) - 1] != '/') {
        safestrcat(buffer, "/", buffer_lim);
    }
    safestrcat(buffer, path, buffer_lim);
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
