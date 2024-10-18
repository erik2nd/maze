#include "test.h"

START_TEST(test_state_to_index_simple) {
  int size = 3;
  int row = 1;
  int col = 2;

  int index = state_to_index(row, col, size);

  ck_assert_int_eq(index, 5);
}
END_TEST

START_TEST(test_index_to_state_simple) {
  int size = 3;
  int index = 5;
  int row, col;

  index_to_state(index, &row, &col, size);

  ck_assert_int_eq(row, 1);
  ck_assert_int_eq(col, 2);
}
END_TEST

START_TEST(test_state_to_index_boundary) {
  int size = 3;
  int row = 2;
  int col = 2;

  int index = state_to_index(row, col, size);

  ck_assert_int_eq(index, 8);
}
END_TEST

START_TEST(test_index_to_state_boundary) {
  int size = 3;
  int index = 8;
  int row, col;

  index_to_state(index, &row, &col, size);

  ck_assert_int_eq(row, 2);
  ck_assert_int_eq(col, 2);
}
END_TEST

START_TEST(test_state_to_index_zero) {
  int size = 3;
  int row = 0;
  int col = 0;

  int index = state_to_index(row, col, size);

  ck_assert_int_eq(index, 0);
}
END_TEST

START_TEST(test_index_to_state_zero) {
  int size = 3;
  int index = 0;
  int row, col;

  index_to_state(index, &row, &col, size);

  ck_assert_int_eq(row, 0);
  ck_assert_int_eq(col, 0);
}
END_TEST

START_TEST(test_is_valid_action_simple) {
  int rows = 3;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int state = 4;   // row = 1, col = 1
  int action = 1;  // down

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_is_valid_action_boundary) {
  int rows = 3;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int state = 0;   // row = 0, col = 0
  int action = 0;  // up

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 0);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_is_valid_action_wall) {
  int rows = 3;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  bottom_walls[0][1] = 1;

  int state = 1;   // row = 0, col = 1
  int action = 1;  // down

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 0);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_is_valid_action_all_directions) {
  int rows = 3;
  int cols = 3;
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int state = 4;  // row = 1, col = 1

  ck_assert_int_eq(
      is_valid_action(state, 0, right_walls, bottom_walls, rows, cols),
      1);  // up
  ck_assert_int_eq(
      is_valid_action(state, 1, right_walls, bottom_walls, rows, cols),
      1);  // down
  ck_assert_int_eq(
      is_valid_action(state, 2, right_walls, bottom_walls, rows, cols),
      1);  // left
  ck_assert_int_eq(
      is_valid_action(state, 3, right_walls, bottom_walls, rows, cols),
      1);  // right

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_take_action_simple) {
  int size = 3;
  int state = 4;   // row = 1, col = 1
  int action = 1;  // down

  int new_state = take_action(state, action, size);

  ck_assert_int_eq(new_state, 7);  // row = 2, col = 1
}
END_TEST

START_TEST(test_take_action_boundary) {
  int size = 3;
  int state = 0;   // row = 0, col = 0
  int action = 0;  // up

  int new_state = take_action(state, action, size);

  ck_assert_int_eq(new_state, -3);  // row = 0, col = 0
}
END_TEST

START_TEST(test_take_action_all_directions) {
  int size = 3;
  int state = 4;  // row = 1, col = 1

  ck_assert_int_eq(take_action(state, 0, size), 1);  // up
  ck_assert_int_eq(take_action(state, 1, size), 7);  // down
  ck_assert_int_eq(take_action(state, 2, size), 3);  // left
  ck_assert_int_eq(take_action(state, 3, size), 5);  // right
}
END_TEST

START_TEST(test_take_action_invalid_action) {
  int size = 3;
  int state = 4;   // row = 1, col = 1
  int action = 4;  // invalid action

  int new_state = take_action(state, action, size);

  ck_assert_int_eq(new_state, state);
}
END_TEST

START_TEST(test_get_opposite_action_up) {
  int action = 0;  // up

  int opposite_action = get_opposite_action(action);

  ck_assert_int_eq(opposite_action, 1);  // down
}
END_TEST

START_TEST(test_get_opposite_action_down) {
  int action = 1;  // down

  int opposite_action = get_opposite_action(action);

  ck_assert_int_eq(opposite_action, 0);  // up
}
END_TEST

