#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    uint32_t game; 
    list *free;
    list *taken;
} configuration;

