#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/**
*	@file grille.c
*	@brief Fonctions de traitement de la grille 
*	@author LEON Mathtieu
*	@date 13/04/2015
*/


/**	@brief creer une nouvelle grille
*	@param n nombre de ligne de la grille
*	@param m nomnre de colonnes de la grille
*	@return return un pointeur sur grille
*/	
grid * create_Grid(int n, int m)
{
	int i;
	grid * g = (grid*)malloc(sizeof(grid));
	g->tab=(int**)malloc(n*sizeof(int*));
	if(g->tab == NULL)
		exit(1);
	for(i=0; i<n; i++)
	{
		g->tab[i] = (int*)calloc(m,sizeof(int));
		if(g->tab[i] == NULL)
			exit(1);
	}
	g->lines = n;
	g->columns = m;
	return g;
}

/**	@brief libere la mémoire utilisée par une grille
*	@param g pointeur sur la grille a effacer
*/
void delete_Grid(grid * g)
{
	int i;
	for(i=0; i<g->lines; i++)
			free(g->tab[i]);
	free(g->tab);
}

/** @brief charge la grille contenue dans un fichier texte
* 	@param file fichier texte à convertir en grille
* 	@return renvoie un pointeur sur la grille generee par le fichier
*/
grid * charge_file(char * file)
{
	char *mode = "r";

	FILE *fd;
	if((fd = fopen(file,mode)) == NULL)
	{
		perror("Erreur sur le fichier entrée");
		exit(1); 
	}
	int r, n, m, i, j;
	fscanf(fd,"%d %d", &n, &m);

	grid * g =create_Grid(n,m);
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			fscanf(fd, "%d ", &r);
			g->tab[i][j] = r;
		}
	}
	fclose(fd);
	return g;
}

/** @brief affiche la grille en ASCII sur le terminal
* 	@param g pointeur sur la grille a afficher
*/
void display_Grid_ascii(grid * g)
{
	int i, j, gij;

	for(j=0; j<g->columns+2; j++)
		printf("-");
	printf("\n");

	for(i=0; i<g->lines; i++)
	{	
		printf("|");
		for(j=0; j<g->columns; j++)
		{
			gij = g->tab[i][j];
			switch (gij) {
				case 0:	printf(" ");
						break;
				case 1:	printf("#");
						break;
				case 2: printf("+");
						break;
				case 3: printf("-");
						break;
				case 4: printf("H");
						break;
				case 5: printf("b");
						break;
				case 6: printf("E");
						break;
				case 7: printf("U");
						break;
				default: printf(" ");
						break;
			}

		}
		printf("|\n");
	}

	for(j=0; j<g->columns+2; j++)
		printf("-");
	printf("\n");
}

/** @brief affiche un caractere en fonction du contenu de la case verifiee
* 	@param sq contenu de la case a verifier
* 	@param i coordonnee de la ligne
* 	@param j coordonnee de la colonne 
*/
void square(int sq, int i, int j)
{
	switch (sq) 
	{
	case 0:	mvprintw(i+2, j+2," ");		
			break;
	case 1:	mvprintw(i+2, j+2,"#");		//Mur
			break;
	case 2: mvprintw(i+2, j+2,"+");		//Soigne
			break;
	case 3: mvprintw(i+2, j+2,"-");		//piège
			break;
	case 4: mvprintw(i+2, j+2,"a");		//Augmente l'attaque
			break;
	case 5: mvprintw(i+2, j+2,"b");		//Augmente le bouclier
			break;
	case 6:	mvprintw(i+2, j+2,"E");		//Sortie
			break;
	case 7: mvprintw(i+2, j+2," ");		//début
			break;
	case 8: mvprintw(i+2, j+2,"P");		//Joueur 
			break;
	case 9: mvprintw(i+2, j+2,"~");		//Objet aléatoire (En déevloppement)
			break;
	default: mvprintw(i+2, j+2," ");
			break;
	}
}

/** @brief affiche la grille en ncurses sur le terminal
* 	@param g pointeur sur la grille a afficher
*/
void display_grid_lnc(grid * g)
{
	int i, j, gij;
	for(i = 0; i < g->lines; i++)
	{
		for(j=0; j<g->columns; j++)
		{
			gij = g->tab[i][j];
			square(gij, i, j);
			
		}
	}
	refresh();
}

/** @brief verifie si une case est accessible
* 	@param g pointeur sur la grille a afficher
* 	@param square contenue de la case verifiee
*/
int empty_square(int square, grid * g)
{
	if(square == 1)
		return 0;
	return 1;
}

