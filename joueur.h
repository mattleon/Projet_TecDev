#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct{
		int x;
		int y;
		int hp;
		int hp_max;
		int def;
		int att;
		int bouclier;
		char **inventory;
}player;

player * init_player(int x, int y, int hp, int hp_max, int def, int att, int bouclier, int inventory_size);
void delete_player(player * p);
void move_player(player * p, grid * g, int key);
void test_square(player * p, grid * g);
void player_data(player * p, grid * g);
void open_door(player * p, grid * g);
int rand_n(int n);
void objet_alea(player * p, grid * g, char *tab);



#endif
