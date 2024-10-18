#ifndef CAVE_GENERATION_H
#define CAVE_GENERATION_H

#include <unistd.h>

#include "../common/common.h"
#include "../gui/frontend.h"

#define DEAD 0
#define ALIVE 1

void generate_cave(const char *path, int birth, int death, int ms);
int alive_count(int **cave, int i, int j, int rows, int cols);
void read_cave_from_file(const char *path, int ***cave, int *rows, int *cols);

#endif
