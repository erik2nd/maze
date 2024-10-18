#include "io/io.h"

int main(int argc, char *argv[]) {
  Args args;
  init_args(&args);
  Flags flags = {0};

  parse_args(argc, argv, &args, &flags);

  if (flags.maze_flag)
    if (args.maze_file)
      process_maze(args, flags);
    else
      process_maze_generation(args, flags);
  else if (flags.learning_flag)
    process_maze_learning(args, flags);
  else if (flags.cave_flag)
    process_cave_generation(args, flags);

  free_args(&args);

  return 0;
}
