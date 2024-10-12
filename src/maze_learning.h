#ifndef MAZE_LEARNING_H
#define MAZE_LEARNING_H

#include <time.h>

#include "common.h"

#define ACTIONS 4
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.1
#define EPISODES 1000

int state_to_index(int row, int col, int size);
void index_to_state(int index, int *row, int *col, int size);
int is_valid_action(int state, int action, int **right_walls, int **bottom_walls, int rows, int cols);
int take_action(int state, int action, int size);
int choose_action(int state, double **Q);
void q_learning(int start_state, int goal_state, double **Q, int **right_walls, int **bottom_walls, int rows, int cols);
void print_path(double **Q, int size, int start_state, int goal_state);

#endif
