#include <stdio.h>
#include <stdlib.h>

#include "cave/cave.h"
#include "gui/frontend.h"
#include "io/io.h"
#include "maze/maze.h"
#include "maze/maze_learning.h"
#include "maze/maze_solving.h"

int main(int argc, char *argv[]) {
  Args args;
  init_args(&args);
  Flags flags = {0};

  parse_args(argc, argv, &args, &flags);

  printf("Maze file: %s\n",
         flags.maze_flag ? (args.maze_file ? args.maze_file : "не указан")
                         : "не указан");
  printf("Start: (%d, %d)\n", args.start_x, args.start_y);
  printf("End: (%d, %d)\n", args.end_x, args.end_y);
  printf("Height: %d\n", args.height);
  printf("Width: %d\n", args.width);
  printf("Cave file: %s\n", flags.cave_flag ? args.cave_file : "не указан");
  printf("Birth: %d\n", args.birth);
  printf("Death: %d\n", args.death);
  printf("Milliseconds: %d\n", args.ms);
  printf("Learning file: %s\n",
         flags.learning_flag ? args.learning_file : "не указан");
  printf("Output file: %s\n",
         flags.output_flag ? args.output_file : "не указан");
  printf("Not render: %d\n", flags.nonrender_flag);

  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0, cols = 0;
  bool solution[MAX_ROWS][MAX_COLS] = {false};

  if (flags.maze_flag) {
    if (args.maze_file) {
      if (flags.start_flag || flags.end_flag) {
        solve_maze(args.maze_file, args.start_y, args.start_x, args.end_y,
                   args.end_x);
        if (!flags.nonrender_flag) {
          read_maze_from_file(args.maze_file, &right_walls, &bottom_walls,
                              &rows, &cols);
          read_maze_solution_from_file(MAZE_SOLUTION, solution);
          render_maze_solution(right_walls, bottom_walls, solution, rows, cols);
        }
      } else {
        if (!flags.nonrender_flag) {
          read_maze_from_file(args.maze_file, &right_walls, &bottom_walls,
                              &rows, &cols);
          render_maze(right_walls, bottom_walls, rows, cols);
        }
      }
    } else {
      if (flags.start_flag || flags.end_flag) {
        generate_maze(args.height, args.width,
                      flags.output_flag ? args.output_file : SAVE_PATH);
        solve_maze(flags.output_flag ? args.output_file : SAVE_PATH,
                   args.start_y, args.start_x, args.end_y, args.end_x);
        if (!flags.nonrender_flag) {
          read_maze_from_file(flags.output_flag ? args.output_file : SAVE_PATH,
                              &right_walls, &bottom_walls, &rows, &cols);
          read_maze_solution_from_file(MAZE_SOLUTION, solution);
          render_maze_solution(right_walls, bottom_walls, solution, rows, cols);
        }
      } else {
        generate_maze(args.height, args.width,
                      flags.output_flag ? args.output_file : SAVE_PATH);
        if (!flags.nonrender_flag) {
          read_maze_from_file(flags.output_flag ? args.output_file : SAVE_PATH,
                              &right_walls, &bottom_walls, &rows, &cols);
          render_maze(right_walls, bottom_walls, rows, cols);
        }
      }
    }
  } else if (flags.cave_flag) {
    generate_cave(args.cave_file, args.birth, args.death);
  } else if (flags.learning_flag) {
    read_maze_from_file(args.learning_file, &right_walls, &bottom_walls, &rows,
                        &cols);
    learn_agent(right_walls, bottom_walls, rows, cols, solution, args.start_x,
                args.start_y, args.end_x, args.end_y);
    if (!flags.nonrender_flag) {
      render_maze_solution(right_walls, bottom_walls, solution, rows, cols);
    }
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
  free_args(&args);

  return 0;
}
