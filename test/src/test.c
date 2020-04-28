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
void test_parse_git_url_name();
void test_escapesh();
void test_runcmd();
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

    RUN_TEST(test_parse_git_url_name);
    RUN_TEST(test_escapesh);
    RUN_TEST(test_runcmd);
    RUN_TEST(test_safestrcpy);
    return UNITY_END();
}

void test_gitid_get_system_gitid_ids() {

    //Attempt to get system ids from one with two
    vector_gitid_id v;
    vector_gitid_id_init(&v);
    gitid_get_system_gitid_ids_file(&v, "data/double_gitid_id_1");
    
    //Assert each data piece, and size
    TEST_ASSERT_EQUAL_INT(2, vector_gitid_id_size(&v));
    TEST_ASSERT_EQUAL_STRING("Luiserebii", string_cstr(&v.head->id_name));
    TEST_ASSERT_EQUAL_STRING("Luiserebii", string_cstr(&v.head->user.name));
    TEST_ASSERT_EQUAL_STRING("luis@serebii.io", string_cstr(&v.head->user.email));
    TEST_ASSERT_EQUAL_STRING("3B7E2D68E27CBBCF", string_cstr(&v.head->user.signing_key));
    
    TEST_ASSERT_EQUAL_STRING("cheem", string_cstr(&(v.head + 1)->id_name));
    TEST_ASSERT_EQUAL_STRING("I am cheem", string_cstr(&(v.head + 1)->user.name));
    TEST_ASSERT_EQUAL_STRING("cheem@tothemoon.io", string_cstr(&(v.head + 1)->user.email));
    TEST_ASSERT_EQUAL_INT(0, string_size(&(v.head + 1)->user.signing_key));
    
    //Free vector
    vector_gitid_id_deinit(&v);

    //Test attempting to grab ids from empty file
    vector_gitid_id_init(&v);
    gitid_get_system_gitid_ids_file(&v, "data/empty_gitid_id_1");

    //Assert state
    TEST_ASSERT_EQUAL_INT(0, vector_gitid_id_size(&v));
    TEST_ASSERT_EQUAL_PTR(NULL, v.head);

    //Free vector
    vector_gitid_id_deinit_r(&v);
    vector_gitid_id_deinit(&v);
}

void test_gitid_set_system_gitid_ids() {
    //Initialize gitid_id vector
    vector_gitid_id ids;
    vector_gitid_id_init(&ids);

    //Sample data
    char* id_data1[] = {"cheem", "i am cheem", "cheem@tothemoon.io"};
    char* id_data2[] = {"notcheem", "uncheem prime", "uncheemz@meme.io", "A2FJ39SA"};
    char* id_data3[] = {"secret cheem", "???", "???@???.cheem"};
    
    //Push all of sample data as gitid_ids onto the vector
    gitid_id id;

    gitid_id_safe_init(&id, id_data1[0], id_data1[1], id_data1[2]);
    vector_gitid_id_push_back_r(&ids, &id);

    //NOTE: The heap pointers are copied directly as an element to the vector, so our reference
    //to those are invalid; we need to reinitialize (**NOT DEINIT**) to clear our id.
    //The alternative, I suppose, would be to create a copy and push that, but it seems easier
    //(and cheaper!) to just reinitialize
    gitid_id_safe_init(&id, id_data2[0], id_data2[1], id_data2[2]);
    string_asn_cstr(&id.user.signing_key, id_data2[3]);
    vector_gitid_id_push_back_r(&ids, &id);

    gitid_id_safe_init(&id, id_data3[0], id_data3[1], id_data3[2]);
    vector_gitid_id_push_back_r(&ids, &id);
    //We don't free id for the same reason noted above

    //Finally, write to file
    gitid_set_system_gitid_ids_file(&ids, "./tmp/tmp_test_gitid_set_system_gitid_ids");

    //Free vector
    vector_gitid_id_deinit_r(&ids);
    vector_gitid_id_deinit(&ids);
}

void test_git_get_user_global() { 
    char buffer[1000];
    string buf;
    string_init(&buf);
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
    runcmd(cmd, &buf);

    git_user user;
    git_user_init(&user);
    git_get_user_global(&user);

    //Finally, try confirming the get
    runcmd("git config --global user.name", &buf), string_pop_back(&buf);
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.name), string_cstr(&buf));
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.name), n);
    string_clear(&buf);

    runcmd("git config --global user.email", &buf), string_pop_back(&buf);
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.email), string_cstr(&buf));
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.email), e);
    string_clear(&buf);

    runcmd("git config --global user.signingkey", &buf), string_pop_back(&buf);
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.signing_key), string_cstr(&buf));
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.signing_key), sigkey);
    string_deinit(&buf);

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
    git_user_deinit(&user);
}