START_TEST(test_get_opposite_action_left) {
  int action = 2;  // left

  int opposite_action = get_opposite_action(action);

  ck_assert_int_eq(opposite_action, 3);  // right
}
END_TEST

START_TEST(test_get_opposite_action_right) {
  int action = 3;  // right

  int opposite_action = get_opposite_action(action);

  ck_assert_int_eq(opposite_action, 2);  // left
}
END_TEST

START_TEST(test_get_opposite_action_invalid) {
  int action = 4;  // invalid action

  int opposite_action = get_opposite_action(action);

  ck_assert_int_eq(opposite_action, -1);
}
END_TEST

START_TEST(test_show_progress_simple) {
  int current_iteration = 50;
  int total_iterations = 100;

  char buffer[100];
  FILE *stdout_buffer = fmemopen(buffer, sizeof(buffer), "w");
  if (stdout_buffer == NULL) {
    ck_abort_msg("Error opening buffer for stdout redirection");
  }

  FILE *original_stdout = stdout;
  stdout = stdout_buffer;

  show_progress(current_iteration, total_iterations);

  fflush(stdout_buffer);
  stdout = original_stdout;
  fclose(stdout_buffer);

  ck_assert_str_eq(buffer, "Progress: 50.00%\r");
}
END_TEST

START_TEST(test_show_progress_boundary) {
  int current_iteration = 0;
  int total_iterations = 100;

  char buffer[100];
  FILE *stdout_buffer = fmemopen(buffer, sizeof(buffer), "w");
  if (stdout_buffer == NULL) {
    ck_abort_msg("Error opening buffer for stdout redirection");
  }

  FILE *original_stdout = stdout;
  stdout = stdout_buffer;

  show_progress(current_iteration, total_iterations);

  fflush(stdout_buffer);
  stdout = original_stdout;
  fclose(stdout_buffer);

  ck_assert_str_eq(buffer, "Progress: 0.00%\r");
}
END_TEST

START_TEST(test_show_progress_full) {
  int current_iteration = 100;
  int total_iterations = 100;

  char buffer[100];
  FILE *stdout_buffer = fmemopen(buffer, sizeof(buffer), "w");
  if (stdout_buffer == NULL) {
    ck_abort_msg("Error opening buffer for stdout redirection");
  }

  FILE *original_stdout = stdout;
  stdout = stdout_buffer;

  show_progress(current_iteration, total_iterations);

  fflush(stdout_buffer);
  stdout = original_stdout;
  fclose(stdout_buffer);

  ck_assert_str_eq(buffer, "Progress: 100.00%\r");
}
END_TEST

Suite *suite_maze_learning() {
  Suite *s = suite_create("MAZE_LEARNING");
  TCase *tc = tcase_create("maze_learning_tc");

  // state_to_index
  tcase_add_test(tc, test_state_to_index_simple);
  tcase_add_test(tc, test_state_to_index_boundary);
  tcase_add_test(tc, test_state_to_index_zero);

  // index_to_state
  tcase_add_test(tc, test_index_to_state_simple);
  tcase_add_test(tc, test_index_to_state_boundary);
  tcase_add_test(tc, test_index_to_state_zero);

  // is_valid_action
  tcase_add_test(tc, test_is_valid_action_simple);
  tcase_add_test(tc, test_is_valid_action_boundary);
  tcase_add_test(tc, test_is_valid_action_wall);
  tcase_add_test(tc, test_is_valid_action_all_directions);

  // take_action
  tcase_add_test(tc, test_take_action_simple);
  tcase_add_test(tc, test_take_action_boundary);
  tcase_add_test(tc, test_take_action_all_directions);
  tcase_add_test(tc, test_take_action_invalid_action);

  // get_opposite_action
  tcase_add_test(tc, test_get_opposite_action_up);
  tcase_add_test(tc, test_get_opposite_action_down);
  tcase_add_test(tc, test_get_opposite_action_left);
  tcase_add_test(tc, test_get_opposite_action_right);
  tcase_add_test(tc, test_get_opposite_action_invalid);

  // show_progress
  tcase_add_test(tc, test_show_progress_simple);
  tcase_add_test(tc, test_show_progress_boundary);
  tcase_add_test(tc, test_show_progress_full);

  // choose_action

  // q_learning
  // write_solution

  // learn_agent

  suite_add_tcase(s, tc);
  return s;
}
