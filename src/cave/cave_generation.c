#include "cave_generation.h"

void generate_cave(int **cave, int **cave_prev, int rows, int cols, int birth,
                   int death) {
  copy_matrix(cave, cave_prev, rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int count = alive_count(cave_prev, i, j, rows, cols);
      if (cave_prev[i][j]) {
        if (count < death) cave[i][j] = DEAD;
      } else {
        if (count > birth) cave[i][j] = ALIVE;
      }
    }
  }
}

int alive_count(int **cave, int i, int j, int rows, int cols) {
  int res = 0;
  for (int k = -1; k <= 1; k++) {
    for (int m = -1; m <= 1; m++) {
      if (k == 0 && m == 0) continue;
      int i_c = i + k;
      int j_c = j + m;
      if (i_c < 0 || i_c >= rows || j_c < 0 || j_c >= cols)
        res++;
      else if (cave[i_c][j_c])
        res++;
    }
  }
  return res;
}

void read_cave_from_file(const char *path, int ***cave, int *rows, int *cols) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Error opening file %s\n", path);
    return;
  }

  if (fscanf(file, "%d %d", rows, cols) != 2) {
    printf("Error reading cave dimensions from file %s\n", path);
    fclose(file);
    return;
  }

  *cave = create_matrix(*rows, *cols);

  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {
      if (fscanf(file, "%d", &(*cave)[i][j]) != 1) {
        printf("Error reading cave from file %s\n", path);
        fclose(file);
        free_matrix(*cave, *rows);
        *cave = NULL;
        return;
      }
    }
  }

  fclose(file);
}
