#include "../lib/unity.h"
#include "../../include/git.h"
#include "../../include/git-user.h"
#include "../../include/gitid-id.h"
#include "../../include/util.h"

#include <stdio.h>
#include <string.h>

void test_git_user_init();
void test_git_user_set_functions();
void test_git_user_write();
void test_escapesh();
void test_runcmd();
void test_trimNewline();

void setUp() {}
void tearDown() {}

int main() {

    UNITY_BEGIN();
    RUN_TEST(test_git_user_init);
    RUN_TEST(test_git_user_set_functions);
    RUN_TEST(test_git_user_write);
    
    RUN_TEST(test_escapesh);
    RUN_TEST(test_runcmd);
    RUN_TEST(test_trimNewline);
    return UNITY_END();
}

void test_git_user_write() {
    git_user* id = git_user_init();
    
    git_user_set_name(id, "Luiserebii");
    git_user_set_email(id, "luis@serebii.io");
    git_user_set_signing_key(id, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    FILE* tmp = fopen("../tmp/temp_test_git_user_write", "w");
    git_user_write(id, tmp);
    int res = fclose(tmp);
    TEST_ASSERT(res != EOF)
}

void test_git_user_set_functions() {
    char n[] = "Luiserebii";
    char e[] = "luis@serebii.io";
    char sigkey[] = "3B7E2D68E27CBBCF";
    git_user* user = git_user_init();

    git_user_set_name(user, n);
    git_user_set_email(user, e);
    git_user_set_signing_key(user, sigkey);

    TEST_ASSERT(strcmp(n, user->name) == 0);
    TEST_ASSERT(strcmp(e, user->email) == 0);
    TEST_ASSERT(strcmp(sigkey, user->signing_key) == 0);

    git_user_free(user);
}

void test_git_user_init() {
    git_user* user = git_user_init();

    TEST_ASSERT_EQUAL_PTR(user->name, NULL);
    TEST_ASSERT_EQUAL_PTR(user->email, NULL);
    TEST_ASSERT_EQUAL_PTR(user->signing_key, NULL);

    git_user_free(user);
}

void test_escapesh() {
    char s1[100] = "ls -lha";
    char s2[100] = "Fun Giraffe' 'ls -lha'";
    char s3[100] = "'Meme Team'";

    char exp1[] = "ls -lha";
    char exp2[] = "Fun Giraffe'\\'' '\\''ls -lha'\\''";
    char exp3[] = "'\\''Meme Team'\\''";

    escapesh(s1);
    escapesh(s2);
    escapesh(s3);

    TEST_ASSERT(strcmp(s1, exp1) == 0);
    TEST_ASSERT(strcmp(s2, exp2) == 0);
    TEST_ASSERT(strcmp(s3, exp3) == 0);
}

void test_runcmd() {
    char cmd[] = "echo hello";
    char exp[] = "hello\n";

    int maxsz = 100;
    char res[maxsz];
    
    runcmd(cmd, maxsz, res);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(res, exp, sizeof(exp));
}

void test_trimNewline() {
    char s[] = "Hello\n";
    char exp[] = "Hello";
    trimNewline(s);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(s, exp, sizeof(exp));
}
