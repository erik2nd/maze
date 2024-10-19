#include "test.h"

START_TEST(test_create_right_walls_first_row) {
  int size = 50;
  int row = 0;

  int **maze = create_matrix(1, size);
  int **right_walls = create_matrix(1, size);

  for (int j = 0; j < size; j++) {
    maze[row][j] = j;
  }

  srand(time(NULL));

  create_right_walls(maze, right_walls, row, size);

  for (int j = 0; j < size - 1; j++) {
    if (maze[row][j] == maze[row][j + 1]) {
      ck_assert_int_eq(right_walls[row][j], !WALL);
    } else {
      ck_assert_int_eq(right_walls[row][j], WALL);
    }
  }
  ck_assert_int_eq(right_walls[row][size - 1], WALL);

  free_matrix(maze, 1);
  free_matrix(right_walls, 1);
}
END_TEST

START_TEST(test_create_right_walls_another_row) {
  int size = 50;
  int row = 0;

  int **maze = create_matrix(1, size);
  int **right_walls = create_matrix(1, size);

  for (int j = 0; j < size; j++) {
    maze[row][j] = j / 2;
  }

  srand(time(NULL));

  create_right_walls(maze, right_walls, row, size);

  for (int j = 0; j < size - 1; j++) {
    ck_assert(right_walls[row][j] == WALL || right_walls[row][j] == !WALL);
  }
  ck_assert_int_eq(right_walls[row][size - 1], WALL);

  free_matrix(maze, 1);
  free_matrix(right_walls, 1);
}
END_TEST

START_TEST(test_create_bottom_walls) {
  int size = 5;
  int row = 0;

  int **maze = create_matrix(1, size);
  int **bottom_walls = create_matrix(1, size);

  for (int j = 0; j < size; j++) {
    maze[row][j] = j;
  }

  srand(time(NULL));

  create_bottom_walls(maze, bottom_walls, row, size);

  for (int j = 0; j < size; j++) {
    ck_assert(bottom_walls[row][j] == WALL || bottom_walls[row][j] == !WALL);
  }

  free_matrix(maze, 1);
  free_matrix(bottom_walls, 1);
}
END_TEST

START_TEST(test_create_bottom_walls_all_same) {
  int size = 5;
  int row = 0;

  int **maze = create_matrix(1, size);
  int **bottom_walls = create_matrix(1, size);

  for (int j = 0; j < size; j++) {
    maze[row][j] = 1;
  }

  srand(time(NULL));

  create_bottom_walls(maze, bottom_walls, row, size);

  for (int j = 0; j < size; j++) {
    ck_assert(bottom_walls[row][j] == WALL || bottom_walls[row][j] == !WALL);
  }

  free_matrix(maze, 1);
  free_matrix(bottom_walls, 1);
}
END_TEST

START_TEST(test_handle_row) {
  int rows = 3;
  int cols = 4;
  int i = 1;

  int **maze = create_matrix(rows, cols);
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      maze[r][c] = r * cols + c;
      right_walls[r][c] = WALL;
      bottom_walls[r][c] = WALL;
    }
  }

  handle_row(maze, right_walls, bottom_walls, i, rows, cols);

  i = rows - 1;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      maze[r][c] = r * cols + c;
      right_walls[r][c] = WALL;
      bottom_walls[r][c] = WALL;
    }
  }

  handle_row(maze, right_walls, bottom_walls, i, rows, cols);

  for (int j = 0; j < cols; j++) {
    ck_assert_int_eq(bottom_walls[i][j], WALL);
  }
  for (int j = 0; j < cols - 1; j++) {
    if (maze[i][j] != maze[i][j + 1]) {
      ck_assert_int_eq(right_walls[i][j], !WALL);
    }
  }

  free_matrix(maze, rows);
  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_handle_row_first_row) {
  int rows = 3;
  int cols = 4;
  int i = 0;

  int **maze = create_matrix(rows, cols);
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      maze[r][c] = r * cols + c;
      right_walls[r][c] = WALL;
      bottom_walls[r][c] = WALL;
    }
  }

  handle_row(maze, right_walls, bottom_walls, i, rows, cols);

  for (int j = 0; j < cols; j++) {
    ck_assert_int_eq(bottom_walls[i][j], WALL);
  }
  for (int j = 0; j < cols - 1; j++) {
    if (maze[i][j] != maze[i][j + 1]) {
      ck_assert_int_eq(right_walls[i][j], WALL);
    }
  }

  free_matrix(maze, rows);
  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_check_bottom_walls) {
  int size = 5;
  int set_array[] = {1, 2, 1, 3, 2};
  int walls_array[] = {1, 0, 1, 1, 0};

  check_bottom_walls(set_array, walls_array, size);

  ck_assert_int_eq(walls_array[0], 0);
  ck_assert_int_eq(walls_array[1], 0);
  ck_assert_int_eq(walls_array[2], 1);
  ck_assert_int_eq(walls_array[3], 0);
  ck_assert_int_eq(walls_array[4], 0);
}
END_TEST

