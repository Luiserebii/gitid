#include "../lib/unity.h"
#include "../../include/git.h"
#include "../../include/gitid.h"
#include "../../include/gitid-id.h"
#include "../../include/vector-gitid-id.h"
#include "../../include/git-user.h"
#include "../../include/util.h"

#include <cstl/string.h>
#include <cstl/cstring.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test_gitid_get_system_gitid_ids();
void test_gitid_set_system_gitid_ids();
void test_git_get_user_global();
void test_git_set_user_global();
void test_vector_gitid_id();
void test_gitid_id_write();
void test_gitid_id_min_write();
void test_gitid_id_read();
void test_git_user_init();
void test_git_user_write();
void test_parseGitURLName();
void test_escapesh();
void test_runcmd();
void test_trimNewline();
void test_safestrcpy();

void setUp() {}
void tearDown() {}

int main() {

    UNITY_BEGIN();
    RUN_TEST(test_gitid_get_system_gitid_ids);
    RUN_TEST(test_gitid_set_system_gitid_ids);
    RUN_TEST(test_git_get_user_global);
    RUN_TEST(test_git_set_user_global);
    RUN_TEST(test_vector_gitid_id);
    RUN_TEST(test_gitid_id_write);
    RUN_TEST(test_gitid_id_min_write);
    RUN_TEST(test_gitid_id_read);

    RUN_TEST(test_git_user_init);    
    RUN_TEST(test_git_user_write);

    RUN_TEST(test_parseGitURLName);
    RUN_TEST(test_escapesh);
    RUN_TEST(test_runcmd);
    RUN_TEST(test_trimNewline);
    RUN_TEST(test_safestrcpy);
    return UNITY_END();
}

void test_gitid_get_system_gitid_ids() {

    //Attempt to get system ids from one with two
    vector_gitid_id* v = vector_init_gitid_id();
    gitid_get_system_gitid_ids_file(v, "data/double_gitid_id_1");
    
    //Assert each data piece, and size
    TEST_ASSERT_EQUAL_INT(2, vector_size_gitid_id(v));
    TEST_ASSERT_EQUAL_STRING("Luiserebii", string_cstr((*(v->head))->id_name));
    TEST_ASSERT_EQUAL_STRING("Luiserebii", string_cstr((*(v->head))->user->name));
    TEST_ASSERT_EQUAL_STRING("luis@serebii.io", string_cstr((*(v->head))->user->email));
    TEST_ASSERT_EQUAL_STRING("3B7E2D68E27CBBCF", string_cstr((*(v->head))->user->signing_key));
    
    TEST_ASSERT_EQUAL_STRING("cheem", string_cstr((*(v->head + 1))->id_name));
    TEST_ASSERT_EQUAL_STRING("I am cheem", string_cstr((*(v->head + 1))->user->name));
    TEST_ASSERT_EQUAL_STRING("cheem@tothemoon.io", string_cstr((*(v->head + 1))->user->email));
    TEST_ASSERT_EQUAL_INT(0, string_size((*(v->head + 1))->user->signing_key));
    
    //Free vector
    vector_free_gitid_id(v);

    //Test attempting to grab ids from empty file
    v = vector_init_gitid_id();
    gitid_get_system_gitid_ids_file(v, "data/empty_gitid_id_1");

    //Assert state
    TEST_ASSERT_EQUAL_INT(0, vector_size_gitid_id(v));
    TEST_ASSERT_EQUAL_PTR(NULL, v->head);

    //Free vector
    vector_free_gitid_id(v);
}

