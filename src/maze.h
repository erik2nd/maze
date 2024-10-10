#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SAVE_PATH "generated_maze.txt"

#define WALL 1

typedef struct {
  int value;
  bool without_wall;
} SetElement;

void generate_maze(int row, int col, char* path);
void check_bottom_walls(int* set_array, int* walls_array, int size);
int find_max_number(int* array, int size);
void fill_empty_cells(int* array, int size);
void union_sets(int* array, int size, int current, int next);
void write_maze_to_file(const char* path, int** right_walls, int** bottom_walls,
                        int rows, int cols);

#endif
