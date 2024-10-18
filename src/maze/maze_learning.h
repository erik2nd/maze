#ifndef MAZE_LEARNING_H
#define MAZE_LEARNING_H

#include <math.h>
#include <time.h>

#include "../common/common.h"

#define ACTIONS 4

#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.1
#define EPISODES 1000

#define INIT_Q_VALUE -0.01
#define REWARD_GOAL 100.0
#define REWARD_STEP -1.0
#define REWARD_REVISIT -10.0
#define REWARD_DEAD_END -20.0

void learn_agent(int **right_walls, int **bottom_walls, int rows, int cols,
                 bool solution[MAX_ROWS][MAX_COLS], int start_x, int start_y,
                 int end_x, int end_y);

int state_to_index(int row, int col, int size);
void index_to_state(int index, int *row, int *col, int size);

int is_valid_action(int state, int action, int **right_walls,
                    int **bottom_walls, int rows, int cols);
int take_action(int state, int action, int size);
int choose_action(int state, double **Q, double epsilon, int **right_walls,
                  int **bottom_walls, int rows, int cols);

void q_learning(int start_state, int goal_state, double **Q, int **right_walls,
                int **bottom_walls, int rows, int cols);
void write_solution(double **Q, int size, int start_state, int goal_state,
                    bool solution[MAX_ROWS][MAX_COLS], int **right_walls,
                    int **bottom_walls);

int get_opposite_action(int action);
void show_progress(int current_iteration, int total_iterations);

#endif
