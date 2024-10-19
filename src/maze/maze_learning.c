#include "maze_learning.h"

int state_to_index(int row, int col, int size) { return row * size + col; }

void index_to_state(int index, int *row, int *col, int size) {
  *row = index / size;
  *col = index % size;
}

int is_valid_action(int state, int action, int **right_walls,
                    int **bottom_walls, int rows, int cols) {
  int row = 0, col = 0;
  index_to_state(state, &row, &col, cols);
  int res = 0;
  if (action == 0 && row > 0 && !bottom_walls[row - 1][col])
    res = 1;  // up
  else if (action == 1 && row < rows - 1 && !bottom_walls[row][col])
    res = 1;  // down
  else if (action == 2 && col > 0 && !right_walls[row][col - 1])
    res = 1;  // left
  else if (action == 3 && col < cols - 1 && !right_walls[row][col])
    res = 1;  // right
  return res;
}

int take_action(int state, int action, int size) {
  int row = 0, col = 0;
  index_to_state(state, &row, &col, size);
  int res = 0;
  if (action == 0)
    res = state_to_index(row - 1, col, size);  // up
  else if (action == 1)
    res = state_to_index(row + 1, col, size);  // down
  else if (action == 2)
    res = state_to_index(row, col - 1, size);  // left
  else if (action == 3)
    res = state_to_index(row, col + 1, size);  // right
  else
    res = state;
  return res;
}

int get_opposite_action(int action) {
  int res = 0;
  switch (action) {
    case 0:     // up
      res = 1;  // down
      break;
    case 1:     // down
      res = 0;  // up
      break;
    case 2:     // left
      res = 3;  // right
      break;
    case 3:     // right
      res = 2;  // left
      break;
    default:
      res = -1;
      break;
  }
  return res;
}

int choose_action(int state, double **Q, double epsilon, int **right_walls,
                  int **bottom_walls, int rows, int cols) {
  int res = 0;

  int valid_actions[ACTIONS];
  int valid_count = 0;

  for (int a = 0; a < ACTIONS; a++) {
    if (is_valid_action(state, a, right_walls, bottom_walls, rows, cols)) {
      valid_actions[valid_count++] = a;
    }
  }

  if (valid_count == 0) {
    res = -1;
  } else {
    if ((double)rand() / RAND_MAX < epsilon) {
      res = valid_actions[rand() % valid_count];
    } else {
      int best_action = -1;
      double best_value = -INFINITY;
      for (int a = 0; a < ACTIONS; a++) {
        if (is_valid_action(state, a, right_walls, bottom_walls, rows, cols) &&
            Q[state][a] > best_value) {
          best_action = a;
          best_value = Q[state][a];
        }
      }
      res = best_action;
    }
  }
  return res;
}

void q_learning(int start_state, int goal_state, double **Q, int **right_walls,
                int **bottom_walls, int rows, int cols) {
  int count = 1;
  int total_size = rows * cols;
  int *visited = calloc(total_size, sizeof(int));

  for (int episode = 0; episode < EPISODES; episode++) {
    show_progress(count++, EPISODES);
    int state = start_state;
    int prev_state = -1;

    for (int i = 0; i < total_size; i++) {
      visited[i] = 0;
    }

    int attempts_count = 0;
    while (state != goal_state) {
      attempts_count++;
      int action = choose_action(state, Q, EPSILON, right_walls, bottom_walls,
                                 rows, cols);
      if (action == -1) break;

      int next_state = take_action(state, action, cols);
      double reward = (next_state == goal_state) ? REWARD_GOAL : REWARD_STEP;

      if (next_state == prev_state) reward += REWARD_REVISIT;
      if (visited[next_state]) Q[state][action] += ALPHA * REWARD_REVISIT;

      int valid_actions_count = 0;
      for (int a = 0; a < ACTIONS; a++) {
        if (is_valid_action(next_state, a, right_walls, bottom_walls, rows,
                            cols)) {
          valid_actions_count++;
        }
      }
      if (valid_actions_count == 1 &&
          take_action(next_state, get_opposite_action(action), cols) == state) {
        reward += REWARD_DEAD_END;
      }

      double max_next_q = -INFINITY;
      for (int a = 0; a < ACTIONS; a++) {
        if (is_valid_action(state, a, right_walls, bottom_walls, rows, cols) &&
            Q[next_state][a] > max_next_q) {
          max_next_q = Q[next_state][a];
        }
      }
      Q[state][action] +=
          ALPHA * (reward + GAMMA * max_next_q - Q[state][action]);

      prev_state = state;
      visited[state] = 1;
      state = next_state;
      if (attempts_count > 10000000) break;
    }
  }
  free(visited);
}

void show_progress(int current_iteration, int total_iterations) {
  double progress_percentage =
      ((double)current_iteration / total_iterations) * 100;
  if ((int)progress_percentage % 1 == 0) {
    printf("Progress: %.2f%%\r", progress_percentage);
    fflush(stdout);
  }
}

void learn_agent(int **right_walls, int **bottom_walls, int rows, int cols,
                 bool solution[MAX_ROWS][MAX_COLS], int start_x, int start_y,
                 int end_x, int end_y) {
  int total_size = rows * cols;
  double **Q = create_matrix_double(total_size, ACTIONS);

  for (int i = 0; i < total_size; i++) {
    for (int j = 0; j < ACTIONS; j++) {
      Q[i][j] = INIT_Q_VALUE;
    }
  }

  int start_state = state_to_index(start_y, start_x, cols);
  int end_state = state_to_index(end_y, end_x, cols);

  q_learning(start_state, end_state, Q, right_walls, bottom_walls, rows, cols);

  write_solution(Q, cols, start_state, end_state, solution, right_walls,
                 bottom_walls);

  free_matrix_double(Q, total_size);
}

void write_solution(double **Q, int size, int start_state, int goal_state,
                    bool solution[MAX_ROWS][MAX_COLS], int **right_walls,
                    int **bottom_walls) {
  int state = start_state;

  while (state != goal_state) {
    int row = 0, col = 0;
    index_to_state(state, &row, &col, size);
    solution[row][col] = true;

    int best_action = -1;
    double max_q = -INFINITY;

    for (int a = 0; a < ACTIONS; a++) {
      if (is_valid_action(state, a, right_walls, bottom_walls, size, size) &&
          Q[state][a] > max_q && Q[state][a] != INIT_Q_VALUE) {
        int row_s, col_s;
        index_to_state(take_action(state, a, size), &row_s, &col_s, size);
        if (solution[row_s][col_s] != 0) continue;
        max_q = Q[state][a];
        best_action = a;
      }
    }

    if (best_action == -1) {
      printf("More training episodes needed!\n");
      break;
    }

    state = take_action(state, best_action, size);
  }
  int row = 0, col = 0;
  index_to_state(goal_state, &row, &col, size);
  solution[row][col] = true;
}