void test_git_set_user_global() { 
    char buffer[1000];
    string buf;
    string_init(&buf);
    //Create a temporary directory, and set it to TMPDIR
    //as a way to safely rm -rf it
    char tmpdir[] = "/tmp/tmp.XXXXXX";
    mkdtemp(tmpdir);
    
    //Set HOME to temporary directory
    setenv("HOME", tmpdir, 1);
  
    //Create git_user as test, and try setting
    git_user user;
    git_user_init(&user);
    char n[] = "End of Evangello";
    char e[] = "endofeva@meme.io";
    char sigkey[] = "3V@01";
    string_asn_cstr(&user.name, n);
    string_asn_cstr(&user.email, e);
    string_asn_cstr(&user.signing_key, sigkey);

    git_set_user_global(&user);

    //Finally, try confirming the set
    runcmd("git config --global user.name", &buf), string_pop_back(&buf);
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.name), string_cstr(&buf));
    string_clear(&buf);

    runcmd("git config --global user.email", &buf), string_pop_back(&buf);
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.email), string_cstr(&buf));
    string_clear(&buf);

    runcmd("git config --global user.signingkey", &buf), string_pop_back(&buf);
    TEST_ASSERT_EQUAL_STRING(string_cstr(&user.signing_key), string_cstr(&buf));
    string_deinit(&buf);

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
    git_user_deinit(&user);
}

void test_vector_gitid_id() {
    //Initialize gitid_id vector
    vector_gitid_id ids;
    vector_gitid_id_init(&ids);

    //Sample data
    char* id_data1[] = {"cheem", "i am cheem", "cheem@tothemoon.io"};
    char* id_data2[] = {"notcheem", "uncheem prime", "uncheemz@meme.io", "A2FJ39SA"};
    char* id_data3[] = {"secret cheem", "???", "???@???.cheem"};
    
    //Push all of sample data as gitid_ids onto the vector
    gitid_id id;

    gitid_id_safe_init(&id, id_data1[0], id_data1[1], id_data1[2]);
    vector_gitid_id_push_back_r(&ids, &id);

    //NOTE: The heap pointers are copied directly as an element to the vector, so our reference
    //to those are invalid; we need to reinitialize (**NOT DEINIT**) to clear our id.
    //The alternative, I suppose, would be to create a copy and push that, but it seems easier
    //(and cheaper!) to just reinitialize
    gitid_id_safe_init(&id, id_data2[0], id_data2[1], id_data2[2]);
    string_asn_cstr(&id.user.signing_key, id_data2[3]);
    vector_gitid_id_push_back_r(&ids, &id);

    gitid_id_safe_init(&id, id_data3[0], id_data3[1], id_data3[2]);
    vector_gitid_id_push_back_r(&ids, &id);
    //We don't free id for the same reason noted above

    //Assert current state
    TEST_ASSERT_EQUAL_STRING(id_data2[3], string_cstr(&(vector_gitid_id_begin(&ids) + 1)->user.signing_key));
    TEST_ASSERT_EQUAL_STRING(id_data3[0], string_cstr(&(vector_gitid_id_begin(&ids) + 2)->id_name));
    TEST_ASSERT_EQUAL_INT(3, vector_gitid_id_size(&ids));

    //Attempt erase of second element
    vector_gitid_id_erase_deinit(&ids, vector_gitid_id_begin(&ids) + 1);

    //Make assertions of first and third (now second) elements
    TEST_ASSERT_EQUAL_STRING(id_data1[1], string_cstr(&(vector_gitid_id_begin(&ids) + 0)->user.name));
    TEST_ASSERT_EQUAL_STRING(id_data3[0], string_cstr(&(vector_gitid_id_begin(&ids) + 1)->id_name));

    //Test vector_get_id_gitid_id by searching for one
    gitid_id* idp = vector_gitid_id_get_id(&ids, id_data3[0]);

    //Assert that we found our one
    TEST_ASSERT_EQUAL_STRING(id_data3[0], string_cstr(&idp->id_name));
    TEST_ASSERT_EQUAL_STRING(id_data3[1], string_cstr(&idp->user.name));
    TEST_ASSERT_EQUAL_STRING(id_data3[2], string_cstr(&idp->user.email));

    //Finally, attempt to free the entire vector (this should result in positives from valgrind)
    vector_gitid_id_deinit_r(&ids);
    vector_gitid_id_deinit(&ids);
}

