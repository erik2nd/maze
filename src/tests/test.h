#ifndef TEST_H
#define TEST_H

#include <check.h>

#include "../cave/cave_generation.h"
#include "../common/common.h"
#include "../maze/maze_generation.h"
#include "../maze/maze_learning.h"
#include "../maze/maze_solving.h"

void run_test_cases(Suite *testcase);

Suite *suite_cave_generation();
Suite *suite_maze_generation();
Suite *suite_maze_learning();
Suite *suite_maze_solving();

void redirect_output_to_null();
void restore_output();
void compare_file_content(const char *path, const char *expected_content);
void create_temp_file(const char *path, const char *content);
void delete_file(const char *path);

#endif