void test_gitid_set_system_gitid_ids() {
    
    //Initialize gitid_id vector
    vector_gitid_id* ids = vector_init_gitid_id();

    //Sample data
    char* id_data1[] = {"cheem", "i am cheem", "cheem@tothemoon.io"};
    char* id_data2[] = {"notcheem", "uncheem prime", "uncheemz@meme.io", "A2FJ39SA"};
    char* id_data3[] = {"secret cheem", "???", "???@???.cheem"};
    
    //Push all of sample data as gitid_ids onto the vector
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data1[0], id_data1[1], id_data1[2]));
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data2[0], id_data2[1], id_data2[2]));
    string_set_cstr(vector_at_gitid_id(ids, 1)->user->signing_key, id_data2[3]);
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data3[0], id_data3[1], id_data3[2]));

    //Finally, write to file
    gitid_set_system_gitid_ids_file(ids, "./tmp/tmp_test_gitid_set_system_gitid_ids");

    //Free vector
    vector_free_gitid_id(ids);
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
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->name), buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->name), n);

    runcmd("git config --global user.email", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->email), buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->email), e);

    runcmd("git config --global user.signingkey", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->signing_key), buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->signing_key), sigkey);

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
    string_set_cstr(user->name, n);
    string_set_cstr(user->email, e);
    string_set_cstr(user->signing_key, sigkey);

    git_set_user_global(user);

    //Finally, try confirming the set
    runcmd("git config --global user.name", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->name), buffer);

    runcmd("git config --global user.email", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->email), buffer);

    runcmd("git config --global user.signingkey", 1000, buffer), trimNewline(buffer);
    TEST_ASSERT_EQUAL_STRING(string_cstr(user->signing_key), buffer);

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
    string_set_cstr(vector_at_gitid_id(ids, 1)->user->signing_key, id_data2[3]);
    vector_push_back_gitid_id(ids, gitid_id_safe_init(id_data3[0], id_data3[1], id_data3[2]));

    //Assert current state
    TEST_ASSERT_EQUAL_STRING(id_data2[3], string_cstr(vector_at_gitid_id(ids, 1)->user->signing_key));
    TEST_ASSERT_EQUAL_STRING(id_data3[0], string_cstr(vector_at_gitid_id(ids, 2)->id_name));
    TEST_ASSERT_EQUAL_INT(3, vector_size_gitid_id(ids));

    //Attempt erase of second element
    vector_erase_free_gitid_id(ids, ids->head + 1);

    //Make assertions of first and third (now second) elements
    TEST_ASSERT_EQUAL_STRING(id_data1[1], string_cstr(vector_at_gitid_id(ids, 0)->user->name));
    TEST_ASSERT_EQUAL_STRING(id_data3[0], string_cstr(vector_at_gitid_id(ids, 1)->id_name));

    //Test vector_get_id_gitid_id by searching for one
    gitid_id* id = vector_get_id_gitid_id(ids, id_data3[0]);

    //Assert that we found our one
    TEST_ASSERT_EQUAL_STRING(id_data3[0], string_cstr(id->id_name));
    TEST_ASSERT_EQUAL_STRING(id_data3[1], string_cstr(id->user->name));
    TEST_ASSERT_EQUAL_STRING(id_data3[2], string_cstr(id->user->email));

    //Finally, attempt to free the entire vector (this should result in positives from valgrind)
    vector_free_gitid_id(ids);
}

void test_gitid_id_write() {
    gitid_id* id = gitid_id_init();
    
    string_set_cstr(id->id_name, "Luiserebii");
    string_set_cstr(id->user->name, "Luiserebii");
    string_set_cstr(id->user->email, "luis@serebii.io");
    string_set_cstr(id->user->signing_key, "3B7E2D68E27CBBCF");

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
    
    string_set_cstr(id->id_name, "Luiserebii");
    string_set_cstr(id->user->name, "Luiserebii");
    string_set_cstr(id->user->email, "luis@serebii.io");
    string_set_cstr(id->user->signing_key, "3B7E2D68E27CBBCF");

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
    
    string_set_cstr(user->name, "Luiserebii");
    string_set_cstr(user->email, "luis@serebii.io");
    string_set_cstr(user->signing_key, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_git_user_write", "w");
    TEST_ASSERT(tmp != NULL);
    git_user_write(user, tmp);

    fclose(tmp);
    git_user_free(user);
}

void test_git_user_init() {
    git_user* user = git_user_init();

    TEST_ASSERT_EQUAL_INT(0, string_size(user->name));
    TEST_ASSERT_EQUAL_INT(0, string_size(user->email));
    TEST_ASSERT_EQUAL_INT(0, string_size(user->signing_key));

    git_user_free(user);
}

void test_parseGitURLName() {
    char s1[] = "https://github.com/Luiserebii/gitid";
    char s2[] = "https://github.com/Luiserebii/gitid/";
    char s3[] = "/path/to/meme.git";
    char s4[] = "/path/to/meme.git/";
    char s5[] = "host.xz:foo/.git";
    
    char exp1[] = "gitid";
    char exp2[] = "gitid";
    char exp3[] = "meme";
    char exp4[] = "meme";
    char exp5[] = "foo";

    //Parse and assert each case
    parseGitURLName(s1);
    TEST_ASSERT_EQUAL_STRING(exp1, s1);
    parseGitURLName(s2);
    TEST_ASSERT_EQUAL_STRING(exp2, s2);
    parseGitURLName(s3);
    TEST_ASSERT_EQUAL_STRING(exp3, s3);
    parseGitURLName(s4);
    TEST_ASSERT_EQUAL_STRING(exp4, s4);
    parseGitURLName(s5);
    TEST_ASSERT_EQUAL_STRING(exp5, s5);
    
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

void test_safestrcpy() {
    char buffer[10];
    int sz = sizeof(buffer);

    char s1[] = "";
    char s2[] = "hello";
    char s3[] = "chicken";
    char s4[] = "I am a loooooooong string";
    char s5[] = "smol";

    char exp1[] = "";
    char exp2[] = "hello";
    char exp3[] = "chicken";
    char exp4[] = "I am a lo";
    char exp5[] = "smol";

    safestrcpy(buffer, s1, sz);
    TEST_ASSERT_EQUAL_STRING(exp1, buffer);
    safestrcpy(buffer, s2, sz);
    TEST_ASSERT_EQUAL_STRING(exp2, buffer);
    safestrcpy(buffer, s3, sz);
    TEST_ASSERT_EQUAL_STRING(exp3, buffer);
    safestrcpy(buffer, s4, sz);
    TEST_ASSERT_EQUAL_STRING(exp4, buffer);
    safestrcpy(buffer, s5, sz);
    TEST_ASSERT_EQUAL_STRING(exp5, buffer);
}