void test_gitid_id_write() {
    gitid_id id;
    gitid_id_init(&id);
    
    string_asn_cstr(&id.id_name, "Luiserebii");
    string_asn_cstr(&id.user.name, "Luiserebii");
    string_asn_cstr(&id.user.email, "luis@serebii.io");
    string_asn_cstr(&id.user.signing_key, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_gitid_id_write", "w");
    TEST_ASSERT(tmp != NULL);
    gitid_id_write(&id, tmp);

    fclose(tmp);
    gitid_id_deinit(&id);
}

void test_gitid_id_min_write() {
    gitid_id id;
    gitid_id_init(&id);
    
    string_asn_cstr(&id.id_name, "Luiserebii");
    string_asn_cstr(&id.user.name, "Luiserebii");
    string_asn_cstr(&id.user.email, "luis@serebii.io");
    string_asn_cstr(&id.user.signing_key, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_gitid_id_min_write", "w");
    gitid_id_min_write(&id, tmp);

    fclose(tmp);
    gitid_id_deinit(&id);
}

void test_gitid_id_read() {
    char fname1[] = "./data/single_gitid_id_1";
    char fname2[] = "./data/single_gitid_id_2";

    gitid_id id;
    gitid_id_init(&id);

    //Attempt to open first file for reading
    FILE* f = fopen(fname1, "r");
    gitid_id_min_read(&id, f);

    //Write input to temporary file
    FILE* tmp = fopen("./tmp/tmp_test_gitid_id_read_1", "w");
    gitid_id_min_write(&id, tmp);
    fclose(f), fclose(tmp);

    //Testing second file
    gitid_id_clear(&id);
    f = fopen(fname2, "r");
    gitid_id_min_read(&id, f);

    //Write input to temporary file
    tmp = fopen("./tmp/tmp_test_gitid_id_read_2", "w");
    gitid_id_min_write(&id, tmp);
   
    fclose(f), fclose(tmp); 
    gitid_id_deinit(&id);
}

void test_git_user_write() {
    git_user user;
    git_user_init(&user);
    
    string_asn_cstr(&user.name, "Luiserebii");
    string_asn_cstr(&user.email, "luis@serebii.io");
    string_asn_cstr(&user.signing_key, "3B7E2D68E27CBBCF");

    //Temporary file to write to
    //NOTE: fopen() relative paths are relative to the execution of the 
    //program, note this
    FILE* tmp = fopen("./tmp/tmp_test_git_user_write", "w");
    TEST_ASSERT(tmp != NULL);
    git_user_write(&user, tmp);

    fclose(tmp);
    git_user_deinit(&user);
}

void test_git_user_init() {
    git_user user;
    git_user_init(&user);

    TEST_ASSERT_EQUAL_INT(0, string_size(&user.name));
    TEST_ASSERT_EQUAL_INT(0, string_size(&user.email));
    TEST_ASSERT_EQUAL_INT(0, string_size(&user.signing_key));

    git_user_deinit(&user);
}

void test_parse_git_url_name() {
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
    parse_git_url_name(s1);
    TEST_ASSERT_EQUAL_STRING(exp1, s1);
    parse_git_url_name(s2);
    TEST_ASSERT_EQUAL_STRING(exp2, s2);
    parse_git_url_name(s3);
    TEST_ASSERT_EQUAL_STRING(exp3, s3);
    parse_git_url_name(s4);
    TEST_ASSERT_EQUAL_STRING(exp4, s4);
    parse_git_url_name(s5);
    TEST_ASSERT_EQUAL_STRING(exp5, s5);
    
}

void test_escapesh() {
    string s1, s2, s3;
    string_init_cstr(&s1, "ls -lha");
    string_init_cstr(&s2, "Fun Giraffe' 'ls -lha'");
    string_init_cstr(&s3, "'Meme Team'");

    char exp1[] = "'ls -lha'";
    char exp2[] = "'Fun Giraffe'\\'' '\\''ls -lha'\\'''";
    char exp3[] = "''\\''Meme Team'\\'''";

    escapesh(&s1);
    escapesh(&s2);
    escapesh(&s3);

    TEST_ASSERT_EQUAL_STRING(exp1, string_cstr(&s1));
    TEST_ASSERT_EQUAL_STRING(exp2, string_cstr(&s2));
    TEST_ASSERT_EQUAL_STRING(exp3, string_cstr(&s3));
}

void test_runcmd() {
    char cmd[] = "echo hello";
    char exp[] = "hello\n";

    string res;
    string_init_capacity(&res, 10);

    runcmd(cmd, &res);
    TEST_ASSERT_EQUAL_STRING(exp, string_cstr(&res));
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
