#include "frontend.h"

void init_ncurses() {
  initscr();
  noecho();
  timeout(0);
  curs_set(0);
  keypad(stdscr, TRUE);
}

void cleanup() {
  wclear(stdscr);
  endwin();
  printf("The program is completed. The terminal has been restored.\n");
}

void draw_maze(int** right_walls, int** bottom_walls, int rows, int cols) {
    attron(COLOR_PAIR(CYAN_FONT));
  for (int j = 1; j < cols * 2; j++) {
    mvaddch(0, j, '_');
  }
  for (int i = 0; i < rows; i++) {
    mvaddch(i + 1, 0, '|');
    for (int j = 0; j < cols; j++) {
      if (right_walls[i][j]) {
        if (bottom_walls[i][j]) {
          mvaddch(i + 1, j * 2 + 1, '_');
          mvaddch(i + 1, j * 2 + 2, '|');
        } else {
          mvaddch(i + 1, j * 2 + 1, ' ');
          mvaddch(i + 1, j * 2 + 2, '|');
        }
      } else {
        if (bottom_walls[i][j]) {
          mvaddch(i + 1, j * 2 + 1, '_');
          mvaddch(i + 1, j * 2 + 2, '_');
        } else {
          mvaddch(i + 1, j * 2 + 1, ' ');
          mvaddch(i + 1, j * 2 + 2, ' ');
        }
      }
    }
    mvaddch(i + 1, cols * 2, '|');
  }
    attroff(COLOR_PAIR(CYAN_FONT));
}

void draw_maze_solution(int** right_walls, int** bottom_walls, bool solution_path[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int j = 1; j < cols * 2; j++) {
    mvaddch(0, j, '_');
  }
  for (int i = 0; i < rows; i++) {
    mvaddch(i + 1, 0, '|');
    for (int j = 0; j < cols; j++) {
      if (right_walls[i][j]) {
        if (bottom_walls[i][j]) {
            if (solution_path[i][j]) {
                attron(COLOR_PAIR(GREEN_FONT));
                attron(A_UNDERLINE);
                mvaddch(i + 1, j * 2 + 1, '*');
                attroff(A_UNDERLINE);
                attroff(COLOR_PAIR(GREEN_FONT));
                
//                attron(COLOR_PAIR(CYAN_FONT));
                mvaddch(i + 1, j * 2 + 2, '|');
//                attroff(COLOR_PAIR(CYAN_FONT));
            }
            else {
//                attron(COLOR_PAIR(CYAN_FONT));
                mvaddch(i + 1, j * 2 + 1, '_');
                mvaddch(i + 1, j * 2 + 2, '|');
//                attroff(COLOR_PAIR(CYAN_FONT));
            }
        } else {
            if (solution_path[i][j]) {
                attron(COLOR_PAIR(GREEN_FONT));
                mvaddch(i + 1, j * 2 + 1, '*');
                attroff(COLOR_PAIR(GREEN_FONT));
                
//                attron(COLOR_PAIR(CYAN_FONT));
                mvaddch(i + 1, j * 2 + 2, '|');
//                attroff(COLOR_PAIR(CYAN_FONT));
            }
            else {
//                attron(COLOR_PAIR(CYAN_FONT));
                mvaddch(i + 1, j * 2 + 1, ' ');
                mvaddch(i + 1, j * 2 + 2, '|');
//                attroff(COLOR_PAIR(CYAN_FONT));
            }
        }
      } else {
        if (bottom_walls[i][j]) {
            if (solution_path[i][j]) {
                attron(COLOR_PAIR(GREEN_FONT));
                attron(A_UNDERLINE);
                mvaddch(i + 1, j * 2 + 1, '*');
                mvaddch(i + 1, j * 2 + 2, ' ');
                attroff(A_UNDERLINE);
                attroff(COLOR_PAIR(GREEN_FONT));
            }
            else {
//                attron(COLOR_PAIR(CYAN_FONT));
                mvaddch(i + 1, j * 2 + 1, '_');
                mvaddch(i + 1, j * 2 + 2, '_');
//                attroff(COLOR_PAIR(CYAN_FONT));
            }
        } else {
            if (solution_path[i][j]) {
                attron(COLOR_PAIR(GREEN_FONT));
                mvaddch(i + 1, j * 2 + 1, '*');
                mvaddch(i + 1, j * 2 + 2, ' ');
                attroff(COLOR_PAIR(GREEN_FONT));
            }
            else {
//                attron(COLOR_PAIR(CYAN_FONT));
                mvaddch(i + 1, j * 2 + 1, ' ');
                mvaddch(i + 1, j * 2 + 2, ' ');
//                attroff(COLOR_PAIR(CYAN_FONT));
            }
        }
      }
    }
    mvaddch(i + 1, cols * 2, '|');
  }
}

void draw_cave(int **cave, int rows, int cols) {
    attron(COLOR_PAIR(RED));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if (cave[i][j]) {
            mvaddstr(i + 1, j * 2 + 1, "  ");
          }
        }
      }
    attroff(COLOR_PAIR(RED));
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
