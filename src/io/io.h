#ifndef IO_H
#define IO_H

#include <string.h>

#include "../common/common.h"

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
  int nonrender_flag;
} Flags;

typedef struct {
  char *maze_file;
  int start_x, start_y;
  int end_x, end_y;
  int height;
  int width;
  char *cave_file;
  int birth;
  int death;
  int ms;
  char *learning_file;
  char *output_file;
} Args;

void parse_args(int argc, char **argv, Args *args, Flags *flags);
void free_args(Args *args);
void init_args(Args *args);
char *allocate_and_copy_string(const char *str);
void print_usage(char *program_name);

#endif
