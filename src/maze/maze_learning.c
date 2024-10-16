#include "maze_learning.h"

#include <math.h>

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
    switch (action) {
        case 0: // Up
            return 1; // Down
        case 1: // Down
            return 0; // Up
        case 2: // Left
            return 3; // Right
        case 3: // Right
            return 2; // Left
        default:
            return -1; // Invalid action
    }
}

int choose_action(int state, double **Q, double epsilon, int **right_walls,
                int **bottom_walls, int rows, int cols) {
  int res = 0;

  int valid_actions[ACTIONS];
    int valid_count = 0;

    for (int a = 0; a < ACTIONS; a++) {
        if (is_valid_action(state, a, right_walls, bottom_walls, rows,
                           cols)) {
            valid_actions[valid_count++] = a;
        }
    }

    if (valid_count == 0) return -1; // No valid actions available

  if ((double)rand() / RAND_MAX < epsilon) {
    res = valid_actions[rand() % valid_count]; 
  } else {
     int best_action = -1;
        double best_value = -INFINITY;
    for (int a = 0; a < ACTIONS; a++) {
      if (is_valid_action(state, a, right_walls, bottom_walls, rows,
                           cols) && Q[state][a] > best_value) {
        best_action = a;
        best_value = Q[state][a];
      }
    }
    res = best_action;
  }
  return res;
}

void q_learning(int start_state, int goal_state, double **Q, int **right_walls,
                int **bottom_walls, int rows, int cols) {
  int count = 0;
  int total_size = rows * cols;
  int *visited = calloc(total_size, sizeof(int));
  for (int episode = 0; episode < EPISODES; episode++) {
    //  double epsilon = EPSILON * (1.0 - (double)episode / EPISODES);
    printf("\n%d\n", count++);
    int state = start_state;
    int prev_state = -1;
    // int *visited = calloc(rows * cols, sizeof(int));
    for (int i = 0; i < total_size; i++) {
      visited[i] = 0;
    }
    // int visited[rows * cols] = {0}; 
    //  int visit_count = 0;
    int count = 0; 
    while (state != goal_state) {
      count++;
      int action = choose_action(state, Q, EPSILON, right_walls,
                bottom_walls, rows, cols);
      // printf("pre-action ");
      if (action == -1) break;  
      if (!is_valid_action(state, action, right_walls, bottom_walls, rows,
                           cols))
        continue;
      // printf("action ");
      int next_state = take_action(state, action, cols);
      // printf("%d ", next_state);
      // double reward = (next_state == goal_state) ? 100.0 : -1.0;
      double reward = (next_state == goal_state) ? REWARD_GOAL : REWARD_STEP;
      if (next_state == prev_state) {
          reward += REWARD_REVISIT; // Punishment for revisiting the same state
      }

      //  for (int i = 0; i < total_size; i++) {
      //           if (visited[i] == next_state) {
      //               reward += REWARD_REVISIT; // Punishment for revisiting a state
      //               Q[state][action] += ALPHA * REWARD_REVISIT; // Punish the current state
      //               Q[next_state][get_opposite_action(action)] += ALPHA * REWARD_REVISIT; // Punish the revisited state
      //               break;
      //           }
      //       }

      if (visited[next_state] == 1) {
          // reward += REWARD_REVISIT; // Punishment for revisiting a state
          Q[state][action] += ALPHA * REWARD_REVISIT; // Punish the current state
          // Q[next_state][get_opposite_action(action)] += ALPHA * REWARD_REVISIT; // Punish the revisited state
          // break;
      }

      int valid_actions_count = 0;
      for (int a = 0; a < ACTIONS; a++) {
          if (is_valid_action(next_state, a, right_walls, bottom_walls, rows,
                           cols)) {
              valid_actions_count++;
          }
      }
      if (valid_actions_count == 1 && take_action(next_state, get_opposite_action(action), cols) == state) {
          reward += REWARD_DEAD_END; // Punishment for entering a dead end
      }

      double max_next_q = -INFINITY;
      for (int a = 0; a < ACTIONS; a++) {
        if (is_valid_action(state, a, right_walls, bottom_walls, rows,
                           cols) && Q[next_state][a] > max_next_q) {
          max_next_q = Q[next_state][a];
        }
      }
      Q[state][action] +=
          ALPHA * (reward + GAMMA * max_next_q - Q[state][action]);

          
      // if (visited[next_state] == 1) {
      //     break;
      // }

      prev_state = state;
      visited[state] = 1;
      state = next_state;
      if (count > 10000000) break;
    }
  }
  free(visited);
}

void learn_agent(int **right_walls, int **bottom_walls, int rows, int cols,
                 bool solution[MAX_ROWS][MAX_COLS], int start_x, int start_y,
                 int end_x, int end_y) {
  int total_size = rows * cols;
  double **Q = (double **)calloc(total_size, sizeof(double *));
  if (Q == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    return;
  }
  for (int i = 0; i < total_size; i++) {
    Q[i] = (double *)calloc(ACTIONS, sizeof(double));
    if (Q[i] == NULL) {
      fprintf(stderr, "Memory allocation error\n");
      return;
    }
  }

   for (int i = 0; i < total_size; i++) {
        for (int j = 0; j < ACTIONS; j++) {
            Q[i][j] = INIT_Q_VALUE;
        }
    }

  int start_state = state_to_index(start_y, start_x, cols);
  int end_state = state_to_index(end_y, end_x, cols);

  q_learning(start_state, end_state, Q, right_walls, bottom_walls, rows, cols);

  for (int i = 0; i < total_size; i++) {
    printf("%d | ", i);
    for (int j = 0; j < ACTIONS; j++) {
      printf("%f ", Q[i][j]);
    }
    printf("\n");
  }

  write_solution(Q, cols, start_state, end_state, solution, right_walls,
                 bottom_walls);

  for (int i = 0; i < rows * cols; i++) {
    free(Q[i]);
  }
  free(Q);
}

void write_solution(double **Q, int size, int start_state, int goal_state,
                    bool solution[MAX_ROWS][MAX_COLS], int **right_walls,
                    int **bottom_walls) {
  int state = start_state;
  int max_iterations = 1000;
  int iteration = 0;
  //  int prev_state = -1;

  while (state != goal_state && iteration < max_iterations) {
    int row = 0, col = 0;
    index_to_state(state, &row, &col, size);
    solution[row][col] = true;
    // printf("(%d, %d) -> ", row, col);
    // int best_action = 0;
    // for (int a = 1; a < ACTIONS; a++) {
    //   if (Q[state][a] > Q[state][best_action]) {
    //     best_action = a;
    //   }
    // }
    // state = take_action(state, best_action, size);
    int best_action = -1;
    double max_q = -INFINITY;

    for (int a = 0; a < ACTIONS; a++) {
      if (is_valid_action(state, a, right_walls, bottom_walls, size, size) &&
          Q[state][a] > max_q && Q[state][a] != INIT_Q_VALUE) {
            int ro, co;
            index_to_state(take_action(state, a, size), &ro, &co, size);
            if (solution[ro][co] != 0) continue;
        max_q = Q[state][a];
        best_action = a;
      }
    }
    printf("%d ", best_action);
    if (best_action == -1) {
      printf("No valid action found from state %d\n", state);
      break;
    }

    // prev_state = state;
    state = take_action(state, best_action, size);
    iteration++;
  }
  if (iteration >= max_iterations) {
    printf("Maximum iterations reached. More training episodes needed.\n");
  } else {
    int row = 0, col = 0;
    index_to_state(goal_state, &row, &col, size);
    solution[row][col] = true;
  }
}
