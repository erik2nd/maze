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

START_TEST(test_is_valid_action_up) {
  int rows = 3;
  int cols = 3;
  int state = 3;   // row = 1, col = 0
  int action = 0;  // up

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_is_valid_action_down) {
  int rows = 3;
  int cols = 3;
  int state = 3;   // row = 1, col = 0
  int action = 1;  // down

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_is_valid_action_left) {
  int rows = 3;
  int cols = 3;
  int state = 4;   // row = 1, col = 1
  int action = 2;  // left

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_is_valid_action_right) {
  int rows = 3;
  int cols = 3;
  int state = 4;   // row = 1, col = 1
  int action = 3;  // right

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  int res =
      is_valid_action(state, action, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(res, 1);

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

START_TEST(test_choose_action_all_valid) {
  int rows = 3;
  int cols = 3;
  int state = 4;  // row = 1, col = 1
  double epsilon = 0.1;

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  double **Q = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; i++) {
    Q[i] = malloc(ACTIONS * sizeof(double));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }
  for (int i = 0; i < rows * cols; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = 0.0;
    }
  }

  Q[state][0] = 1.0;
  Q[state][1] = 2.0;
  Q[state][2] = 3.0;
  Q[state][3] = 4.0;

  int action =
      choose_action(state, Q, epsilon, right_walls, bottom_walls, rows, cols);

  ck_assert_int_ge(action, 0);
  ck_assert_int_le(action, 3);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}
END_TEST

START_TEST(test_choose_action_some_invalid) {
  int rows = 3;
  int cols = 3;
  int state = 0;  // row = 0, col = 0
  double epsilon = 0.1;

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  double **Q = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; i++) {
    Q[i] = malloc(ACTIONS * sizeof(double));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }
  for (int i = 0; i < rows * cols; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = 0.0;
    }
  }

  Q[state][0] = 1.0;
  Q[state][1] = 2.0;
  Q[state][2] = 3.0;
  Q[state][3] = 4.0;

  right_walls[0][0] = 1;
  bottom_walls[0][0] = 1;

  int action =
      choose_action(state, Q, epsilon, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(action, -1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}
END_TEST

START_TEST(test_choose_action_all_invalid) {
  int rows = 3;
  int cols = 3;
  int state = 0;  // row = 0, col = 0
  double epsilon = 0.01;

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  double **Q = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; i++) {
    Q[i] = malloc(ACTIONS * sizeof(double));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 1;
      bottom_walls[i][j] = 1;
    }
  }
  for (int i = 0; i < rows * cols; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = 0.0;
    }
  }

  int action =
      choose_action(state, Q, epsilon, right_walls, bottom_walls, rows, cols);

  ck_assert_int_eq(action, -1);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}
END_TEST

START_TEST(test_choose_action_large_epsilon) {
  int rows = 3;
  int cols = 3;
  int state = 0;  // row = 0, col = 0
  double epsilon = 1;

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  double **Q = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; i++) {
    Q[i] = malloc(ACTIONS * sizeof(double));
  }

  for (int i = 0; i < rows * cols; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = 0.0;
    }
  }

  int action =
      choose_action(state, Q, epsilon, right_walls, bottom_walls, rows, cols);

  ck_assert_int_ge(action, 0);
  ck_assert_int_le(action, 3);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}
END_TEST

START_TEST(test_q_learning_simple) {
  int rows = 3;
  int cols = 3;
  int start_state = 0;  // row = 0, col = 0
  int goal_state = 8;   // row = 2, col = 2

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  double **Q = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; i++) {
    Q[i] = malloc(ACTIONS * sizeof(double));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }
  for (int i = 0; i < rows * cols; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = 0.0;
    }
  }

  redirect_output_to_null();

  q_learning(start_state, goal_state, Q, right_walls, bottom_walls, rows, cols);

  restore_output();

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}
END_TEST

START_TEST(test_q_learning_maze) {
  int rows = 5;
  int cols = 5;
  int start_state = 0;  // row = 0, col = 0
  int goal_state = 24;  // row = 4, col = 4

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  double **Q = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; i++) {
    Q[i] = malloc(ACTIONS * sizeof(double));
  }

  // Initialize walls and Q-table
  int right_walls_data[5][5] = {{1, 1, 1, 0, 1},
                                {1, 0, 0, 1, 1},
                                {0, 1, 1, 1, 1},
                                {1, 1, 0, 1, 1},
                                {0, 0, 0, 0, 1}};
  int bottom_walls_data[5][5] = {{0, 0, 0, 0, 1},
                                 {0, 1, 0, 1, 0},
                                 {0, 0, 0, 0, 0},
                                 {0, 1, 0, 1, 0},
                                 {1, 1, 1, 1, 1}};
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = right_walls_data[i][j];
      bottom_walls[i][j] = bottom_walls_data[i][j];
    }
  }
  for (int i = 0; i < rows * cols; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = 0.0;
    }
  }

  redirect_output_to_null();

  q_learning(start_state, goal_state, Q, right_walls, bottom_walls, rows, cols);

  restore_output();

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}
END_TEST

START_TEST(test_learn_agent_simple) {
  int rows = 3;
  int cols = 3;
  int start_x = 0;
  int start_y = 0;
  int end_x = 2;
  int end_y = 2;

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  bool solution[MAX_ROWS][MAX_COLS] = {false};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 0;
      bottom_walls[i][j] = 0;
    }
  }

  redirect_output_to_null();

  learn_agent(right_walls, bottom_walls, rows, cols, solution, start_x, start_y,
              end_x, end_y);

  restore_output();

  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (solution[i][j]) count++;
    }
  }

  ck_assert_int_eq(count, 5);

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}
END_TEST

START_TEST(test_learn_agent_no_path) {
  int rows = 3;
  int cols = 3;
  int start_x = 0;
  int start_y = 0;
  int end_x = 2;
  int end_y = 2;

  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);
  bool solution[MAX_ROWS][MAX_COLS] = {false};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      right_walls[i][j] = 1;
      bottom_walls[i][j] = 1;
    }
  }

  redirect_output_to_null();

  learn_agent(right_walls, bottom_walls, rows, cols, solution, start_x, start_y,
              end_x, end_y);

  restore_output();

  ck_assert_int_eq(solution[0][0], true);
  ck_assert_int_eq(solution[2][2], true);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if ((i == 0 && j == 0) || (i == 2 && j == 2)) continue;
      ck_assert_int_eq(solution[i][j], false);
    }
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
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
  tcase_add_test(tc, test_is_valid_action_up);
  tcase_add_test(tc, test_is_valid_action_down);
  tcase_add_test(tc, test_is_valid_action_left);
  tcase_add_test(tc, test_is_valid_action_right);

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

  // choose_action
  tcase_add_test(tc, test_choose_action_all_valid);
  tcase_add_test(tc, test_choose_action_some_invalid);
  tcase_add_test(tc, test_choose_action_all_invalid);
  tcase_add_test(tc, test_choose_action_large_epsilon);

  // q_learning
  tcase_add_test(tc, test_q_learning_simple);
  tcase_add_test(tc, test_q_learning_maze);

  // learn_agent & write_solution
  tcase_add_test(tc, test_learn_agent_simple);
  tcase_add_test(tc, test_learn_agent_no_path);

  suite_add_tcase(s, tc);
  return s;
}
