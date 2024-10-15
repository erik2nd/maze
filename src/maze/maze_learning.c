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

int choose_action(int state, double **Q) {
  int res = 0;
  if ((double)rand() / RAND_MAX < EPSILON) {
    res = rand() % ACTIONS;
  } else {
    int best_action = 0;
    for (int a = 1; a < ACTIONS; a++) {
      if (Q[state][a] > Q[state][best_action]) {
        best_action = a;
      }
    }
    res = best_action;
  }
  return res;
}

void q_learning(int start_state, int goal_state, double **Q, int **right_walls,
                int **bottom_walls, int rows, int cols) {
    int count = 0;
  for (int episode = 0; episode < EPISODES; episode++) {
      printf("%d\n", count++);
    int state = start_state;
    while (state != goal_state) {
      int action = choose_action(state, Q);
      if (!is_valid_action(state, action, right_walls, bottom_walls, rows,
                           cols))
        continue;
      printf("() -> ");
      int next_state = take_action(state, action, cols);
      double reward = (next_state == goal_state) ? 100.0 : -1.0;
      double max_next_q = Q[next_state][0];
      for (int a = 1; a < ACTIONS; a++) {
        if (Q[next_state][a] > max_next_q) {
          max_next_q = Q[next_state][a];
        }
      }
      Q[state][action] +=
          ALPHA * (reward + GAMMA * max_next_q - Q[state][action]);
      state = next_state;
    }
  }
}

 void learn_agent(int** right_walls, int** bottom_walls, int rows, int cols, bool solution[MAX_ROWS][MAX_COLS], int start_x, int start_y, int end_x, int end_y) {

     double **Q = (double **)calloc(rows * cols, sizeof(double *));
     if (Q == NULL) {
       fprintf(stderr, "Memory allocation error\n");
       return;
     }
     for (int i = 0; i < rows * cols; ++i) {
       Q[i] = (double *)calloc(ACTIONS, sizeof(double));
       if (Q[i] == NULL) {
         fprintf(stderr, "Memory allocation error\n");
         return;
       }
     }

     int start_state = state_to_index(start_x, start_y, cols);
     int end_state = state_to_index(end_x, end_y, cols);

     q_learning(start_state, end_state, Q, right_walls, bottom_walls, rows,
                cols);
     
     printf("() -> ");
     write_solution(Q, cols, start_state, end_state, solution);

     for (int i = 0; i < rows * cols; i++) {
       free(Q[i]);
     }
     free(Q);
 }

void write_solution(double **Q, int size, int start_state, int goal_state, bool solution[MAX_ROWS][MAX_COLS]) {
    solution[1][1] = true;
//    printf("() -> ");
  int state = start_state;
  while (state != goal_state) {
    int row = 0, col = 0;
    index_to_state(state, &row, &col, size);
//      solution[row][col] = true;
      printf("(%d, %d) -> ", row, col);
    int best_action = 0;
    for (int a = 1; a < ACTIONS; a++) {
      if (Q[state][a] > Q[state][best_action]) {
        best_action = a;
      }
    }
    state = take_action(state, best_action, size);
  }
  int row, col;
  index_to_state(goal_state, &row, &col, size);
//    solution[row][col] = true;
    printf("(%d, %d)\n", row, col);
}
