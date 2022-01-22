#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "matchboxes.h"
#include "hashtable.h"
#include "aide_projet.h"

/*
 *
 * Functions related to arraylist and hash table data structures
 *
 */


//-----------------------------Billes (liste)-------------------------------------
// New bille
maillon_billes *newMaillonBilles(enum billes b)
{
    maillon_billes *m = malloc(sizeof (maillon_billes));
    if (m == NULL)
    {
        assert(0);
    }
    m->bille = b;
    return m;
}

// New liste containing billes
list_billes *newListBilles()
{
    list_billes *r = malloc(sizeof (list_billes));
    if (r == NULL)
    {
        assert(0);
    }
    r->size = 0;
    r->head = NULL;
    r->tail = NULL;
    return r;
}

// Delete head of list with billes
maillon_billes * removeHeadBilles(list_billes *l)
{
    maillon_billes *t = l->head;

    l->head = l->head->next;
    l->size -= 1;

    if(l->size == 0)
    {
        l->head = NULL;
    }

    return t;
}

// Add a new bille to list
void addHeadBilles(list_billes *l, maillon_billes *m)
{
    //maillon_billes *m = newMaillonBilles(b);
    assert(m!=NULL);
    m->next = l->head;
    l->head = m;
    if (l->size == 0)
    {
        l->tail = m;
    }
    l->size += 1;
}

//----------------Free memory (arraylist)----------------
tab_maillon* newTabMaillon(uint32_t size)
{
    uint32_t i;
    tab_maillon *t = malloc(sizeof(tab_maillon));
    assert(t != NULL);

    t->tab = malloc(size * sizeof (maillon_billes));
    assert(t->tab != NULL);

    for(i = 0; i < size - 1; i++)
    {
        t->tab[i].next = &(t->tab[i+1]);
    }
    t->tab[size-1].next = NULL;

    t->size_tab = size;

    return t;
}

list_tab_maillons * newListTabMaillon()
{
    list_tab_maillons *r = malloc(sizeof (list_tab_maillons));
    if (r == NULL)
    {
        assert(0);
    }
    r->size = 0;
    r->head = NULL;
    r->tail = NULL;
    return r;
}

void addHeadLTM(list_tab_maillons *l, tab_maillon *m)
{
    assert(m!=NULL);
    m->next = l->head;
    l->head = m;
    if (l->size == 0)
    {
        l->tail = m;
    }
    l->size += 1;
}

tab_maillon * removeHeadLTM(list_tab_maillons *l)
{
    tab_maillon *t = l->head;

    l->head = l->head->next;
    l->size -= 1;

    if(l->size == 0)
    {
        l->head = NULL;
    }

    return t;
}

// ---------------------------Matchbox (arraylist)-----------------------------

// Add new empty maillons to the arraylist
void enlargeFree(maillon_mb *mb, uint32_t size)
{
    tab_maillon *t;

    assert(mb->free->size == 0);

    t = newTabMaillon(size);
    assert(t != NULL);

    addHeadLTM(mb->ltm, t);

    mb->free->head = &(t->tab[0]);
    mb->free->tail = &(t->tab[t->size_tab - 1]);
    mb->free->size = t->size_tab;
}


// New matchbox (new arraylist)
maillon_mb *newMaillonMb(uint32_t config)
{
    maillon_mb *m = malloc(sizeof (maillon_mb));
    if (m == NULL)
    {
        assert(0);
    }
    m->config = config;
    getConfigurations(config, m->modifications);
    m->taken = newListBilles();
    m->free = newListBilles();
    m->ltm = newListTabMaillon();

    enlargeFree(m, 9);
    //tableToBilles(m);

    return m;
}

// Add a new bille to matchbox
void addHeadMb(maillon_mb* mb, enum billes b)
{
    // If there aren't any empty maillons left
    if (mb->free->size == 0)
    {
        enlargeFree(mb, 9);
    }

    maillon_billes *l = removeHeadBilles(mb->free);
    l->bille = b;

    addHeadBilles(mb->taken, l);
}

// Remove the bille from matchbox
enum billes removeBilleMb(maillon_mb* mb)
{
    maillon_billes *l;
    enum billes b;

    l = removeHeadBilles(mb->taken);
    b = l->bille;

    addHeadBilles(mb->free, l);

    return b;
}

// Free the memory of matchbox
void freeMb(maillon_mb *mb)
{
    tab_maillon  *t;

    while(mb->ltm->size != 0)
    {
        t = removeHeadLTM(mb->ltm);
        free(t->tab);
        free(t);
    }

    free(mb->free);
    free(mb->taken);
    free(mb->ltm);

    free(mb);
}