START_TEST(test_check_bottom_walls_all_walls) {
  int size = 3;
  int set_array[] = {1, 1, 1};
  int walls_array[] = {1, 1, 1};

  check_bottom_walls(set_array, walls_array, size);

  ck_assert_int_eq(walls_array[0], 0);
  ck_assert_int_eq(walls_array[1], 1);
  ck_assert_int_eq(walls_array[2], 1);
}
END_TEST

START_TEST(test_check_bottom_walls_no_walls) {
  int size = 3;
  int set_array[] = {1, 1, 1};
  int walls_array[] = {0, 0, 0};

  check_bottom_walls(set_array, walls_array, size);

  ck_assert_int_eq(walls_array[0], 0);
  ck_assert_int_eq(walls_array[1], 0);
  ck_assert_int_eq(walls_array[2], 0);
}
END_TEST

START_TEST(test_find_max_number_basic) {
  int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  int size = sizeof(array) / sizeof(array[0]);

  int max_number = find_max_number(array, size);

  ck_assert_int_eq(max_number, 9);
}
END_TEST

START_TEST(test_find_max_number_single_element) {
  int array[] = {7};
  int size = sizeof(array) / sizeof(array[0]);

  int max_number = find_max_number(array, size);

  ck_assert_int_eq(max_number, 7);
}
END_TEST

START_TEST(test_find_max_number_negative_numbers) {
  int array[] = {-3, -1, -4, -1, -5, -9, -2, -6, -5, -3, -5};
  int size = sizeof(array) / sizeof(array[0]);

  int max_number = find_max_number(array, size);

  ck_assert_int_eq(max_number, -1);
}
END_TEST

START_TEST(test_find_max_number_all_same) {
  int array[] = {2, 2, 2, 2, 2};
  int size = sizeof(array) / sizeof(array[0]);

  int max_number = find_max_number(array, size);

  ck_assert_int_eq(max_number, 2);
}
END_TEST

