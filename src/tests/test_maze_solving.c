#include "test.h"

START_TEST(test_init_queue) {
  Queue q;
  init_queue(&q);

  ck_assert_int_eq(q.front, -1);
  ck_assert_int_eq(q.rear, -1);
}
END_TEST

START_TEST(test_enqueue_dequeue_single_element) {
  Queue q;
  init_queue(&q);

  Point p1 = {1, 2, 3};

  enqueue(&q, p1);

  Point p = dequeue(&q);
  ck_assert_int_eq(p.row, p1.row);
  ck_assert_int_eq(p.col, p1.col);
  ck_assert_int_eq(p.dist, p1.dist);

  ck_assert(is_empty(&q));
}
END_TEST

START_TEST(test_enqueue_dequeue_multiple_elements) {
  Queue q;
  init_queue(&q);

  Point p1 = {1, 2, 3};
  Point p2 = {4, 5, 6};
  Point p3 = {7, 8, 9};

  enqueue(&q, p1);
  enqueue(&q, p2);
  enqueue(&q, p3);

  Point p = dequeue(&q);
  ck_assert_int_eq(p.row, p1.row);
  ck_assert_int_eq(p.col, p1.col);
  ck_assert_int_eq(p.dist, p1.dist);

  p = dequeue(&q);
  ck_assert_int_eq(p.row, p2.row);
  ck_assert_int_eq(p.col, p2.col);
  ck_assert_int_eq(p.dist, p2.dist);

  p = dequeue(&q);
  ck_assert_int_eq(p.row, p3.row);
  ck_assert_int_eq(p.col, p3.col);
  ck_assert_int_eq(p.dist, p3.dist);

  ck_assert(is_empty(&q));
}
END_TEST

START_TEST(test_bfs_path_exists) {
  int rows = 3;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  Point prev[MAX_ROWS][MAX_COLS];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  right_walls[0][0] = 1;
  bottom_walls[0][1] = 1;

  int start_row = 0;
  int start_col = 0;
  int end_row = 2;
  int end_col = 2;

  int dist = bfs(right_walls, bottom_walls, start_row, start_col, end_row,
                 end_col, rows, cols, prev);

  ck_assert_int_ne(dist, -1);
  ck_assert_int_eq(dist, 4);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_bfs_no_path) {
  int rows = 3;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  Point prev[MAX_ROWS][MAX_COLS];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 1;
      bottom_walls[i][j] = 1;
    }
  }

  int start_row = 0;
  int start_col = 0;
  int end_row = 2;
  int end_col = 2;

  int dist = bfs(right_walls, bottom_walls, start_row, start_col, end_row,
                 end_col, rows, cols, prev);

  ck_assert_int_eq(dist, -1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_bfs_larger_matrix) {
  int rows = 5;
  int cols = 5;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  Point prev[MAX_ROWS][MAX_COLS];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  right_walls[0][1] = 1;
  bottom_walls[1][1] = 1;
  right_walls[2][2] = 1;
  bottom_walls[3][3] = 1;
  bottom_walls[2][3] = 1;

  int start_row = 1;
  int start_col = 4;
  int end_row = 4;
  int end_col = 4;

  int dist = bfs(right_walls, bottom_walls, start_row, start_col, end_row,
                 end_col, rows, cols, prev);

  ck_assert_int_ne(dist, -1);
  ck_assert_int_eq(dist, 3);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_mark_solution_path_simple) {
  Point prev[MAX_ROWS][MAX_COLS] = {0};
  bool solution_path[MAX_ROWS][MAX_COLS] = {false};

  prev[1][1].row = 1;
  prev[1][1].col = 0;
  prev[1][0].row = 0;
  prev[1][0].col = 0;

  int start_row = 0;
  int start_col = 0;
  int end_row = 1;
  int end_col = 1;

  mark_solution_path(prev, solution_path, start_row, start_col, end_row,
                     end_col);

  ck_assert(solution_path[0][0]);
  ck_assert(solution_path[1][0]);
  ck_assert(solution_path[1][1]);
}
END_TEST

START_TEST(test_mark_solution_path_same_start_end) {
  Point prev[MAX_ROWS][MAX_COLS] = {0};
  bool solution_path[MAX_ROWS][MAX_COLS] = {false};

  int start_row = 0;
  int start_col = 0;
  int end_row = 0;
  int end_col = 0;

  mark_solution_path(prev, solution_path, start_row, start_col, end_row,
                     end_col);

  ck_assert(solution_path[0][0]);
}
END_TEST

