#ifndef __GRID_H__
#define __GRID_H__

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#define MAX_LINE 10

typedef struct {int **tab; int lines; int columns;}grid;

grid * create_Grid(int n, int m);
grid * charge_file(char *file);
void delete_Grid(grid * g);
void display_Grid_ascii(grid * g);
void display_grid_lnc(grid * g);
void square(int sq, int i, int j);
int empty_square(int square, grid * g);

#endif
