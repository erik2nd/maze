#ifndef MAZE_SOLVING_H
#define MAZE_SOLVING_H

#include "../common/common.h"
#include "../maze/maze_generation.h"

typedef struct {
  int row;
  int col;
  int dist;
} Point;

typedef struct {
  Point data[MAX_ROWS * MAX_COLS];
  int front, rear;
} Queue;

void init_queue(Queue *q);
bool is_empty(Queue *q);
void enqueue(Queue *q, Point p);
Point dequeue(Queue *q);

void solve_maze(char *path, int start_row, int start_col, int end_row,
                int end_col);

int bfs(int **right_walls, int **bottom_walls, int start_row, int start_col,
        int end_row, int end_col, int rows, int cols,
        Point prev[MAX_ROWS][MAX_COLS]);
void mark_solution_path(Point prev[MAX_ROWS][MAX_COLS],
                        bool solution_path[MAX_ROWS][MAX_COLS], int start_row,
                        int start_col, int end_row, int end_col);

void write_maze_solution_to_file(const char *path,
                                 bool solution[MAX_ROWS][MAX_COLS], int rows,
                                 int cols);
void read_maze_solution_from_file(const char *path,
                                  bool solution[MAX_ROWS][MAX_COLS]);

#endif
