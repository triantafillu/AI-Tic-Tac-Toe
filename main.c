#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "matchboxes.h"
#include "arraylist.h"
#include "aide_projet.h"
#include "game.h"




//Fonction qui initialise un boite:
//Une boite se compose de 9 boules de couleurs différentes
//Et on a un nombre en base 3 correspondant au jeu de la carte
/*matchbox* init_box(uint32_t g)
{
    matchbox* res= malloc(sizeof(matchbox));
    res->config=g;
    char buffer[9]; 
    //On transforme l'entier en chaine de caractère
    sprintf(buffer, "%d", g);
    uint32_t empty=nb_zero(buffer); //Le nombre de cases vides
    maillon* boules=malloc(sizeof(boules)*empty); 
    for(int j=0; j<empty; j++){
        if(buffer[j]=='0'){
            boules[j].bille=j; //On met la boule correspondante à chaque case libre 
        }
    }
    boules[empty].next=NULL;
    res->free->head=&(boules[0]);
    res->free->tail=&(boules[empty]);
    res->free->size=empty;
    //Boules jouées
    res->taken->head=NULL;
    res->taken->tail=NULL;
    res->taken->size=0;

    return res;
}

uint32_t nb_zero(char* string){
    int res=0; 
    for(int i=0; i<stlen(string); i++ ){
        if(string[i]=='0'){
            res++; 
        }
    }
    return res; 
}

//Fonction qui renvoie une bille au hasard dans une boite
enum billes rand_bille(matchbox* boite){
    srand(time(NULL));
    int nb=rand()%(boite->free->size);
    int i=0;
    maillon* m=boite->free->head;
    while(i<nb && m!=NULL){
        m=m->next;
        i++;
    }
    if(m!=NULL){
        return m->bille;
    }
    else
        return -1;
}*/

int main() {
   /* uint8_t table[3][3] = {{2, 1, 1},
                            {1, 2, 1},
                            {0, 1, 2}};

    uint32_t w = isWin(table);*/

    FILE* in = fopen("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\new_game.txt", "w");
    /*FILE* out = fopen("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\gs_out.csv", "w");
    matchbox** mb = initializeMatchboxes();
    writeGameState(out, mb);
    fclose(out);

    // 210122020*/

    uint8_t g[3][3] = {{1, 2, 1}, {0, 0, 2}, {2, 0, 1}};
//
//    print_all_transformations_1d(g, in);
//    while(next_configuration(g)==0)
//    {
//        if (isValid(g))
//        {
//            print_all_transformations_1d(g, in);
//        }
//    }

    generateNewGame(in);

    //print_all_transformations_1d(g, in);
    return 0;
}
