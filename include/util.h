#ifndef UTIL_H
#define UTIL_H

void escapesh(char* str);
void runcmd(const char* command, int maxline, char* out);
int minsystem(const char* str);
void trimNewline(char* str);

#endif
