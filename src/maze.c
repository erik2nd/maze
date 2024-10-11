#include "maze.h"

#include "maze_frontend.h"

void generate_maze(int rows, int cols, char *path) {
  int **maze = (int **)calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    maze[i] = (int *)calloc(cols, sizeof(double));
  }

  int **right_walls = (int **)calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    right_walls[i] = (int *)calloc(cols, sizeof(double));
  }

  int **bottom_walls = (int **)calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    bottom_walls[i] = (int *)calloc(cols, sizeof(double));
  }

  srand(time(NULL));

  for (int i = 0; i < rows; i++) {
    right_walls[i][cols - 1] = WALL;
  }

  for (int i = 0; i < rows; i++) {
    fill_empty_cells(maze[i], cols);

    // creating right walls
    for (int j = 0; j < cols - 1; j++) {
      if (maze[i][j] == maze[i][j + 1])
        right_walls[i][j] = WALL;
      else if (rand() % 2)
        right_walls[i][j] = WALL;
      else
        union_sets(maze[i], cols, maze[i][j], maze[i][j + 1]);
    }
    // creating bottom walls
    for (int j = 0; j < cols; j++) {
      if (rand() % 2) bottom_walls[i][j] = WALL;
    }

    check_bottom_walls(maze[i], bottom_walls[i], cols);

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

  write_maze_to_file(path, right_walls, bottom_walls, rows, cols);

  init_ncurses();
  start_color();
  init_colorpairs();
  atexit(cleanup);

  while (1) {
    attron(COLOR_PAIR(CYAN_FONT));
    draw_maze(right_walls, bottom_walls, rows, cols);
    attroff(COLOR_PAIR(CYAN_FONT));
    refresh();

    int ch = getch();
    if (ch == 'q') {
      break;
    }
  }

  if (maze) {
    for (int i = 0; i < rows; i++) {
      free(maze[i]);
    }
    free(maze);
  }

  if (right_walls) {
    for (int i = 0; i < rows; i++) {
      free(right_walls[i]);
    }
    free(right_walls);
  }

  if (bottom_walls) {
    for (int i = 0; i < rows; i++) {
      free(bottom_walls[i]);
    }
    free(bottom_walls);
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
