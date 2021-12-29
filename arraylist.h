//
// Created by alexa on 12/26/2021.
//

#ifndef PROJET_ARRAYLIST_H
#define PROJET_ARRAYLIST_H

enum billes {yellow, red, green, blue, orange, purple, white, black, pink};

// yellow| red    | green
// blue  | orange | purple
// white | black  | pink

typedef struct _maillon
{
    enum billes bille;
    struct _maillon *next;
}maillon;

typedef struct
{
    uint32_t size;
    maillon *head;
    maillon *tail;
} list;

typedef struct
{
    uint32_t config;
    list *free;
    list *taken;
} matchbox;

maillon *newMaillon(enum billes b);
list *newList();
void addHead(list *l, enum billes b);
void enlargeFree(matchbox *mb, uint32_t size);
matchbox *newMatchbox(uint32_t config);
void addBilles(list *l, enum billes *b);
uint32_t countBilles(list *l, enum billes b);

#endif //PROJET_ARRAYLIST_H
