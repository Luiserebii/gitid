#include "../lib/unity.h"
#include "../../include/git.h"
#include "../../include/git-user.h"
#include "../../include/gitid-id.h"
#include "../../include/util.h"

#include <stdio.h>
#include <string.h>

void test_git_user();
void test_escapesh();
void test_runcmd();
void test_trimNewline();

void setUp() {}
void tearDown() {}

int main() {

    UNITY_BEGIN();
    RUN_TEST(test_git_user);
    RUN_TEST(test_escapesh);
    RUN_TEST(test_runcmd);
    RUN_TEST(test_trimNewline);
    return UNITY_END();
}

void test_git_user() {
    git_user* user = git_user_init();
    git_get_user_global(user);

    printf("User obtained:\n name: %s | email: %s | signingKey: %s\n", user->name, user->email, user->signing_key);

    git_user_free(user);

    gitid_id* id = gitid_id_init();
    gitid_id_set_id_name(id, "Luiserebii");
    gitid_id_set_name(id, "Luiserebii");
    gitid_id_set_email(id, "luis@serebii.io");
    gitid_id_set_signing_key(id, "SIGNING_KEY");

    gitid_id_write(id, stdout);
    gitid_id_min_write(id, stdout);
    //Attempt read
    gitid_id_min_read(id, stdin);
    //Print read
    gitid_id_min_write(id, stdout);
    TEST_ASSERT(1);
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
