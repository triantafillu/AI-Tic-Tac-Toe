#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "hashtable.h"
#include "aide_projet.h"

//-----------------------------Billes-------------------------------------
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

void enlargeFree(maillon_mb *mb, uint32_t size)
{
    tab_maillon *t;
    uint32_t i;

    assert(mb->free->size == 0);

    t = newTabMaillon(size);
    assert(t != NULL);

    addHeadLTM(mb->ltm, t);

//    for (i=0; i<size-1; i++)
//    {
//        t[i].next = &(t[i+1]);
//    }
//    t[size-1].next = NULL;

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

uint32_t hashing(matchboxes *mb, uint32_t config)
{
    uint32_t sum=0;
    uint32_t m;

    while(config > 0)
    {
        m = config % 10;
        sum = sum + m;
        config = config / 10;
    }

    return sum % mb->size;
}

void addHeadHash(matchboxes *mb, uint32_t config)
{
    uint32_t p = hashing(mb, config);
    addHeadMbHash(mb->tab[p], config);
}

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
        }
        free(th->tab[i]);
    }

    free(th->tab);
    free(th);
}

// -----------------------Operations------------------------------
//uint32_t countBilles(list *l, enum billes b)
//{
//    maillon *p = l->head;
//    uint32_t c = 0;
//    uint32_t res = 0;
//    while(p != NULL)
//    {
//        if (p->bille == b)
//        {
//            res++;
//        }
//        c++;
//        p = p->next;
//    }
//    return res;
//}

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



