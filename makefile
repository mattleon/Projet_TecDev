main: main.o grille.o joueur.o
	gcc -Wall -g -o main grille.o main.o joueur.o -lncurses 

main.o: main.c grille.h
	gcc -Wall -g -c main.c

grille.o: grille.c grille.h
	gcc -Wall -g -c grille.c

joueur.o: joueur.c joueur.h
	gcc -Wall -g -c joueur.c

clear:
	rm -rf *.o
