#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "matchboxes.h"
#include "game.h"

/*
 *
 * Functions related to game
 *
 */

// Returns 1 if 3 in a column of value "val"
_Bool isColumn(uint8_t table[3][3], uint32_t val)
{
    for (uint32_t i = 0; i < 3; i++)
    {
        if ((table[0][i] == table[1][i]) & (table[0][i] == table[2][i]) & (table[0][i] == val))
        {
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

// Check if table is a valid matchbox (for 304 version)
_Bool isValid(uint8_t table[3][3])
{
    // Calculate the sum of x and o
    uint32_t sum_x = 0;
    uint32_t sum_o = 0;
    for (uint32_t i = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            if (table[i][j] == 2)
            {
                sum_x++;
            }
            else if (table[i][j] == 1)
            {
                sum_o++;
            }
        }
    }

    // The matchbox is valid if
    // 1) sum of x is equal to sum of 0
    // 2) there is at least one empty field
    // 3) sum of x/o is less or equal to 3
    if ((sum_o == sum_x) && (freePlaces(table)>=1))
    {
        if(sum_x <= 3)
        {
            if (isWin(table) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Generate a new file with 304 matchboxes
void generateNewGame(FILE * file)
{
    // The first empty configuration
    uint32_t *matchboxes = malloc(304 * sizeof(uint32_t));
    uint8_t g[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    matchboxes[0] = tableTo3(g);
    print_all_transformations_1d(g, file);

    // Number of configurations which are already added
    uint32_t counter = 1;

    // Flag of whether current config is a config of already existing matchboxes
    _Bool is_config;

    // Flag to break the while if is configuration / indicate the end of array with matchboxes
    uint32_t while_counter;

    // Index of array with matchboxes
    uint32_t i;

    // Go through all the configurations
    while(next_configuration(g)==0)
    {
        if (isValid(g))
        {
            while_counter = counter;
            i = 0;

            // Check each stored matchbox for configuration
            while(while_counter!=0)
            {
                if (isConfiguration(tableTo3(g), matchboxes[i]))
                {
                    while_counter = 0;
                    is_config = 1;
                }
                else
                {
                    is_config = 0;
                    i++;
                    while_counter--;
                }
            }

            // If a new matchbox (is not a configuration)
            if (!is_config)
            {
                matchboxes[counter] = tableTo3(g);
                counter++;
                print_all_transformations_1d(g, file);
            }
        }
    }

    free(matchboxes);
}