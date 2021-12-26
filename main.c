#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "aide_projet.c"
#include "arraylist.c"
#include "game.c"



//Fonction qui initialise un boite:
//Une boite se compose de 9 boules de couleurs différentes
//Et on a un nombre en base 3 correspondant au jeu de la carte
matchbox* init_box(uint32_t g){
    matchbox* res= malloc(sizeof(matchbox));
    res->config=g;
    //on initialise l'arraylist
    maillon* boules=malloc(sizeof(boules)*9);
    for(int i=0; i<8; i++){
        boules[i].bille=i; //couleur de la bille
        boules[i].next=&(boules[i+1]);
    }
    //Boules non jouées
    boules[8].bille=8; //8 <=> pink
    boules[8].next=NULL;
    res->free->head=&(boules[0]);
    res->free->tail=&(boules[8]);
    res->free->size=9;
    //Boules jouées
    res->taken->head=NULL;
    res->taken->tail=NULL;
    res->taken->size=0;

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
}

int main() {
    uint8_t table[3][3] = {{2, 1, 1},
                            {1, 2, 1},
                            {0, 1, 2}};

    uint32_t w = isWin(table);
    // 210122020
    return 0;
}
