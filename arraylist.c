#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "arraylist.h"

/*
 *
 * Matchbox (arraylist) data structure
 *
 */



maillon *newMaillon(enum billes b)
{
    maillon *m = malloc(sizeof (maillon));
    if (m == NULL)
    {
        assert(0);
    }
    m->bille = b;
    return m;
}

list *newList()
{
    list *r = malloc(sizeof (list));
    if (r == NULL)
    {
        assert(0);
    }
    r->size = 0;
    r->head = NULL;
    r->tail = NULL;
    return r;
}

void addHead(list *l, enum billes b)
{
    maillon *m = newMaillon(b);
    assert(m!=NULL);
    m->next = l->head;
    l->head = m;
    if (l->size == 0)
    {
        l->tail = m;
    }
    l->size += 1;
}

/*void enlargeFree(matchbox *mb, uint32_t size)
{
    maillon *t;
    uint32_t i;

    assert(mb->free->size == 0);

    t = malloc(size * sizeof (maillon));
    assert(t != NULL);

    for (i=0; i<size-1; i++)
    {
        t[i].next = &(t[i+1]);
    }
    t[size-1].next = NULL;

    mb->free->head = &(t[0]);
    mb->free->tail = &(t[size - 1]);
    mb->free->size = size;
}*/

matchbox *newMatchbox(uint32_t config)
{
    matchbox *mb;
    mb = malloc(sizeof(matchbox));
    assert(mb != NULL);

    mb->taken = newList();
    mb->free = newList();
    mb->config = config;

    //enlargeFree(mb, size);

    return mb;
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

void addBilles(list *l, uint8_t table[3][3])
{
    for (uint32_t i = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            if (table[i][j] == 0)
            {
                addHead(l, getBille(i+j+1));
            }
        }
    }
    /*maillon *p = l->head;
    uint32_t c = 0;
    while(p != NULL)
    {
        p->bille = b[c];
        c++;
        p = p->next;
    }*/
}

uint32_t countBilles(list *l, enum billes b)
{
    maillon *p = l->head;
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


