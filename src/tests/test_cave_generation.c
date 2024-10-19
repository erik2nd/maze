#include "test.h"

START_TEST(test_alive_count_center) {
  int rows = 3;
  int cols = 3;
  int **cave = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cave[i][j] = 1;
    }
  }

  int i = 1;
  int j = 1;
  int res = alive_count(cave, i, j, rows, cols);

  ck_assert_int_eq(res, 8);

  free_matrix(cave, rows);
}
END_TEST

START_TEST(test_alive_count_corner) {
  int rows = 3;
  int cols = 3;
  int **cave = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cave[i][j] = 1;
    }
  }
  cave[0][1] = 0;
  cave[1][0] = 0;
  cave[1][1] = 0;

  int i = 0;
  int j = 0;
  int res = alive_count(cave, i, j, rows, cols);

  ck_assert_int_eq(res, 5);

  free_matrix(cave, rows);
}
END_TEST

START_TEST(test_alive_count_edge) {
  int rows = 3;
  int cols = 3;
  int **cave = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cave[i][j] = 1;
    }
  }
  cave[0][0] = 0;

  int i = 1;
  int j = 0;
  int res = alive_count(cave, i, j, rows, cols);

  ck_assert_int_eq(res, 7);

  free_matrix(cave, rows);
}
END_TEST

START_TEST(test_alive_count_all_dead) {
  int rows = 3;
  int cols = 3;
  int **cave = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cave[i][j] = 0;
    }
  }

  int i = 1;
  int j = 1;
  int res = alive_count(cave, i, j, rows, cols);

  ck_assert_int_eq(res, 0);

  free_matrix(cave, rows);
}
END_TEST

START_TEST(test_alive_count_mixed) {
  int rows = 3;
  int cols = 3;
  int **cave = create_matrix(rows, cols);

  cave[0][0] = 1;
  cave[0][1] = 0;
  cave[0][2] = 1;
  cave[1][0] = 0;
  cave[1][1] = 1;
  cave[1][2] = 0;
  cave[2][0] = 1;
  cave[2][1] = 0;
  cave[2][2] = 1;

  int i = 1;
  int j = 1;
  int res = alive_count(cave, i, j, rows, cols);

  ck_assert_int_eq(res, 4);

  free_matrix(cave, rows);
}
END_TEST

START_TEST(test_read_cave_from_file_success) {
  const char *path = "test_cave.txt";
  const char *content = "3 3\n1 0 1\n0 1 0\n1 0 1\n";
  create_temp_file(path, content);

  int **cave = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_cave_from_file(path, &cave, &rows, &cols);

  restore_output();

  ck_assert_int_eq(rows, 3);
  ck_assert_int_eq(cols, 3);

  int expected_cave[3][3] = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_int_eq(cave[i][j], expected_cave[i][j]);
    }
  }

  delete_file(path);
  free_matrix(cave, rows);
}
END_TEST

START_TEST(test_read_cave_from_file_error_opening) {
  const char *path = "nonexistent_file.txt";

  int **cave = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_cave_from_file(path, &cave, &rows, &cols);

  restore_output();

  ck_assert_ptr_eq(cave, NULL);
}
END_TEST

START_TEST(test_read_cave_from_file_error_dimensions) {
  const char *path = "test_cave.txt";
  const char *content = "3\n";
  create_temp_file(path, content);

  int **cave = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_cave_from_file(path, &cave, &rows, &cols);

  restore_output();

  ck_assert_ptr_eq(cave, NULL);

  delete_file(path);
}
END_TEST

START_TEST(test_read_cave_from_file_error_reading_data) {
  const char *path = "test_cave.txt";
  const char *content = "3 3";
  create_temp_file(path, content);

  int **cave = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_cave_from_file(path, &cave, &rows, &cols);

  restore_output();

  ck_assert_ptr_eq(cave, NULL);

  delete_file(path);
}
END_TEST

START_TEST(test_generate_cave) {
  int rows = 10;
  int cols = 10;
  int birth = 4;
  int death = 3;

  int **cave = create_matrix(rows, cols);
  int **cave_prev = create_matrix(rows, cols);

  int initial_matrix[10][10] = {
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {0, 0, 1, 0, 1, 0, 1, 1, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 1, 1, 0, 0, 1, 1, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0, 0, 0}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cave[i][j] = initial_matrix[i][j];
    }
  }

  for (int i = 0; i < 5; i++) {
    generate_cave(cave, cave_prev, rows, cols, birth, death);
  }

  int expected_matrix[10][10] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_int_eq(cave[i][j], expected_matrix[i][j]);
    }
  }

  free_matrix(cave, rows);
  free_matrix(cave_prev, rows);
}
END_TEST

Suite *suite_cave_generation() {
  Suite *s = suite_create("CAVE_GENERATION");
  TCase *tc = tcase_create("cave_generation_tc");

  // generate_cave
  tcase_add_test(tc, test_generate_cave);

  // alive_count
  tcase_add_test(tc, test_alive_count_center);
  tcase_add_test(tc, test_alive_count_corner);
  tcase_add_test(tc, test_alive_count_edge);
  tcase_add_test(tc, test_alive_count_mixed);
  tcase_add_test(tc, test_alive_count_all_dead);

  // read_cave_from_file
  tcase_add_test(tc, test_read_cave_from_file_success);
  tcase_add_test(tc, test_read_cave_from_file_error_opening);
  tcase_add_test(tc, test_read_cave_from_file_error_dimensions);
  tcase_add_test(tc, test_read_cave_from_file_error_reading_data);

  suite_add_tcase(s, tc);
  return s;
}
