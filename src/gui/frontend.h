#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../common/common.h"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define WHITE 7

#define BLUE_FONT 8
#define GREEN_FONT 9
#define CYAN_FONT 10
#define RED_FONT 11
#define MAGENTA_FONT 12
#define YELLOW_FONT 13

void init_ncurses();
void cleanup();

void draw_maze(int** right_walls, int** bottom_walls, int rows, int cols);
void draw_maze_solution(int** right_walls, int** bottom_walls,
                        bool solution_path[MAX_ROWS][MAX_COLS], int rows,
                        int cols);

void draw_cave(int** cave, int rows, int cols);

void init_colorpairs();
short curs_color(int color);

#endif
