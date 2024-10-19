#include "frontend.h"

void init_render() {
  init_ncurses();
  start_color();
  init_colorpairs();
  atexit(cleanup);
}

void init_ncurses() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
}

void cleanup() {
  wclear(stdscr);
  endwin();
  printf("The program is completed. The terminal has been restored.\n");
}

void draw_maze(int** right_walls, int** bottom_walls, int rows, int cols) {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int offset_y = (max_y - rows - 1) / 2;
  int offset_x = (max_x - cols * 2) / 2;

  for (int j = 1; j < cols * 2; j++) {
    mvaddch(offset_y, offset_x + j, '_');
  }

  for (int i = 0; i < rows; i++) {
    mvaddch(offset_y + i + 1, offset_x, '|');
    for (int j = 0; j < cols; j++) {
      if (right_walls[i][j]) {
        if (bottom_walls[i][j]) {
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '_');
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '|');
        } else {
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, ' ');
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '|');
        }
      } else {
        if (bottom_walls[i][j]) {
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '_');
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '_');
        } else {
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, ' ');
          mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, ' ');
        }
      }
    }
    mvaddch(offset_y + i + 1, offset_x + cols * 2, '|');
  }
}

void draw_maze_solution(int** right_walls, int** bottom_walls,
                        bool solution_path[MAX_ROWS][MAX_COLS], int rows,
                        int cols) {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int offset_y = (max_y - rows - 1) / 2;
  int offset_x = (max_x - cols * 2) / 2;

  for (int j = 1; j < cols * 2; j++) {
    mvaddch(offset_y, offset_x + j, '_');
  }

  for (int i = 0; i < rows; i++) {
    mvaddch(offset_y + i + 1, offset_x, '|');
    for (int j = 0; j < cols; j++) {
      if (right_walls[i][j]) {
        if (bottom_walls[i][j]) {
          if (solution_path[i][j]) {
            attron(COLOR_PAIR(GREEN_FONT));
            attron(A_UNDERLINE);
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '*');
            attroff(A_UNDERLINE);
            attroff(COLOR_PAIR(GREEN_FONT));
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '|');
          } else {
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '_');
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '|');
          }
        } else {
          if (solution_path[i][j]) {
            attron(COLOR_PAIR(GREEN_FONT));
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '*');
            attroff(COLOR_PAIR(GREEN_FONT));
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '|');
          } else {
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, ' ');
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '|');
          }
        }
      } else {
        if (bottom_walls[i][j]) {
          if (solution_path[i][j]) {
            attron(COLOR_PAIR(GREEN_FONT));
            attron(A_UNDERLINE);
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '*');
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, ' ');
            attroff(A_UNDERLINE);
            attroff(COLOR_PAIR(GREEN_FONT));
          } else {
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '_');
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, '_');
          }
        } else {
          if (solution_path[i][j]) {
            attron(COLOR_PAIR(GREEN_FONT));
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, '*');
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, ' ');
            attroff(COLOR_PAIR(GREEN_FONT));
          } else {
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 1, ' ');
            mvaddch(offset_y + i + 1, offset_x + j * 2 + 2, ' ');
          }
        }
      }
    }
    mvaddch(offset_y + i + 1, offset_x + cols * 2, '|');
  }
}

void draw_cave(int** cave, int rows, int cols) {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int offset_y = (max_y - rows) / 2;
  int offset_x = (max_x - cols * 2) / 2;

  attron(COLOR_PAIR(CYAN));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!cave[i][j]) {
        mvaddstr(offset_y + i, offset_x + j * 2, "  ");
      }
    }
  }
  attroff(COLOR_PAIR(CYAN));
}

void print_cave_message(int rows) {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  const char* message = "This is the final state";

  int offset_y = (max_y - rows) / 2;
  int offset_x = (max_x - 23) / 2;

  mvaddstr(offset_y + rows + 1, offset_x, message);
}

void render_maze(int** right_walls, int** bottom_walls, int rows, int cols) {
  init_render();
  draw_maze(right_walls, bottom_walls, rows, cols);
  refresh();
  getch();
}

void render_maze_solution(int** right_walls, int** bottom_walls,
                          bool solution_path[MAX_ROWS][MAX_COLS], int rows,
                          int cols) {
  init_render();
  draw_maze_solution(right_walls, bottom_walls, solution_path, rows, cols);
  refresh();
  getch();
}

void init_colorpairs() {
  for (int color = 0; color <= 7; color++) {
    init_pair(color, curs_color(color), curs_color(color));
  }
  for (int color = 8; color <= 13; color++) {
    init_pair(color, curs_color(color - 7), COLOR_BLACK);
  }
}

short curs_color(int color) {
  short res = 0;
  switch (7 & color) { /* RGB */
    case 0:            /* 000 */
      res = (COLOR_BLACK);
      break;
    case 1: /* 001 */
      res = (COLOR_BLUE);
      break;
    case 2: /* 010 */
      res = (COLOR_GREEN);
      break;
    case 3: /* 011 */
      res = (COLOR_CYAN);
      break;
    case 4: /* 100 */
      res = (COLOR_RED);
      break;
    case 5: /* 101 */
      res = (COLOR_MAGENTA);
      break;
    case 6: /* 110 */
      res = (COLOR_YELLOW);
      break;
    case 7: /* 111 */
      res = (COLOR_WHITE);
      break;
  }
  return res;
}
