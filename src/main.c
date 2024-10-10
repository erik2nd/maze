#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

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
  fprintf(stderr, "Использование: %s [опции]\n", program_name);
  fprintf(stderr, "Опции:\n");
  fprintf(stderr,
          "  -m, --maze <файл>         Файл с лабиринтом (необязательный)\n");
  fprintf(stderr,
          "  -s, --start <x> <y>       Начальная позиция (два целых числа)\n");
  fprintf(stderr,
          "  -e, --end <x> <y>         Конечная позиция (два целых числа)\n");
  fprintf(stderr, "  -h, --height <int>        Высота\n");
  fprintf(stderr, "  -w, --width <int>         Ширина\n");
  fprintf(stderr, "  -c, --cave <файл>         Файл с пещерой\n");
  fprintf(stderr, "  -b, --birth <int>         Рождение\n");
  fprintf(stderr, "  -d, --death <int>         Смерть\n");
  fprintf(stderr, "  -n, --milliseconds <int>  Миллисекунды\n");
  fprintf(stderr, "  -l, --learning <файл>     Файл для обучения\n");
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
        start_x = atoi(argv[++i]);
        start_y = atoi(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--end") == 0) {
      flags.end_flag = 1;
      if (i + 2 < argc) {
        end_x = atoi(argv[++i]);
        end_y = atoi(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) {
      flags.height_flag = 1;
      if (i + 1 < argc) {
        height = atoi(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
      flags.width_flag = 1;
      if (i + 1 < argc) {
        width = atoi(argv[++i]);
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
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--death") == 0) {
      flags.death_flag = 1;
      if (i + 1 < argc) {
        death = atoi(argv[++i]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-n") == 0 ||
               strcmp(argv[i], "--milliseconds") == 0) {
      flags.milliseconds_flag = 1;
      if (i + 1 < argc) {
        milliseconds = atoi(argv[++i]);
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

  generate_maze(width, height, flags.output_flag ? output_file : SAVE_PATH);

  // Освобождение памяти
  if (maze_file) free(maze_file);
  if (cave_file) free(cave_file);
  if (learning_file) free(learning_file);
  if (output_file) free(output_file);

  return 0;
}
