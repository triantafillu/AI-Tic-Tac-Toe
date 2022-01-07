#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

enum billes {yellow, red, green, blue, orange, purple, white, black, pink};

// yellow| red    | green
// blue  | orange | purple
// white | black  | pink


typedef struct _maillon_billes
{
    enum billes bille;
    struct _maillon_billes *next;
}maillon_billes;


typedef struct _maillon_mb
{
    uint32_t config;
    list *billes;
    struct _maillon_mb *next;
}maillon_mb;

typedef struct
{
    uint32_t size;
    maillon *head;
    maillon *tail;
} list;

typedef struct
{
    list **tab;
    uint32_t size;
} matchboxes;

maillon *newMaillon(enum billes b);
list *newList();
void addHead(list *l, enum billes b);




maillon_mb *newMaillonMb(uint32_t config)
{
    maillon_mb *m = malloc(sizeof (maillon_mb));
    if (m == NULL)
    {
        assert(0);
    }
    m->config = config;
    m->billes = malloc(sizeof(list));
    return m;
}

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

void addHeadBilles(list *l, enum billes b)
{
    maillon_billes *m = newMaillonBilles(b);
    assert(m!=NULL);
    m->next = l->head;
    l->head = m;
    if (l->size == 0)
    {
        l->tail = m;
    }
    l->size += 1;
}

void addHeadMb(list *l, uint32_t config)
{
    maillon_mb *m = newMaillonMb(config);
    assert(m!=NULL);
    m->billes = newList();
    m->next = l->head;
    l->head = m;
    if (l->size == 0)
    {
        l->tail = m;
    }
    l->size += 1;
}

matchboxes* newMatchboxes(uint32_t size)
{
    uint32_t i;
    matchboxes *mb = malloc(sizeof(matchboxes));
    assert(mb != NULL);

    mb->tab = malloc(size * sizeof(list*));
    assert(mb->tab != NULL);

    for (i = 0; i < size; i++)
    {
        mb->tab[i] = newList();
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
    addHeadMb(mb->tab[p], config);
}