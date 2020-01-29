#include "../lib/unity.h"
#include "../../include/git.h"
#include "../../include/gitid-id.h"
#include "../../include/vector-gitid-id.h"
#include "../../include/git-user.h"
#include "../../include/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test_git_get_user_global();
void test_git_set_user_global();
void test_vector_gitid_id();
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
    RUN_TEST(test_git_get_user_global);
    RUN_TEST(test_git_set_user_global);
    RUN_TEST(test_vector_gitid_id);
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

void test_git_get_user_global() { 
    char buffer[1000];
    //Create a temporary directory, and set it to TMPDIR
    //as a way to safely rm -rf it
    char tmpdir[] = "/tmp/tmp.XXXXXX";
    mkdtemp(tmpdir);
    
    //Set HOME to temporary directory
    setenv("HOME", tmpdir, 1);
  
    //Set temporary git user details to TMPDIR
    char n[] = "End of Evangello";
    char e[] = "endofeva@meme.io";
    char sigkey[] = "3V@01";
    //Create the command, and run
    char cmd[1000];
    sprintf(cmd, "git config --global user.name '%s' && git config --global user.email '%s'"
            "&& git config --global user.signingkey '%s'", n, e, sigkey);
    runcmd(cmd, 1000, buffer);

    git_user* user = git_user_init();
    git_get_user_global(user);

    //Finally, try confirming the get
    runcmd("git config --global user.name", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(user->name, buffer);
    TEST_ASSERT_EQUAL_STRING(user->name, n);

    runcmd("git config --global user.email", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(user->email, buffer);
    TEST_ASSERT_EQUAL_STRING(user->email, e);

    runcmd("git config --global user.signingkey", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(user->signing_key, buffer);
    TEST_ASSERT_EQUAL_STRING(user->signing_key, sigkey);

    //It feels to risky to ever run something like "rm -rf $HOME", even when temporary,
    //so let's attempt it on the TMPDIR
    //Attempt to remove .gitconfig
    strcpy(buffer, tmpdir), strcat(buffer, "/.gitconfig");
    int res = unlink(buffer);
    TEST_ASSERT_EQUAL_INT(0, res);
    //Attempt to remove the TMPDIR 
    res = rmdir(tmpdir);
    TEST_ASSERT_EQUAL_INT(0, res);
    
    //Finally, free git_user
    git_user_free(user);
}

void test_git_set_user_global() { 
    char buffer[1000];
    //Create a temporary directory, and set it to TMPDIR
    //as a way to safely rm -rf it
    char tmpdir[] = "/tmp/tmp.XXXXXX";
    mkdtemp(tmpdir);
    
    //Set HOME to temporary directory
    setenv("HOME", tmpdir, 1);
  
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
    runcmd("git config --global user.name", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(user->name, buffer);

    runcmd("git config --global user.email", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(user->email, buffer);

    runcmd("git config --global user.signingkey", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(user->signing_key, buffer);

    //It feels to risky to ever run something like "rm -rf $HOME", even when temporary,
    //so let's attempt it on the TMPDIR
    //Attempt to remove .gitconfig
    strcpy(buffer, tmpdir), strcat(buffer, "/.gitconfig");
    int res = unlink(buffer);
    TEST_ASSERT_EQUAL_INT(0, res);
    //Attempt to remove the TMPDIR 
    res = rmdir(tmpdir);
    TEST_ASSERT_EQUAL_INT(0, res);
    
    //Finally, free git_user
    git_user_free(user);
}

void test_vector_gitid_id() {
    //Initialize gitid_id vector
    vector_gitid_id* ids = vector_init_gitid_id();
    //Sample data
    char* id_data1[] = {"cheem", "i am cheem", "cheem@tothemoon.io"};
    char* id_data2[] = {"notcheem", "uncheem prime", "uncheemz@meme.io", "A2FJ39SA"};
    char* id_data3[] = {"secret cheem", "???", "???@???.cheem"};
    
    //Push all of sample data as gitid_ids onto the vector
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data1[0], id_data1[1], id_data1[2]));
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data2[0], id_data2[1], id_data2[2]));
    git_user_set_signing_key(vector_at_gitid_id(ids, 1)->user, id_data2[3]);
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data3[0], id_data3[1], id_data3[2]));

    //Assert current state
    TEST_ASSERT_EQUAL_STRING(id_data2[3], vector_at_gitid_id(ids, 1)->user->signing_key);
    TEST_ASSERT_EQUAL_STRING(id_data3[0], vector_at_gitid_id(ids, 2)->id_name);
    TEST_ASSERT_EQUAL_INT(3, vector_size_gitid_id(ids));

    //Attempt erase of second element
    vector_erase_free_gitid_id(ids, ids->head + 1);

    //Make assertions of first and third (now second) elements
    TEST_ASSERT_EQUAL_STRING(id_data1[1], vector_at_gitid_id(ids, 0)->user->name);
    TEST_ASSERT_EQUAL_STRING(id_data3[0], vector_at_gitid_id(ids, 1)->id_name);

    //Finally, attempt to free the entire vector (this should result in positives from valgrind)
    vector_free_gitid_id(ids);
}

void test_gitid_id_write() {
    gitid_id* id = gitid_id_init();
    
    gitid_id_set_id_name(id, "Luiserebii");
    git_user_set_name(id->user, "Luiserebii");
    git_user_set_email(id->user, "luis@serebii.io");
    git_user_set_signing_key(id->user, "3B7E2D68E27CBBCF");

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
    git_user_set_name(id->user, "Luiserebii");
    git_user_set_email(id->user, "luis@serebii.io");
    git_user_set_signing_key(id->user, "3B7E2D68E27CBBCF");

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
    fclose(f), fclose(tmp);

    //Testing second file
    gitid_id_clear(id);
    f = fopen(fname2, "r");
    gitid_id_min_read(id, f);

    //Write input to temporary file
    tmp = fopen("./tmp/tmp_test_gitid_id_read_2", "w");
    gitid_id_min_write(id, tmp);
   
    fclose(f), fclose(tmp); 
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

    TEST_ASSERT_EQUAL_STRING(n, user->name);
    TEST_ASSERT_EQUAL_STRING(e, user->email);
    TEST_ASSERT_EQUAL_STRING(sigkey, user->signing_key);

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

    char exp1[] = "'ls -lha'";
    char exp2[] = "'Fun Giraffe'\\'' '\\''ls -lha'\\'''";
    char exp3[] = "''\\''Meme Team'\\'''";

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
