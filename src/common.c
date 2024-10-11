#include "common.h"

int **create_matrix(int rows, int cols) {
  int **matrix = (int **)calloc(rows, sizeof(int *));
  if (matrix == NULL) {
    perror("Failed to allocate memory for matrix");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int *)calloc(cols, sizeof(int));
    if (matrix[i] == NULL) {
      perror("Failed to allocate memory for matrix row");
      for (int j = 0; j < i; j++) {
        free(matrix[j]);
      }
      free(matrix);
      exit(EXIT_FAILURE);
    }
  }
  return matrix;
}

void copy_matrix(int **src, int **dst, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

int compare_matrices(int **first, int **second, int rows, int cols) {
    int res = 1;
    for (int i = 0; i < rows && res; i++) {
        for (int j = 0; j < cols; j++) {
            if (first[i][j] != second[i][j]) {
                res = 0;
                break;
            }
        }
    }
    return res;
}

void free_matrix(int **matrix, int size) {
  if (matrix) {
    for (int i = 0; i < size; i++) {
      free(matrix[i]);
    }
    free(matrix);
  }
}