START_TEST(test_fill_empty_cells_basic) {
  int array[] = {3, 0, 4, 0, 5, 0};
  int size = sizeof(array) / sizeof(array[0]);
  int expected[] = {3, 6, 4, 7, 5, 8};

  fill_empty_cells(array, size);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_fill_empty_cells_no_empty) {
  int array[] = {1, 2, 3, 4, 5};
  int size = sizeof(array) / sizeof(array[0]);
  int expected[] = {1, 2, 3, 4, 5};

  fill_empty_cells(array, size);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_fill_empty_cells_all_empty) {
  int array[] = {0, 0, 0, 0, 0};
  int size = sizeof(array) / sizeof(array[0]);
  int expected[] = {1, 2, 3, 4, 5};

  fill_empty_cells(array, size);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_fill_empty_cells_mixed) {
  int array[] = {0, 2, 0, 4, 0};
  int size = sizeof(array) / sizeof(array[0]);
  int expected[] = {5, 2, 6, 4, 7};

  fill_empty_cells(array, size);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_union_sets_basic) {
  int array[] = {1, 2, 3, 4, 5};
  int size = sizeof(array) / sizeof(array[0]);
  int current = 2;
  int next = 4;
  int expected[] = {1, 2, 3, 2, 5};

  union_sets(array, size, current, next);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_union_sets_no_change) {
  int array[] = {1, 2, 3, 4, 5};
  int size = sizeof(array) / sizeof(array[0]);
  int current = 2;
  int next = 6;
  int expected[] = {1, 2, 3, 4, 5};

  union_sets(array, size, current, next);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_union_sets_all_same) {
  int array[] = {2, 2, 2, 2, 2};
  int size = sizeof(array) / sizeof(array[0]);
  int current = 2;
  int next = 4;
  int expected[] = {2, 2, 2, 2, 2};

  union_sets(array, size, current, next);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_union_sets_multiple_changes) {
  int array[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
  int size = sizeof(array) / sizeof(array[0]);
  int current = 2;
  int next = 4;
  int expected[] = {1, 2, 3, 2, 5, 2, 3, 2, 1};

  union_sets(array, size, current, next);

  for (int i = 0; i < size; i++) {
    ck_assert_int_eq(array[i], expected[i]);
  }
}
END_TEST

START_TEST(test_write_maze_to_file) {
  int rows = 2;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = j % 2 == 0 ? WALL : !WALL;
      bottom_walls[i][j] = j % 2 == 0 ? !WALL : WALL;
    }
  }

  const char *path = "test_maze.txt";
  const char *expected_content = "2 3\n1 0 1 \n1 0 1 \n\n0 1 0 \n0 1 0 \n";

  redirect_output_to_null();

  write_maze_to_file(path, right_walls, bottom_walls, rows, cols);

  restore_output();

  compare_file_content(path, expected_content);

  delete_file(path);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_write_maze_to_file_error_opening) {
  const char *path = "\0";

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  write_maze_to_file(path, right_walls, bottom_walls, rows, cols);

  restore_output();

  ck_assert_ptr_null(right_walls);
  ck_assert_ptr_null(bottom_walls);
}
END_TEST

START_TEST(test_read_maze_from_file_success) {
  const char *path = "test_maze.txt";
  const char *content = "2 3\n1 2 3 \n4 5 6 \n\n7 8 9 \n10 11 12 \n";
  create_temp_file(path, content);

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  restore_output();

  ck_assert_int_eq(rows, 2);
  ck_assert_int_eq(cols, 3);

  int expected_right_walls[2][3] = {{1, 2, 3}, {4, 5, 6}};
  int expected_bottom_walls[2][3] = {{7, 8, 9}, {10, 11, 12}};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_int_eq(right_walls[i][j], expected_right_walls[i][j]);
      ck_assert_int_eq(bottom_walls[i][j], expected_bottom_walls[i][j]);
    }
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_from_file_error_opening) {
  const char *path = "nonexistent_file.txt";

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  restore_output();

  ck_assert_ptr_null(right_walls);
  ck_assert_ptr_null(bottom_walls);
}
END_TEST

START_TEST(test_read_maze_from_file_empty_file) {
  const char *path = "test_maze.txt";
  const char *content = "\n";
  create_temp_file(path, content);

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  restore_output();

  ck_assert_ptr_null(right_walls);
  ck_assert_ptr_null(bottom_walls);

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_from_file_error_dimensions) {
  const char *path = "test_maze.txt";
  const char *content = "101 101\n";
  create_temp_file(path, content);

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  restore_output();

  ck_assert_ptr_null(right_walls);
  ck_assert_ptr_null(bottom_walls);

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_from_file_error_reading_right_walls) {
  const char *path = "test_maze.txt";
  const char *content = "2 3\n1 2 3 \n4 5 \n";
  create_temp_file(path, content);

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  restore_output();

  ck_assert_ptr_null(right_walls);
  ck_assert_ptr_null(bottom_walls);

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_from_file_error_reading_bottom_walls) {
  const char *path = "test_maze.txt";
  const char *content = "2 3\n1 2 3 \n4 5 6 \n\n7 8 \n10 11 12 \n";
  create_temp_file(path, content);

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0;
  int cols = 0;

  redirect_output_to_null();

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  restore_output();

  ck_assert_ptr_null(right_walls);
  ck_assert_ptr_null(bottom_walls);

  delete_file(path);
}
END_TEST

