#include "joueur.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/**
*	@file joueur.c
*	@brief fonction de traitement du joueur
*	@author LEON Matthieu
*	@date 13/04/2015
*/

/** @brief creer un joueur avec ses caracteristiques de base
*	@param g pointeur de la grille sur la quelle le joueur va se déplacer *
* 	@param x abscisse d'origine du joueur
* 	@param y ordonnee d'origine du joueur
* 	@param hp point de vie du joueur
* 	@param hp_max point de vie maximum du joueur
* 	@param def points de défense du joueur
* 	@param att points d'attaque du joueur
* 	@param inventory_size taille de l'inventaire du joueur
* 	@return renvoie un pointeur sur le joueur 
*/
player * init_player(int x, int y, int hp, int hp_max, int def, int att, int bouclier, int inventory_size)
{
	player * p=(player *)malloc(sizeof(player));
	p->x = x;
	p->y = y;
	p->hp = hp;
	p->hp_max = hp_max;
	p->def = def;
	p->att = att;
	p->bouclier = bouclier;
	p->inventory=(char **)malloc(inventory_size*sizeof(char*));
	p->inventory[0]="Epee";
	return p;
}

/** @brief libere la mémoire allouée pour un joueur
*	@param p pointeur sur le joueur a effacer
*/	
void delete_player(player * p)
{
	free(p->inventory);
	free(p);
}

/** @brief modifie les coordonnees du joueur en fonction d'une cle entree
* 	@param p pointeur sur le joueur
* 	@param g pointeur sur la grille
* 	@param k cle entree par le joueur
*/	
void move_player(player * p, grid * g, int k)
{
	int x2 = p->x, y2 = p->y;

	switch (k)
	{
		case 'q':	if(empty_square(g->tab[p->x][p->y-1], g))
					{
						g->tab[p->x][p->y]=0;
						p->y-=1;
						
					}
					break;

		case 'z':	if(empty_square(g->tab[p->x-1][p->y], g))
					{
						g->tab[p->x][p->y]=0;
						p->x-=1;
					}
					break;

		case 'd':	if(empty_square(g->tab[p->x][p->y+1], g))
					{
						g->tab[p->x][p->y]=0;
						p->y+=1;
					}
					break;
		case 's':	if(empty_square(g->tab[p->x+1][p->y], g))
					{
						g->tab[p->x][p->y]=0;
						p->x+=1;
					}
					break;
		default:	break;
	}
	square(g->tab[x2][y2], x2, y2);
	square(8, p->x, p->y);
}

/** @brief affiche les donnees sur le joueur (vie, def, att, inventaire)
* 	@param p pointeur sur le joueur
* 	@param g pointeur sur la grille
*/	
void player_data(player * p, grid * g)
{
 	mvprintw(4,(g->columns)+5,"PV:   %d / %d", p->hp, p->hp_max);
	mvprintw(5,(g->columns)+5,"DEF:  %d   ATT: %d", p->def, p->att);
	mvprintw(6,(g->columns)+5,"Bouclier: %d", p->bouclier);
	int i;
	//for (i=0; i<10; i++)
		//mvprintw(7+i,(g->columns)+5, "Inventaire : %s", p->inventory[i]);
	refresh();
}

/** @brief test et applique les effets d'une case sur le joueur
* 	@param p pointeur sur le joueur
* 	@param g pointeur sur la grille
*/	
void test_square(player * p, grid * g)
{
	switch(g->tab[p->x][p->y])
	{
		case 2: p->hp+=1;
				if(p->hp>p->hp_max)
					p->hp=p->hp_max;
				break;
		case 3:  
				if (p->bouclier>0)
				{
					int tmp=(p->bouclier)-rand_n(5);
					p->bouclier=tmp;
					if (p->bouclier<0)
					{
						p->hp+=p->bouclier;
						p->bouclier=0;
					}
						
				}
				else
					p->hp-=1;
				if(p->hp<0)
					p->hp=0;
				break;
		case 4: p->att+=1;
				break;
		case 5: p->bouclier+=rand_n(5);
				break;
		default:break;
	}
}


/** @brief Retourne un resultat aleatoire de 0 à la taille max du tableau d'objets
*		@param n taille max du tableau
*/
int rand_n(int n) 
{ 
    int partSize   = 1 + (n == RAND_MAX ? 0 : (RAND_MAX - n) / (n + 1)); 
    int maxUsefull = partSize * n + (partSize - 1); 
    int draw; 
  
    do { 
        draw = rand(); 
    } while (draw > maxUsefull); 
  
    return draw / partSize; 
}


/** @brief Test et ajoute un objet à l'inventaire du joueur
*		@param p pointeur sur le joueur
*		@param g pointeur sur la grille
*		@param tab pointeur sur tableau d'objets
*/
/*void objet_alea(player * p, grid * g, char **tab) {
	p->inventory[0]=tab[rand_n(6)];
}*/
	
		
	
	
