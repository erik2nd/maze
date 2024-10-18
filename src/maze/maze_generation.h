#ifndef MAZE_GENERATION_H
#define MAZE_GENERATION_H

#include <string.h>
#include <time.h>

#include "../common/common.h"

#define WALL 1

typedef struct {
  int value;
  bool without_wall;
} SetElement;

void generate_maze(int row, int col, char* path);

void create_right_walls(int** maze, int** right_walls, int row, int size);
void create_bottom_walls(int** maze, int** bottom_walls, int row, int size);
void check_bottom_walls(int* set_array, int* walls_array, int size);
void handle_row(int** maze, int** right_walls, int** bottom_walls, int i,
                int rows, int cols);

int find_max_number(int* array, int size);
void fill_empty_cells(int* array, int size);
void union_sets(int* array, int size, int current, int next);

void write_maze_to_file(const char* path, int** right_walls, int** bottom_walls,
                        int rows, int cols);
void read_maze_from_file(const char* path, int*** right_walls,
                         int*** bottom_walls, int* rows, int* cols);

#endif
