#ifndef IO_H
#define IO_H

#include <string.h>

#include "../cave/cave_generation.h"
#include "../common/common.h"
#include "../gui/frontend.h"
#include "../maze/maze_generation.h"
#include "../maze/maze_learning.h"
#include "../maze/maze_solving.h"

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

void process_maze(Args args, Flags flags);
void process_maze_generation(Args args, Flags flags);
void process_maze_learning(Args args, Flags flags);
void process_cave_generation(Args args, Flags flags);

char *allocate_and_copy_string(const char *str);
void print_usage(char *program_name);

#endif