START_TEST(test_mark_solution_path_complex) {
  Point prev[MAX_ROWS][MAX_COLS] = {0};
  bool solution_path[MAX_ROWS][MAX_COLS] = {false};

  prev[1][2].row = 1;
  prev[1][2].col = 1;
  prev[1][1].row = 1;
  prev[1][1].col = 0;
  prev[1][0].row = 0;
  prev[1][0].col = 0;
  prev[2][2].row = 1;
  prev[2][2].col = 2;
  prev[2][1].row = 2;
  prev[2][1].col = 0;

  int start_row = 0;
  int start_col = 0;
  int end_row = 2;
  int end_col = 2;

  mark_solution_path(prev, solution_path, start_row, start_col, end_row,
                     end_col);

  ck_assert(solution_path[0][0]);
  ck_assert(solution_path[1][0]);
  ck_assert(solution_path[1][1]);
  ck_assert(solution_path[1][2]);
  ck_assert(solution_path[2][2]);
}
END_TEST

START_TEST(test_write_maze_solution_to_file_simple) {
  int rows = 2;
  int cols = 3;
  bool solution[MAX_ROWS][MAX_COLS] = {{true, false, true},
                                       {false, true, false}};

  const char *path = "test_maze_solution.txt";
  const char *expected_content = "2 3\n1 0 1 \n0 1 0 \n";

  redirect_output_to_null();

  write_maze_solution_to_file(path, solution, rows, cols);

  restore_output();

  compare_file_content(path, expected_content);

  delete_file(path);
}
END_TEST

START_TEST(test_write_maze_solution_to_file_error_opening) {
  int rows = 0;
  int cols = 0;
  bool solution[MAX_ROWS][MAX_COLS] = {{true, false, true},
                                       {false, true, false}};

  const char *path = NULL;

  redirect_output_to_null();

  write_maze_solution_to_file(path, solution, rows, cols);

  restore_output();
}
END_TEST

START_TEST(test_write_maze_solution_to_file_all_true) {
  int rows = 2;
  int cols = 3;
  bool solution[MAX_ROWS][MAX_COLS] = {{true, true, true}, {true, true, true}};

  const char *path = "test_maze_solution.txt";
  const char *expected_content = "2 3\n1 1 1 \n1 1 1 \n";

  redirect_output_to_null();

  write_maze_solution_to_file(path, solution, rows, cols);

  restore_output();

  compare_file_content(path, expected_content);

  delete_file(path);
}
END_TEST

START_TEST(test_write_maze_solution_to_file_all_false) {
  int rows = 2;
  int cols = 3;
  bool solution[MAX_ROWS][MAX_COLS] = {{false, false, false},
                                       {false, false, false}};

  const char *path = "test_maze_solution.txt";
  const char *expected_content = "2 3\n0 0 0 \n0 0 0 \n";

  redirect_output_to_null();

  write_maze_solution_to_file(path, solution, rows, cols);

  restore_output();

  compare_file_content(path, expected_content);

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_solution_from_file_success) {
  const char *path = "test_maze_solution.txt";
  const char *content = "2 3\n1 0 1 \n0 1 0 \n";
  create_temp_file(path, content);

  bool solution[MAX_ROWS][MAX_COLS] = {false};

  redirect_output_to_null();

  read_maze_solution_from_file(path, solution);

  restore_output();

  bool expected_solution[MAX_ROWS][MAX_COLS] = {{true, false, true},
                                                {false, true, false}};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_int_eq(solution[i][j], expected_solution[i][j]);
    }
  }

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_solution_from_file_error_opening) {
  const char *path = "nonexistent_file.txt";

  bool solution[MAX_ROWS][MAX_COLS] = {false};

  redirect_output_to_null();

  read_maze_solution_from_file(path, solution);

  restore_output();

  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      ck_assert_int_eq(solution[i][j], false);
    }
  }
}
END_TEST

