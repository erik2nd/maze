#include "maze.h"

#include "frontend.h"

void generate_maze(int rows, int cols, char *path) {
  int **maze = create_matrix(rows, cols);
  int **right_walls = create_matrix(rows, cols);
  int **bottom_walls = create_matrix(rows, cols);

  srand(time(NULL));

  for (int i = 0; i < rows; i++) {
    fill_empty_cells(maze[i], cols);
    create_right_walls(maze, right_walls, i, cols);
    create_bottom_walls(maze, bottom_walls, i, cols);
    handle_row(maze, right_walls, bottom_walls, i, rows, cols);
  }

  write_maze_to_file(path, right_walls, bottom_walls, rows, cols);

//  init_ncurses();
//  start_color();
//  init_colorpairs();
//  atexit(cleanup);
//
//  while (1) {
//    draw_maze(right_walls, bottom_walls, rows, cols);
//    refresh();
//
//    int ch = getch();
//    if (ch == 'q') {
//      break;
//    }
//  }

  free_matrix(maze, rows);
  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}

void create_right_walls(int **maze, int **right_walls, int row, int size) {
  for (int j = 0; j < size - 1; j++) {
    if (maze[row][j] == maze[row][j + 1])
      right_walls[row][j] = WALL;
    else if (rand() % 2)
      right_walls[row][j] = WALL;
    else
      union_sets(maze[row], size, maze[row][j], maze[row][j + 1]);
  }
  right_walls[row][size - 1] = WALL;
}

void create_bottom_walls(int **maze, int **bottom_walls, int row, int size) {
  for (int j = 0; j < size; j++) {
    if (rand() % 2) bottom_walls[row][j] = WALL;
  }
  check_bottom_walls(maze[row], bottom_walls[row], size);
}

void handle_row(int **maze, int **right_walls, int **bottom_walls, int i,
                int rows, int cols) {
  if (i != rows - 1) {
    memcpy(maze[i + 1], maze[i], cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      if (bottom_walls[i][j]) maze[i + 1][j] = 0;
    }
  } else {
    for (int j = 0; j < cols; j++) {
      bottom_walls[i][j] = WALL;
    }
    for (int j = 0; j < cols - 1; j++) {
      if (maze[i][j] != maze[i][j + 1]) {
        right_walls[i][j] = 0;
        union_sets(maze[i], cols, maze[i][j], maze[i][j + 1]);
      }
    }
  }
}

void check_bottom_walls(int *set_array, int *walls_array, int size) {
  SetElement *sets = NULL;
  int set_count = 0;

  for (int i = 0; i < size; i++) {
    int set_value = set_array[i];
    bool found = false;

    for (int j = 0; j < set_count; j++) {
      if (sets[j].value == set_value) {
        found = true;
        if (!walls_array[i]) {
          sets[j].without_wall = true;
        }
        break;
      }
    }

    if (!found) {
      set_count++;
      sets = (SetElement *)realloc(sets, set_count * sizeof(SetElement));
      sets[set_count - 1].value = set_value;
      sets[set_count - 1].without_wall = !walls_array[i];
    }
  }

  for (int i = 0; i < size; i++) {
    int set_value = set_array[i];
    for (int j = 0; j < set_count; j++) {
      if (sets[j].value == set_value && !sets[j].without_wall) {
        walls_array[i] = false;
        sets[j].without_wall = true;
        break;
      }
    }
  }

  free(sets);
}

int find_max_number(int *array, int size) {
  int max_number = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max_number) {
      max_number = array[i];
    }
  }
  return max_number;
}

void fill_empty_cells(int *array, int size) {
  int max_number = find_max_number(array, size);
  int next = max_number + 1;
  for (int i = 0; i < size; i++) {
    if (!array[i]) {
      array[i] = next;
      next++;
    }
  }
}

void union_sets(int *array, int size, int current, int next) {
  for (int i = 0; i < size; i++) {
    if (array[i] == next) {
      array[i] = current;
    }
  }
}

void write_maze_to_file(const char *path, int **right_walls, int **bottom_walls,
                        int rows, int cols) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    printf("Error opening file %s\n", path);
    return;
  }

  fprintf(file, "%d %d\n", rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(file, "%d ", right_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  fprintf(file, "\n");

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(file, "%d ", bottom_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
  printf("Maze successfully written to file %s\n", path);
}

void read_maze_from_file(const char *path, int ***right_walls, int ***bottom_walls, int *rows, int *cols) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", path);
        return;
    }

    if (fscanf(file, "%d %d", rows, cols) != 2) {
        printf("Error reading maze dimensions from file %s\n", path);
        fclose(file);
        return;
    }

    *right_walls = create_matrix(*rows, *cols);
    *bottom_walls = create_matrix(*rows, *cols);

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (fscanf(file, "%d", &(*right_walls)[i][j]) != 1) {
                printf("Error reading right_walls from file %s\n", path);
                fclose(file);
                free_matrix(*right_walls, *rows);
                free_matrix(*bottom_walls, *rows);
                return;
            }
        }
    }

    fscanf(file, "\n");

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (fscanf(file, "%d", &(*bottom_walls)[i][j]) != 1) {
                printf("Error reading bottom_walls from file %s\n", path);
                fclose(file);
                free_matrix(*right_walls, *rows);
                free_matrix(*bottom_walls, *rows);
                return;
            }
        }
    }

    fclose(file);
    printf("Maze successfully read from file %s\n", path);
}