START_TEST(test_generate_maze) {
  int rows = 2;
  int cols = 3;
  char *path = "test_maze.txt";

  redirect_output_to_null();

  generate_maze(rows, cols, path);

  restore_output();

  FILE *file = fopen(path, "r");
  if (file == NULL) {
    ck_abort_msg("Error opening file %s\n", path);
  }

  int file_rows, file_cols;
  fscanf(file, "%d %d", &file_rows, &file_cols);
  ck_assert_int_eq(file_rows, rows);
  ck_assert_int_eq(file_cols, cols);

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fscanf(file, "%d", &right_walls[i][j]);
    }
  }

  fscanf(file, "\n");

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fscanf(file, "%d", &bottom_walls[i][j]);
    }
  }

  fclose(file);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      ck_assert(right_walls[i][j] == WALL || right_walls[i][j] == !WALL);
      ck_assert(bottom_walls[i][j] == WALL || bottom_walls[i][j] == !WALL);
      if (i == rows - 1) ck_assert_int_eq(bottom_walls[i][j], WALL);
    }
    ck_assert_int_eq(right_walls[i][cols - 1], WALL);
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);

  delete_file(path);
}
END_TEST

Suite *suite_maze_generation() {
  Suite *s = suite_create("MAZE_GENERATION");
  TCase *tc = tcase_create("maze_generation_tc");

  // create_right_walls
  tcase_add_test(tc, test_create_right_walls_first_row);
  tcase_add_test(tc, test_create_right_walls_another_row);

  // create_bottom_walls
  tcase_add_test(tc, test_create_bottom_walls);
  tcase_add_test(tc, test_create_bottom_walls_all_same);

  // handle_row
  tcase_add_test(tc, test_handle_row);
  tcase_add_test(tc, test_handle_row_first_row);

  // check_bottom_walls
  tcase_add_test(tc, test_check_bottom_walls);
  tcase_add_test(tc, test_check_bottom_walls_all_walls);
  tcase_add_test(tc, test_check_bottom_walls_no_walls);

  // find_max_number
  tcase_add_test(tc, test_find_max_number_basic);
  tcase_add_test(tc, test_find_max_number_single_element);
  tcase_add_test(tc, test_find_max_number_negative_numbers);
  tcase_add_test(tc, test_find_max_number_all_same);

  // fill_empty_cells
  tcase_add_test(tc, test_fill_empty_cells_basic);
  tcase_add_test(tc, test_fill_empty_cells_no_empty);
  tcase_add_test(tc, test_fill_empty_cells_all_empty);
  tcase_add_test(tc, test_fill_empty_cells_mixed);

  // union_sets
  tcase_add_test(tc, test_union_sets_basic);
  tcase_add_test(tc, test_union_sets_no_change);
  tcase_add_test(tc, test_union_sets_all_same);
  tcase_add_test(tc, test_union_sets_multiple_changes);

  // write_maze_to_file
  tcase_add_test(tc, test_write_maze_to_file);
  tcase_add_test(tc, test_write_maze_to_file_error_opening);

  // read_maze_from_file
  tcase_add_test(tc, test_read_maze_from_file_success);
  tcase_add_test(tc, test_read_maze_from_file_error_opening);
  tcase_add_test(tc, test_read_maze_from_file_empty_file);
  tcase_add_test(tc, test_read_maze_from_file_error_dimensions);
  tcase_add_test(tc, test_read_maze_from_file_error_reading_right_walls);
  tcase_add_test(tc, test_read_maze_from_file_error_reading_bottom_walls);

  // generate_maze
  tcase_add_test(tc, test_generate_maze);

  suite_add_tcase(s, tc);
  return s;
}
