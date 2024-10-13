#include "maze_solving.h"

void init_queue(Queue *q) { q->front = q->rear = -1; }

bool is_empty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, Point p) {
  if (is_empty(q)) {
    q->front = q->rear = 0;
  } else {
    q->rear++;
  }
  q->data[q->rear] = p;
}

Point dequeue(Queue *q) {
  Point p = q->data[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = -1;
  } else {
    q->front++;
  }
  return p;
}

void solve_maze(char *path, int start_row, int start_col, int end_row,
                int end_col) {
  int **right_walls = NULL;
  int **bottom_walls = NULL;
  int rows = 0, cols = 0;

  read_maze_from_file(path, &right_walls, &bottom_walls, &rows, &cols);

  Point prev[MAX_ROWS][MAX_COLS];
  bool solution_path[MAX_ROWS][MAX_COLS] = {false};

  int shortest_path = bfs(right_walls, bottom_walls, start_row, start_col,
                          end_row, end_col, rows, cols, prev);

  if (shortest_path != -1) {
    mark_solution_path(prev, solution_path, start_row, start_col, end_row,
                       end_col);
    write_maze_solution_to_file(SOLUTION_PATH, solution_path, rows, cols);
    //            printMazeWithSolution(solution_path, rows, cols);
//    init_ncurses();
//    start_color();
//    init_colorpairs();
//    atexit(cleanup);
//
//    while (1) {
//      draw_maze_solution(right_walls, bottom_walls, solution_path, rows, cols);
//      refresh();
//
//      int ch = getch();
//      if (ch == 'q') {
//        break;
//      }
//    }
  } else {
    printf("No path found\n");
  }

  free_matrix(right_walls, rows);
  free_matrix(bottom_walls, rows);
}

int bfs(int **right_walls, int **bottom_walls, int start_row, int start_col,
        int end_row, int end_col, int rows, int cols,
        Point prev[MAX_ROWS][MAX_COLS]) {
  bool visited[MAX_ROWS][MAX_COLS] = {false};
  Queue q;
  init_queue(&q);

  Point start = {start_row, start_col, 0};
  enqueue(&q, start);
  visited[start_row][start_col] = true;

  while (!is_empty(&q)) {
    Point current = dequeue(&q);

    if (current.row == end_row && current.col == end_col) {
      return current.dist;
    }

    // right
    if (current.col + 1 < cols && !right_walls[current.row][current.col] &&
        !visited[current.row][current.col + 1]) {
      Point next = {current.row, current.col + 1, current.dist + 1};
      enqueue(&q, next);
      visited[current.row][current.col + 1] = true;
      prev[current.row][current.col + 1] = current;
    }

    // left
    if (current.col - 1 >= 0 && !right_walls[current.row][current.col - 1] &&
        !visited[current.row][current.col - 1]) {
      Point next = {current.row, current.col - 1, current.dist + 1};
      enqueue(&q, next);
      visited[current.row][current.col - 1] = true;
      prev[current.row][current.col - 1] = current;
    }

    // down
    if (current.row + 1 < rows && !bottom_walls[current.row][current.col] &&
        !visited[current.row + 1][current.col]) {
      Point next = {current.row + 1, current.col, current.dist + 1};
      enqueue(&q, next);
      visited[current.row + 1][current.col] = true;
      prev[current.row + 1][current.col] = current;
    }

    // up
    if (current.row - 1 >= 0 && !bottom_walls[current.row - 1][current.col] &&
        !visited[current.row - 1][current.col]) {
      Point next = {current.row - 1, current.col, current.dist + 1};
      enqueue(&q, next);
      visited[current.row - 1][current.col] = true;
      prev[current.row - 1][current.col] = current;
    }
  }

  return -1;  // no path found
}

void mark_solution_path(Point prev[MAX_ROWS][MAX_COLS],
                        bool solution_path[MAX_ROWS][MAX_COLS], int start_row,
                        int start_col, int end_row, int end_col) {
  if (end_row == start_row && end_col == start_col) {
    solution_path[start_row][start_col] = true;
    return;
  }
  mark_solution_path(prev, solution_path, start_row, start_col,
                     prev[end_row][end_col].row, prev[end_row][end_col].col);
  solution_path[end_row][end_col] = true;
}

void printMazeWithSolution(bool solutionPath[MAX_ROWS][MAX_COLS], int rows,
                           int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (solutionPath[i][j]) {
        printf("* ");
      } else {
        printf(". ");
      }
    }
    printf("\n");
  }
}

void write_maze_solution_to_file(const char *path, bool solution[MAX_ROWS][MAX_COLS], int rows, int cols) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    printf("Error opening file %s\n", path);
    return;
  }

  fprintf(file, "%d %d\n", rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (solution[i][j]) fprintf(file, "1 ");
      else fprintf(file, "0 ");
    }
    fprintf(file, "\n");
  }

  fclose(file);
  printf("Maze solution successfully written to file %s\n", path);
}
