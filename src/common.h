#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_ROWS 50
#define MAX_COLS 50

int** create_matrix(int rows, int cols);
void copy_matrix(int **src, int **dst, int rows, int cols);
int compare_matrices(int **first, int **second, int rows, int cols);
void free_matrix(int** matrix, int size);

#endif
