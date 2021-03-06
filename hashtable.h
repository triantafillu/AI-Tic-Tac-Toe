#ifndef PROJET_HASHTABLE_H
#define PROJET_HASHTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "aide_projet.h"

enum billes {yellow, red, green, blue, orange, purple, white, black, pink};

// yellow| red    | green
// blue  | orange | purple
// white | black  | pink

// Maillon de bille
typedef struct _maillon_billes
{
    enum billes bille;
    struct _maillon_billes *next;
}maillon_billes;

typedef struct
{
    uint32_t size;
    maillon_billes *head;
    maillon_billes *tail;
} list_billes;

typedef struct _tab_maillon
{
    maillon_billes *tab; //Un tableau de maillons
    uint32_t size_tab; //La taille du tableau de maillons
    struct _tab_maillon *next;
} tab_maillon;

typedef struct
{
    uint32_t size;
    tab_maillon *head;
    tab_maillon *tail;
} list_tab_maillons;

// Maillon de matchbox
//Une boite d'allumettes est une arraylist 
//free->est vide au début on y ajoute les billes quand on joue 
//takes sont les billes qui sont disponible pour jouer 
//config-> nb en base 3 qui définit la configuration de la boite d'allumettes 
//modifications-> tableau des nombres en base 3 des configurations possible de la boite d'allumettes 
typedef struct _maillon_mb
{
    uint32_t config;

    list_billes *free;
    list_billes *taken;
    list_tab_maillons *ltm;

    uint32_t modifications[8];

    struct _maillon_mb *next;
}maillon_mb;
//Liste de boites d'allumettes 
//Servira dans le tableau de hachage 
typedef struct
{
    uint32_t size;
    maillon_mb *head;
    maillon_mb *tail;
} list_mb;
//Tableau de hachage 
//Servira à stocker les différentes boites d'allumettes selon leur hachecode 
typedef struct
{
    list_mb **tab;
    uint32_t size;
} matchboxes;

maillon_billes *newMaillonBilles(enum billes b);
list_billes *newListBilles();
maillon_billes * removeHeadBilles(list_billes *l);
void addHeadBilles(list_billes *l, maillon_billes *m);
tab_maillon* newTabMaillon(uint32_t size);
list_tab_maillons * newListTabMaillon();
void addHeadLTM(list_tab_maillons *l, tab_maillon *m);
tab_maillon * removeHeadLTM(list_tab_maillons *l);
void enlargeFree(maillon_mb *mb, uint32_t size);
maillon_mb *newMaillonMb(uint32_t config);
void addHeadMb(maillon_mb* mb, enum billes b);
enum billes removeBilleMb(maillon_mb* mb);
void freeMb(maillon_mb *mb);
void addHeadMbHash(list_mb *l, uint32_t config);
list_mb *newListMB();
matchboxes* newMatchboxes(uint32_t size);
uint32_t hashing(matchboxes *mb, uint32_t config);
void addHeadHash(matchboxes *mb, uint32_t config);
void freeHashTable(matchboxes *th);
enum billes getBille(uint32_t ind);
maillon_mb *findMb(matchboxes *th, uint32_t config);
uint32_t countBilles(list_billes *l, enum billes b);
uint32_t getBilleIndex(enum billes b);
maillon_mb *findBaseConfiguration(matchboxes *th, uint32_t config);

#endif //PROJET_HASHTABLE_H
