#include "io.h"

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
  fprintf(stderr,
          "  -h, --height <int>         Number of rows (positive number)\n");
  fprintf(stderr,
          "  -w, --width <int>          Number of columns (positive number)\n");
  fprintf(stderr,
          "  -s, --start <x> <y>        Start position (positive numbers)\n");
  fprintf(stderr,
          "  -e, --end <x> <y>          End position (positive numbers)\n");
  fprintf(stderr, "  -c, --cave <path>          Cave file\n");
  fprintf(stderr, "  -b, --birth <int>          Birth limit (0 <= x <= 7)\n");
  fprintf(stderr, "  -d, --death <int>          Death limit (0 <= x <= 7)\n");
  fprintf(stderr,
          "  -n, --milliseconds <int>   Render frequency in ms (positive "
          "number)\n");
  fprintf(stderr, "  -l, --learning <path>      Cave file for learning\n");
  fprintf(stderr, "  -o, --output-file <path>   Output file\n");
  exit(EXIT_FAILURE);
}

void init_args(Args *args) {
  args->maze_file = NULL;
  args->start_x = 0;
  args->start_y = 0;
  args->end_x = 0;
  args->end_y = 0;
  args->height = 1;
  args->width = 1;
  args->cave_file = NULL;
  args->birth = 0;
  args->death = 0;
  args->ms = 0;
  args->learning_file = NULL;
  args->output_file = NULL;
}

void parse_args(int argc, char **argv, Args *args, Flags *flags) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--maze") == 0) {
      flags->maze_flag = 1;
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        if (!args->maze_file)
          args->maze_file = allocate_and_copy_string(argv[++i]);
        else
          i++;
      }
    } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--start") == 0) {
      flags->start_flag = 1;
      if (i + 2 < argc) {
        args->start_x = atoi(argv[++i]) - 1;
        args->start_y = atoi(argv[++i]) - 1;
        if (args->start_x < 0 || args->start_y < 0) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--end") == 0) {
      flags->end_flag = 1;
      if (i + 2 < argc) {
        args->end_x = atoi(argv[++i]) - 1;
        args->end_y = atoi(argv[++i]) - 1;
        if (args->end_x < 0 || args->end_y < 0) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) {
      flags->height_flag = 1;
      if (i + 1 < argc) {
        args->height = atoi(argv[++i]);
        if (args->height <= 0 || args->height > MAX_COLS) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
      flags->width_flag = 1;
      if (i + 1 < argc) {
        args->width = atoi(argv[++i]);
        if (args->width <= 0 || args->width > MAX_ROWS) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cave") == 0) {
      flags->cave_flag = 1;
      if (i + 1 < argc) {
        if (!args->cave_file)
          args->cave_file = allocate_and_copy_string(argv[++i]);
        else
          i++;
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--birth") == 0) {
      flags->birth_flag = 1;
      if (i + 1 < argc) {
        args->birth = atoi(argv[++i]);
        if (args->birth < 0 || args->birth > 7) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--death") == 0) {
      flags->death_flag = 1;
      if (i + 1 < argc) {
        args->death = atoi(argv[++i]);
        if (args->death < 0 || args->death > 7) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-n") == 0 ||
               strcmp(argv[i], "--milliseconds") == 0) {
      flags->milliseconds_flag = 1;
      if (i + 1 < argc) {
        args->ms = atoi(argv[++i]);
        if (args->ms < 0) print_usage(argv[0]);
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-l") == 0 ||
               strcmp(argv[i], "--learning") == 0) {
      flags->learning_flag = 1;
      if (i + 1 < argc) {
        if (!args->learning_file)
          args->learning_file = allocate_and_copy_string(argv[++i]);
        else
          i++;
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-o") == 0 ||
               strcmp(argv[i], "--output-file") == 0) {
      flags->output_flag = 1;
      if (i + 1 < argc) {
        if (!args->output_file)
          args->output_file = allocate_and_copy_string(argv[++i]);
        else
          i++;
      } else {
        print_usage(argv[0]);
      }
    } else if (strcmp(argv[i], "-q") == 0 ||
               strcmp(argv[i], "--nonrender-flag") == 0) {
      flags->nonrender_flag = 1;
    } else {
      print_usage(argv[0]);
    }
  }
}

void process_maze(Args args, Flags flags) {
  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0, cols = 0;
  bool solution[MAX_ROWS][MAX_COLS] = {false};

  if (flags.start_flag || flags.end_flag) {
    solve_maze(args.maze_file, args.start_y, args.start_x, args.end_y,
               args.end_x);
    if (!flags.nonrender_flag) {
      read_maze_from_file(args.maze_file, &right_walls, &bottom_walls, &rows,
                          &cols);
      read_maze_solution_from_file(MAZE_SOLUTION, solution);
      render_maze_solution(right_walls, bottom_walls, solution, rows, cols);
    }
  } else {
    if (!flags.nonrender_flag) {
      read_maze_from_file(args.maze_file, &right_walls, &bottom_walls, &rows,
                          &cols);
      render_maze(right_walls, bottom_walls, rows, cols);
    }
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}

void process_maze_generation(Args args, Flags flags) {
  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0, cols = 0;
  bool solution[MAX_ROWS][MAX_COLS] = {false};

  generate_maze(args.height, args.width,
                flags.output_flag ? args.output_file : SAVE_PATH);

  if (flags.start_flag || flags.end_flag) {
    solve_maze(flags.output_flag ? args.output_file : SAVE_PATH, args.start_y,
               args.start_x, args.end_y, args.end_x);
    if (!flags.nonrender_flag) {
      read_maze_from_file(flags.output_flag ? args.output_file : SAVE_PATH,
                          &right_walls, &bottom_walls, &rows, &cols);
      read_maze_solution_from_file(MAZE_SOLUTION, solution);
      render_maze_solution(right_walls, bottom_walls, solution, rows, cols);
    }
  } else {
    if (!flags.nonrender_flag) {
      read_maze_from_file(flags.output_flag ? args.output_file : SAVE_PATH,
                          &right_walls, &bottom_walls, &rows, &cols);
      render_maze(right_walls, bottom_walls, rows, cols);
    }
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}

void process_maze_learning(Args args, Flags flags) {
  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0, cols = 0;
  bool solution[MAX_ROWS][MAX_COLS] = {false};

  read_maze_from_file(args.learning_file, &right_walls, &bottom_walls, &rows,
                      &cols);
  learn_agent(right_walls, bottom_walls, rows, cols, solution, args.start_x,
              args.start_y, args.end_x, args.end_y);
  if (!flags.nonrender_flag) {
    render_maze_solution(right_walls, bottom_walls, solution, rows, cols);
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}

void process_cave_generation(Args args, Flags flags) {
  generate_cave(args.cave_file, args.birth, args.death,
                flags.milliseconds_flag ? args.ms : -1);
}

void free_args(Args *args) {
  if (args->maze_file) {
    free(args->maze_file);
    args->maze_file = NULL;
  }
  if (args->cave_file) {
    free(args->cave_file);
    args->cave_file = NULL;
  }
  if (args->learning_file) {
    free(args->learning_file);
    args->learning_file = NULL;
  }
  if (args->output_file) {
    free(args->output_file);
    args->output_file = NULL;
  }
}
