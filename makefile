main: main.o aide_projet.o game.o matchboxes.o hashtable.o
	gcc -o main main.o aide_projet.o game.o hashtable.o matchboxes.o 
main.o: main.c aide_projet.c game.c hashtable.c matchboxes.c
	gcc -c -Wall main.c  
aide_projet.o: aide_projet.c 
	gcc -c -Wall aide_projet.c 
game.o: game.c 
	gcc -c -Wall game.c 
hashtable.o: hashtable.c 
	gcc -c -Wall hashtable.c 
matchboxes.o: matchboxes.c 
	gcc -c -Wall matchboxes.c 

