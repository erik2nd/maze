#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cave/cave.h"
#include "maze/maze.h"
#include "maze/maze_learning.h"
#include "maze/maze_solving.h"

// Структура для хранения флагов
typedef struct {
  int maze_flag;
  int start_flag;
  int end_flag;
  int height_flag;
  int width_flag;
  int cave_flag;
  int birth_flag;
  int death_flag;
  int milliseconds_flag;
  int learning_flag;
  int output_flag;
} Flags;

// Функция для выделения памяти и копирования строки
char *allocate_and_copy_string(const char *str) {
  char *new_str = malloc(strlen(str) + 1);
  if (new_str) {
    strcpy(new_str, str);
  }
  return new_str;
}

void print_usage(char *program_name) {
  fprintf(stderr, "Usage: %s [options]\n", program_name);
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "  -m, --maze <path>          Maze file (optional)\n");
  fprintf(stderr, "  -h, --height <int>         Height (positive number)\n");
  fprintf(stderr, "  -w, --width <int>          Width (positive number)\n");
  fprintf(stderr,
          "  -s, --start <x> <y>        Start position (positive numbers)\n");
  fprintf(stderr,
          "  -e, --end <x> <y>          End position (positive numbers)\n");
  fprintf(stderr, "  -c, --cave <path>          Cave file\n");
  fprintf(stderr, "  -b, --birth <int>          Birth (0 <= x <= 7)\n");
  fprintf(stderr, "  -d, --death <int>          Death (0 <= x <= 7)\n");
  fprintf(stderr,
          "  -n, --milliseconds <int>   Milliseconds (positive number)\n");
  fprintf(stderr, "  -l, --learning <path>      Learning file\n");
  fprintf(stderr, "  -f, --output-file <path>   Output file\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  Flags flags = {0};
  char *maze_file = NULL;
  int start_x = 0, start_y = 0;
  int end_x = 0, end_y = 0;
  int height = 0;
  int width = 0;
  char *cave_file = NULL;
  int birth = 0;
  int death = 0;
  int milliseconds = 0;
  char *learning_file = NULL;
  char *output_file = NULL;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--maze") == 0) {
      flags.maze_flag = 1;
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        maze_file = allocate_and_copy_string(argv[++i]);
      }
    } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--start") == 0) {
      flags.start_flag = 1;
      if (i + 2 < argc) {
        start_x = atoi(argv[++i]) - 1;
        start_y = atoi(argv[++i]) - 1;
        if (start_x < 0 || start_y < 0) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--end") == 0) {
      flags.end_flag = 1;
      if (i + 2 < argc) {
        end_x = atoi(argv[++i]) - 1;
        end_y = atoi(argv[++i]) - 1;
        if (end_x < 0 || end_y < 0) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) {
      flags.height_flag = 1;
      if (i + 1 < argc) {
        height = atoi(argv[++i]);
        if (height <= 0 || height > MAX_COLS) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
      flags.width_flag = 1;
      if (i + 1 < argc) {
        width = atoi(argv[++i]);
        if (width <= 0 || width > MAX_ROWS) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cave") == 0) {
      flags.cave_flag = 1;
      if (i + 1 < argc) {
        cave_file = allocate_and_copy_string(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--birth") == 0) {
      flags.birth_flag = 1;
      if (i + 1 < argc) {
        birth = atoi(argv[++i]);
        if (birth < 0 || birth > 7) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--death") == 0) {
      flags.death_flag = 1;
      if (i + 1 < argc) {
        death = atoi(argv[++i]);
        if (death < 0 || death > 7) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-n") == 0 ||
               strcmp(argv[i], "--milliseconds") == 0) {
      flags.milliseconds_flag = 1;
      if (i + 1 < argc) {
        milliseconds = atoi(argv[++i]);
        if (milliseconds < 0) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-l") == 0 ||
               strcmp(argv[i], "--learning") == 0) {
      flags.learning_flag = 1;
      if (i + 1 < argc) {
        learning_file = allocate_and_copy_string(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-f") == 0 ||
               strcmp(argv[i], "--output-file") == 0) {
      flags.output_flag = 1;
      if (i + 1 < argc) {
        output_file = allocate_and_copy_string(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else {
      print_usage(argv[0]);
    }
  }

  // Вывод значений для проверки
  printf("Maze file: %s\n",
         flags.maze_flag ? (maze_file ? maze_file : "не указан") : "не указан");
  printf("Start: (%d, %d)\n", start_x, start_y);
  printf("End: (%d, %d)\n", end_x, end_y);
  printf("Height: %d\n", height);
  printf("Width: %d\n", width);
  printf("Cave file: %s\n", flags.cave_flag ? cave_file : "не указан");
  printf("Birth: %d\n", birth);
  printf("Death: %d\n", death);
  printf("Milliseconds: %d\n", milliseconds);
  printf("Learning file: %s\n",
         flags.learning_flag ? learning_file : "не указан");
  printf("Output file: %s\n", flags.output_flag ? output_file : "не указан");

  if (flags.maze_flag) {
    if (maze_file) {
      if (flags.start_flag || flags.end_flag) {
        solve_maze(maze_file, start_y, start_x, end_y, end_x);
      } else {
      }
    } else {
      if (flags.start_flag || flags.end_flag) {
        generate_maze(height, width,
                      flags.output_flag ? output_file : SAVE_PATH);
        solve_maze(flags.output_flag ? output_file : SAVE_PATH, start_y,
                   start_x, end_y, end_x);
      } else {
        generate_maze(height, width,
                      flags.output_flag ? output_file : SAVE_PATH);
      }
    }
  }
  if (flags.cave_flag) {
    generate_cave(cave_file, birth, death);
  }
  if (flags.learning_flag) {
    int **right_walls = NULL;
    int **bottom_walls = NULL;
    int rows = 0, cols = 0;

    read_maze_from_file(learning_file, &right_walls, &bottom_walls, &rows,
                        &cols);

    double **Q = (double **)calloc(rows * cols, sizeof(double *));
    if (Q == NULL) {
      fprintf(stderr, "Ошибка выделения памяти\n");
      return 1;
    }

    for (int i = 0; i < rows * cols; ++i) {
      Q[i] = (double *)calloc(ACTIONS, sizeof(double));
      if (Q[i] == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
      }
    }

    int start_state = state_to_index(start_x, start_y, cols);
    int end_state = state_to_index(end_x, end_y, cols);

    q_learning(start_state, end_state, Q, right_walls, bottom_walls, rows,
               cols);

    for (int i = 0; i < rows * cols; ++i) {
      free(Q[i]);
    }
    free(Q);

    free_matrix(right_walls, rows);
    free_matrix(bottom_walls, rows);
  }

  // Освобождение памяти
  if (maze_file) free(maze_file);
  if (cave_file) free(cave_file);
  if (learning_file) free(learning_file);
  if (output_file) free(output_file);

  return 0;
}