START_TEST(test_read_maze_solution_from_file_empty_file) {
  const char *path = "test_maze_solution.txt";
  const char *content = "\n";
  create_temp_file(path, content);

  bool solution[MAX_ROWS][MAX_COLS] = {false};

  redirect_output_to_null();

  read_maze_solution_from_file(path, solution);

  restore_output();

  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      ck_assert_int_eq(solution[i][j], false);
    }
  }

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_solution_from_file_error_dimensions) {
  const char *path = "test_maze_solution.txt";
  const char *content = "101 101\n";
  create_temp_file(path, content);

  bool solution[MAX_ROWS][MAX_COLS] = {false};

  redirect_output_to_null();

  read_maze_solution_from_file(path, solution);

  restore_output();

  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      ck_assert_int_eq(solution[i][j], false);
    }
  }

  delete_file(path);
}
END_TEST

START_TEST(test_read_maze_solution_from_file_error_reading_data) {
  const char *path = "test_maze_solution.txt";
  const char *content = "2 3\n0 0 0 \n0 0 \n";
  create_temp_file(path, content);

  bool solution[MAX_ROWS][MAX_COLS] = {false};

  redirect_output_to_null();

  read_maze_solution_from_file(path, solution);

  restore_output();

  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      ck_assert_int_eq(solution[i][j], false);
    }
  }

  delete_file(path);
}
END_TEST

START_TEST(test_solve_maze_path_exists) {
  char *path = "test_maze.txt";
  const char *content = "2 3\n0 0 0 \n0 0 0 \n\n0 0 0 \n0 0 0 \n";
  create_temp_file(path, content);

  int start_row = 0;
  int start_col = 0;
  int end_row = 1;
  int end_col = 2;

  redirect_output_to_null();

  solve_maze(path, start_row, start_col, end_row, end_col);

  restore_output();

  const char *expected_content = "2 3\n1 1 1 \n0 0 1 \n";
  compare_file_content(MAZE_SOLUTION, expected_content);

  delete_file(path);
  delete_file(MAZE_SOLUTION);
}
END_TEST

START_TEST(test_solve_maze_no_path) {
  char *path = "test_maze.txt";
  const char *content = "2 3\n1 1 1 \n1 1 1 \n\n1 1 1 \n1 1 1 \n";
  create_temp_file(path, content);

  int start_row = 0;
  int start_col = 0;
  int end_row = 1;
  int end_col = 2;

  redirect_output_to_null();

  solve_maze(path, start_row, start_col, end_row, end_col);

  restore_output();

  FILE *file = fopen(MAZE_SOLUTION, "r");
  ck_assert_ptr_null(file);

  delete_file(path);
}
END_TEST

Suite *suite_maze_solving() {
  Suite *s = suite_create("MAZE_SOLVING");
  TCase *tc = tcase_create("maze_solving_tc");

  // init_queue & is_empty & enqueue & dequeue
  tcase_add_test(tc, test_init_queue);
  tcase_add_test(tc, test_enqueue_dequeue_single_element);
  tcase_add_test(tc, test_enqueue_dequeue_multiple_elements);

  // bfs
  tcase_add_test(tc, test_bfs_path_exists);
  tcase_add_test(tc, test_bfs_larger_matrix);
  tcase_add_test(tc, test_bfs_no_path);

  // mark_solution_path
  tcase_add_test(tc, test_mark_solution_path_simple);
  tcase_add_test(tc, test_mark_solution_path_same_start_end);
  tcase_add_test(tc, test_mark_solution_path_complex);

  // write_maze_solution_to_file
  tcase_add_test(tc, test_write_maze_solution_to_file_simple);
  tcase_add_test(tc, test_write_maze_solution_to_file_error_opening);
  tcase_add_test(tc, test_write_maze_solution_to_file_all_true);
  tcase_add_test(tc, test_write_maze_solution_to_file_all_false);

  // read_maze_solution_from_file
  tcase_add_test(tc, test_read_maze_solution_from_file_success);
  tcase_add_test(tc, test_read_maze_solution_from_file_error_opening);
  tcase_add_test(tc, test_read_maze_solution_from_file_empty_file);
  tcase_add_test(tc, test_read_maze_solution_from_file_error_dimensions);
  tcase_add_test(tc, test_read_maze_solution_from_file_error_reading_data);

  // solve_maze
  tcase_add_test(tc, test_solve_maze_path_exists);
  tcase_add_test(tc, test_solve_maze_no_path);

  suite_add_tcase(s, tc);
  return s;
}
