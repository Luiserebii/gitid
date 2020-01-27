#include "../lib/unity.h"
#include "../../include/git.h"
#include "../../include/gitid-id.h"
#include "../../include/git-user.h"
#include "../../include/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_git_set_user_global();
void test_gitid_id_write();
void test_gitid_id_min_write();
void test_gitid_id_read();
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
    RUN_TEST(test_git_set_user_global);
    RUN_TEST(test_gitid_id_write);
    RUN_TEST(test_gitid_id_min_write);
    RUN_TEST(test_gitid_id_read);

    RUN_TEST(test_git_user_init);    
    RUN_TEST(test_git_user_set_functions);
    RUN_TEST(test_git_user_write);
    
    RUN_TEST(test_escapesh);
    RUN_TEST(test_runcmd);
    RUN_TEST(test_trimNewline);
    return UNITY_END();
}

void test_git_set_user_global() { 
    char buffer[1000];
    //Create a temporary directory, and set it to TMPDIR
    //as a way to safely rm -rf it
    runcmd("mktemp -d", 1000, buffer);
    setenv("TMPDIR", buffer, 1);
    //Set HOME to temporary directory
    setenv("HOME", buffer, 1);
  
    //Create git_user as test, and try setting
    git_user* user = git_user_init();
    char n[] = "End of Evangello";
    char e[] = "endofeva@meme.io";
    char sigkey[] = "3V@01";
    git_user_set_name(user, n);
    git_user_set_email(user, e);
    git_user_set_signing_key(user, sigkey);

    git_set_user_global(user);

    //Finally, try confirming the set
    runcmd("git config --global user.name", 1000, buffer);
    TEST_ASSERT_EQUAL_STRING(user->name, buffer);

    runcmd("git config --global user.email", 1000, buffer);
    TEST_ASSERT_EQUAL_STRING(user->email, buffer);

    runcmd("git config --global user.signingkey", 1000, buffer);
    TEST_ASSERT_EQUAL_STRING(user->signing_key, buffer);

    //It feels to risky to ever run something like "rm -rf $HOME", even when temporary,
    //so let's attempt it on the TMPDIR
    runcmd("rm -rf $TMPDIR", 1000, buffer);
}

void test_gitid_id_write() {
    gitid_id* id = gitid_id_init();
    
    gitid_id_set_id_name(id, "Luiserebii");
    gitid_id_set_name(id, "Luiserebii");
    gitid_id_set_email(id, "luis@serebii.io");
    gitid_id_set_signing_key(id, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_gitid_id_write", "w");
    TEST_ASSERT(tmp != NULL);
    gitid_id_write(id, tmp);

    fclose(tmp);
    gitid_id_free(id);
}

void test_gitid_id_min_write() {
    gitid_id* id = gitid_id_init();
    
    gitid_id_set_id_name(id, "Luiserebii");
    gitid_id_set_name(id, "Luiserebii");
    gitid_id_set_email(id, "luis@serebii.io");
    gitid_id_set_signing_key(id, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_gitid_id_min_write", "w");
    gitid_id_min_write(id, tmp);

    fclose(tmp);
    gitid_id_free(id);
}

void test_gitid_id_read() {
    char fname1[] = "./data/single_gitid_id_1";
    char fname2[] = "./data/single_gitid_id_2";

    gitid_id* id = gitid_id_init();

    //Attempt to open first file for reading
    FILE* f = fopen(fname1, "r");
    gitid_id_min_read(id, f);

    //Write input to temporary file
    FILE* tmp = fopen("./tmp/tmp_test_gitid_id_read_1", "w");
    gitid_id_min_write(id, tmp);
    
    //Testing second file
    gitid_id_clear(id);
    f = fopen(fname2, "r");
    gitid_id_min_read(id, f);

    //Write input to temporary file
    tmp = fopen("./tmp/tmp_test_gitid_id_read_2", "w");
    gitid_id_min_write(id, tmp);

    gitid_id_free(id);
}

void test_git_user_write() {
    git_user* user = git_user_init();
    
    git_user_set_name(user, "Luiserebii");
    git_user_set_email(user, "luis@serebii.io");
    git_user_set_signing_key(user, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_git_user_write", "w");
    TEST_ASSERT(tmp != NULL);
    git_user_write(user, tmp);

    fclose(tmp);
    git_user_free(user);
}

void test_git_user_set_functions() {
    char n[] = "Luiserebii";
    char e[] = "luis@serebii.io";
    char sigkey[] = "3B7E2D68E27CBBCF";
    git_user* user = git_user_init();

    git_user_set_name(user, n);
    git_user_set_email(user, e);
    git_user_set_signing_key(user, sigkey);

    TEST_ASSERT_EQUAL_PTR(n, user->name);
    TEST_ASSERT_EQUAL_PTR(e, user->email);
    TEST_ASSERT_EQUAL_PTR(sigkey, user->signing_key);

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

    TEST_ASSERT_EQUAL_STRING(s1, exp1);
    TEST_ASSERT_EQUAL_STRING(s2, exp2);
    TEST_ASSERT_EQUAL_STRING(s3, exp3);
}

void test_runcmd() {
    char cmd[] = "echo hello";
    char exp[] = "hello\n";

    int maxsz = 100;
    char res[maxsz];
    
    runcmd(cmd, maxsz, res);
    TEST_ASSERT_EQUAL_STRING(exp, res);
}

void test_trimNewline() {
    char s[] = "Hello\n";
    char exp[] = "Hello";
    trimNewline(s);
    TEST_ASSERT_EQUAL_STRING(exp, s);
}
