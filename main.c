#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "grille.h"
#include "joueur.h"
#include <time.h>

/**
*	@file main.c
*	@brief fonction main
*	@author LEON Matthieu
*	@date 13/04/2015
*/

/** @brief mise en relation des fonctions pour gerer le jeux
*/	
int main(int argc, char **argv)
{
	char **objets=(char **)malloc(7*sizeof(char *));
	objets[0]="Dagues";
	objets[1]="Epee";
	objets[2]="Bout de bois";
	objets[3]="Bouclier";
	objets[4]="Veste";
	objets[5]="Cotte de maille";
	objets[6]="Casque";
	
	grid * g = charge_file(argv[1]);
	player * p = init_player(1, 1, 50, 50, 0, 0, 0, 10);

	initscr();
	noecho();		
	curs_set(0);	//n'affiche pas le curseur
	display_grid_lnc(g);
	square(8, p->x, p->y);
	int key='s';
	player_data(p, g);
	
	while ((key!='a')&&(p->hp>0)&&(g->tab[p->x][p->y]!=6))
	{	
		key=getch();

		move_player(p, g, key);
		test_square(p, g);
		player_data(p, g);
	}
		
	delete_player(p);
	delete_Grid(g);
	clear();
	mvprintw(5,5, "OVER");
	refresh();
	napms(500);
	endwin();
	return 0;
}	