//-------------------------Hashing------------------------------

// Add matchbox to the list
void addHeadMbHash(list_mb *l, uint32_t config)
{
    maillon_mb *m = newMaillonMb(config);
    assert(m!=NULL);
    m->next = l->head;
    l->head = m;
    if (l->size == 0)
    {
        l->tail = m;
    }
    l->size += 1;
}

// New list of matchboxes
list_mb *newListMB()
{
    list_mb *r = malloc(sizeof (list_mb));
    if (r == NULL)
    {
        assert(0);
    }
    r->size = 0;
    r->head = NULL;
    r->tail = NULL;
    return r;
}

// New hashtable
matchboxes* newMatchboxes(uint32_t size)
{
    uint32_t i;
    matchboxes *mb = malloc(sizeof(matchboxes));
    assert(mb != NULL);

    mb->tab = malloc(size * sizeof(list_mb *));
    assert(mb->tab != NULL);

    for (i = 0; i < size; i++)
    {
        mb->tab[i] = newListMB();
    }

    mb->size = size;
    return mb;
}

// Hash function
uint32_t hashing(matchboxes *mb, uint32_t config)
{
    // Sum of 7 configurations
    uint32_t sum1=0;

    // Sum of digits of sum1
    uint32_t sum2=0;

    // Fill in the array with "transformation"
    uint32_t conf[8];
    getConfigurations(config, conf);

    // Sum up each configuration
    for (uint32_t p = 0; p < 8; p++)
    {
        sum1+=conf[p];
    }

    uint32_t tmp = sum1;
    uint32_t m;

    // Calculate the sum of digits
    while(tmp > 0)
    {
        m = tmp % 10;
        sum2 = sum2 + m;
        tmp = tmp / 10;
    }

    if(sum2 == 0)
    {
        sum2=1;
    }

    return (sum1/sum2)%mb->size;
}

// Add a matchbox to the hash table
void addHeadHash(matchboxes *mb, uint32_t config)
{
    uint32_t p = hashing(mb, config);
    addHeadMbHash(mb->tab[p], config);
}

// Free the memory of hash table
void freeHashTable(matchboxes *th)
{
    uint32_t i;
    maillon_mb *mb;

    for(i = 0; i < th->size; i = i + 1)
    {
        while(th->tab[i]->size != 0)
        {
            mb = th->tab[i]->head;

            th->tab[i]->head = th->tab[i]->head->next;

            freeMb(mb);

            th->tab[i]->size--;
        }
        free(th->tab[i]);
    }

    free(th->tab);
    free(th);
}

// Find a matchbox in hash table
maillon_mb *findMb(matchboxes *th, uint32_t config)
{
    maillon_mb *mb;
    uint32_t p = hashing(th, config);
    mb = th->tab[p]->head;

    while(mb != NULL)
    {
        if (mb->config == config)
        {
            return mb;
        }
        mb = mb->next;
    }
    return NULL;
}

// Find a basic matchbox for the modification
maillon_mb *findBaseConfiguration(matchboxes *th, uint32_t config)
{
    maillon_mb *mb;
    uint32_t p = hashing(th, config);
    mb = th->tab[p]->head;

    while(mb != NULL)
    {
        for (uint32_t i = 0; i < 8; i++)
        {
            if (mb->modifications[i] == config)
            {
                return mb;
            }
        }

        mb = mb->next;
    }
    return NULL;
}

// -----------------------Operations------------------------------

// Cound the number of specific billes in the matchbox
uint32_t countBilles(list_billes *l, enum billes b)
{
    maillon_billes *p = l->head;
    uint32_t c = 0;
    uint32_t res = 0;
    while(p != NULL)
    {
        if (p->bille == b)
        {
            res++;
        }
        c++;
        p = p->next;
    }
    return res;
}

// Get the bille by index
enum billes getBille(uint32_t ind)
{
    switch (ind)
    {
        case 1:
            return yellow;
        case 2:
            return red;
        case 3:
            return green;
        case 4:
            return blue;
        case 5:
            return orange;
        case 6:
            return purple;
        case 7:
            return white;
        case 8:
            return black;
        case 9:
            return pink;
        default:
            break;
    }
    return -1;
}

// Get the index by bille
uint32_t getBilleIndex(enum billes b)
{
    switch(b)
    {
        case yellow:
            return 1;
        case red:
            return 2;
        case green:
            return 3;
        case blue:
            return 4;
        case orange:
            return 5;
        case purple:
            return 6;
        case white:
            return 7;
        case black:
            return 8;
        case pink:
            return 9;
        default:
            break;
    }
}



