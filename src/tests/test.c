#include "test.h"

int main() {
  //  Suite *suite_array[] = {suite_cave_generation(), suite_maze_generation(),
  //  suite_maze_learning(), suite_maze_solving()};
  Suite *suite_array[] = {suite_maze_generation(), suite_maze_solving(),
                          suite_maze_learning()};
  printf("\n");
  for (unsigned long i = 0; i < sizeof(suite_array) / sizeof(suite_array[0]);
       i++) {
    run_test_cases(suite_array[i]);
    printf("\n");
  }
  return 0;
}

void run_test_cases(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

void redirect_output_to_null() {
  freopen("/dev/null", "w", stdout);
  freopen("/dev/null", "w", stderr);
}

void restore_output() {
  freopen("/dev/tty", "w", stdout);
  freopen("/dev/tty", "w", stderr);
}

void compare_file_content(const char *path, const char *expected_content) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    ck_abort_msg("Error opening file %s\n", path);
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *file_content = malloc(file_size + 1);
  fread(file_content, 1, file_size, file);
  file_content[file_size] = '\0';

  fclose(file);

  ck_assert_str_eq(file_content, expected_content);

  free(file_content);
}

void create_temp_file(const char *path, const char *content) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    ck_abort_msg("Error creating temporary file %s\n", path);
  }
  fprintf(file, "%s", content);
  fclose(file);
}

void delete_file(const char *path) {
  if (remove(path) != 0) {
    printf("Error deleting file %s\n", path);
  }
}
