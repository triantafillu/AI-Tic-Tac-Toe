#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "aide_projet.h"
#include "matchboxes.h"
#define CONTINUE 0
#define FINISHED 1

void appliquer_transformation_base(uint8_t grille[3][3], transformation tr)
{
    uint8_t t;
    switch(tr)
    {
        case(ID):
            break;

        case(ROT_90):
            t = grille[0][0];
            grille[0][0] = grille[2][0];
            grille[2][0]=grille[2][2];
            grille[2][2]=grille[0][2];
            grille[0][2]=t;

            t = grille[0][1];
            grille[0][1] = grille[1][0];
            grille[1][0]=grille[2][1];
            grille[2][1]=grille[1][2];
            grille[1][2]=t;
            break;

        case(ROT_180):
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, ROT_90);
            break;

        case(ROT_270):
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, ROT_90);
            break;

        case(MIROIR_VERT):
            t = grille[0][0];
            grille[0][0] = grille[0][2];
            grille[0][2] = t;

            t = grille[1][0];
            grille[1][0] = grille[1][2];
            grille[1][2] = t;

            t = grille[2][0];
            grille[2][0] = grille[2][2];
            grille[2][2] = t;
            break;

        case(MIROIR_HORIZ):
            appliquer_transformation_base(grille, ROT_90);
            appliquer_transformation_base(grille, MIROIR_VERT);
            appliquer_transformation_base(grille, ROT_270);
    }
}

void appliquer_transformation_base_pointer(uint8_t **grille, transformation tr)
{
    uint8_t t;
    switch(tr)
    {
        case(ID):
            break;

        case(ROT_90):
            t = grille[0][0];
            grille[0][0] = grille[2][0];
            grille[2][0]=grille[2][2];
            grille[2][2]=grille[0][2];
            grille[0][2]=t;

            t = grille[0][1];
            grille[0][1] = grille[1][0];
            grille[1][0]=grille[2][1];
            grille[2][1]=grille[1][2];
            grille[1][2]=t;
            break;

        case(ROT_180):
            appliquer_transformation_base_pointer(grille, ROT_90);
            appliquer_transformation_base_pointer(grille, ROT_90);
            break;

        case(ROT_270):
            appliquer_transformation_base_pointer(grille, ROT_90);
            appliquer_transformation_base_pointer(grille, ROT_90);
            appliquer_transformation_base_pointer(grille, ROT_90);
            break;

        case(MIROIR_VERT):
            t = grille[0][0];
            grille[0][0] = grille[0][2];
            grille[0][2] = t;

            t = grille[1][0];
            grille[1][0] = grille[1][2];
            grille[1][2] = t;

            t = grille[2][0];
            grille[2][0] = grille[2][2];
            grille[2][2] = t;
            break;

        case(MIROIR_HORIZ):
            appliquer_transformation_base_pointer(grille, ROT_90);
            appliquer_transformation_base_pointer(grille, MIROIR_VERT);
            appliquer_transformation_base_pointer(grille, ROT_270);
    }
}

// Store all the configurations of board in the tab[7]
void getConfigurations(uint32_t config, uint32_t tab[8])
{
    uint8_t **g;
    g = threeToTable(config);

    for(uint32_t i = 0; i < 8; i++)
    {
        appliquer_transformation_base_pointer(g, ROT_90);
        if ( i == 3 || i == 7)
        {
            appliquer_transformation_base_pointer(g, MIROIR_VERT);
        }
        tab[i] = tableTo3Pointer(g);
    }

    for(uint32_t k = 0; k < 3; k++)
    {
        free(g[k]);
    }
    free(g);
}

uint8_t next_configuration(uint8_t grille[3][3])
{
    uint8_t i, j;

    grille[0][0]++;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(grille[i][j]==3)
            {
                grille[i][j]=0;
                if(j<2) grille[i][j+1]++;
                else if(i<2) grille[i+1][0]++;
                else return FINISHED;
            }
        }
    }

    return CONTINUE;
}

// Check whether t1 and t2 are equivalent
_Bool isConfiguration(uint32_t t1, uint32_t t2)
{
    uint8_t **table1 = threeToTable(t1);
    uint32_t t3;

    uint8_t copy[3][3];
    for (uint32_t i = 0; i<3; i++)
    {
        for (uint32_t j = 0; j<3; j++)
        {
            copy[i][j] = table1[i][j];
        }
    }

    appliquer_transformation_base(copy, ROT_90);
    t3 = tableTo3(copy);
    if (t3 == t2)
    {
        return 1;
    }
    else
    {
        appliquer_transformation_base(copy, ROT_90);
        t3 = tableTo3(copy);
        if (t3 == t2)
        {
            return 1;
        }
        else
        {
            appliquer_transformation_base(copy, ROT_90);
            t3 = tableTo3(copy);
            if (t3 == t2)
            {
                return 1;
            }
            else
            {
                appliquer_transformation_base(copy, ROT_90);
                appliquer_transformation_base(copy, MIROIR_VERT);
                t3 = tableTo3(copy);
                if (t3 == t2)
                {
                    return 1;
                }
                else
                {
                    appliquer_transformation_base(copy, ROT_90);
                    t3 = tableTo3(copy);
                    if (t3 == t2)
                    {
                        return 1;
                    }
                    else
                    {
                        appliquer_transformation_base(copy, ROT_90);
                        t3 = tableTo3(copy);
                        if (t3 == t2)
                        {
                            return 1;
                        }
                        else
                        {
                            appliquer_transformation_base(copy, ROT_90);
                            t3 = tableTo3(copy);
                            if (t3 == t2)
                            {
                                return 1;
                            }

                        }
                    }
                }
            }
        }
    }

    for(uint32_t k = 0; k < 3; k++)
    {
        free(table1[k]);
    }
    free(table1);

    return 0;

}


