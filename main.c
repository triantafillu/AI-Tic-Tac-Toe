#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "aide_projet.c"
#include "arraylist.c"
#include<time.h>

// Returns 1 if 3 in a column of value "val"
_Bool isColumn(uint8_t table[3][3], uint32_t val)
{
    for (uint32_t i = 0; i < 3; i++)
    {
        if ((table[0][i] == table[1][i]) & (table[0][i] == table[2][i]) & (table[0][i] == val))
        {
            printf("%d", table[0][i]);
            printf("%d", table[1][i]);
            printf("%d", table[2][i]);
            return 1;
        }
    }

    return 0;
}

// Returns 1 if 3 in a row of value "val"
_Bool isRow(uint8_t table[3][3], uint32_t val)
{
    for (uint32_t i = 0; i < 3; i++)
    {
        if ((table[i][0] == table[i][1]) & (table[i][0] == table[i][2]) & (table[i][0] == val))
        {
            return 1;
        }
    }

    return 0;
}

// Returns 1 if 3 in a diagonal of value "val"
_Bool isDiagonal(uint8_t table[3][3], uint32_t val)
{
    if ((table[0][0] == table[1][1]) & (table[0][0] == table[2][2]) & (table[0][0] == val))
    {
        return 1;
    }
    else if ((table[0][2] == table[1][1]) & (table[0][2] == table[2][0]) & (table[0][2] == val))
    {
        return 1;
    }

    return 0;
}

// 1 - win of 1
// 2 - win of 2
// 0 - draw
uint32_t isWin(uint8_t table[3][3])
{
    if (isColumn(table, 1) | isRow(table,1) | isDiagonal(table, 1))
    {
        return 1;
    }
    if (isColumn(table, 2) | isRow(table,2) | isDiagonal(table, 2))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

uint32_t tableTo3(uint8_t table[3][3])
{
    uint32_t res = 0;
    uint32_t mult = 100000000;
    for (uint32_t i = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            res += table[i][j] * mult;
            mult /= 10;
        }
    }

    return res;
}


/*uint32_t[3][3] * threeToTable(uint32_t three)
{
    uint32_t res[3][3];
    for (int i = 2; i > -1 ; i--)
    {
        for (int j = 2; j > -1 ; j--)
        {
            res[i][j] = three % 10;
            three /= 10;
        }
    }

    return res;
}*/

// Translate the table represented by a number of base 3 to the base 10
uint32_t translate10 (uint32_t table)
{
    uint32_t digit;
    uint32_t res = 0;
    uint32_t power = 0;

    // Iterate over the table
    while(table != 0)
    {
        // Pick up the last digit of the number
        digit = table % 10;

        // + digit multiplied by a 3 in power corresponding to position in table
        res += digit * pow(3,power);

        // Increment power
        power++;

        // Remove the last digit
        table = table / 10;
    }

    return res;
}

// Translate the decimal number to its table representation (base 3)
uint32_t translate3(uint32_t number)
{
    uint32_t res = 0;
    uint32_t power = 0;
    uint32_t rem;

    while (number != 0)
    {
        // Pick up the remainder
        rem = number % 3;

        // Get the result of division by base (3)
        number = number / 3;

        // The remainder becomes the lowest digit
        res += rem * pow(10, power);

        // Increment the power
        power++;
    }

    return res;
}

//Fonction qui initialise un boite: 
//Une boite se compose de 9 boules de couleurs différentes 
//Et on a un nombre en base 3 correspondant au jeu de la carte 
configuration* init_box(uint32_t g){
    configuration* res= malloc(sizeof(configuration)); 
    res->game=g; 
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
enum billes rand_bille(configuration* boite){
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
