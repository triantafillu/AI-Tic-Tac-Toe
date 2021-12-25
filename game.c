#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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