#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "aide_projet.h"
#include "math.h"
#include "matchboxes.h"
#include "arraylist.h"
#define CONTINUE 0

/*
 *
 * All the functions related to manipulations with matchboxes
 * e.g. initialising new matchboxes, saving results to file
 *
 */


/*uint32_t tableTo3(uint8_t table[3][3])
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
}*/


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

// Get a list of free billes for the configuration
enum billes *tableToBilles(uint8_t table[3][3], uint32_t size)
{
    enum billes *b = malloc(size * sizeof (enum billes));
    uint32_t counter = 0;
    for (uint32_t i = 0; i<3; i++)
    {
        for (uint32_t j = 0; j<3; j++)
        {
            if (table[i][j] != 0)
            {
                b[counter] = getBille(i+j+1);
                counter++;
            }
        }
    }
    return b;
}

// Get a number of emply places on the board
uint32_t freePlaces(uint8_t table[3][3])
{
    uint32_t res = 0;
    for (uint32_t i = 0; i<3; i++)
    {
        for (uint32_t j = 0; j<3; j++)
        {
            if (table[i][j] == 0)
            {
                res++;
            }
        }
    }
    return res;
}

// Initialize matchboxes for the start of learning
void initializeMatchboxes()
{
    // Table of matchboxes
    matchbox mb[304];
    uint32_t num_of_billes;
    uint32_t c = 1;

    // Empty board
    uint8_t g[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    // Matchbox with 9 free beads
    mb[0] = *newMatchbox(9, 000000000);
    // Fill up the names of free beads
    addBilles(mb[0].free, tableToBilles(g, 9));

    // Repeat for each configuration
    while(next_configuration(g)==CONTINUE)
    {
        num_of_billes = freePlaces(g);
        mb[c] = *newMatchbox(num_of_billes, tableTo3(g));
        addBilles(mb[c].free, tableToBilles(g, num_of_billes));
        c++;
    }

}

const char* getCaseCSV(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

matchbox * readGameState(FILE* file)
{
    // Table of matchboxes
    matchbox* mb=malloc(sizeof(matchbox));
    // Index of matchbox
    uint32_t c = 0;

    char line[1];
    // For each line in file
    while (fgets(line, 1, file))
    {
        // Next line
        char* tmp = strdup(line);
        // First cell - configuration
        mb[c].config = atoi(getCaseCSV(tmp, 1));

        uint32_t case_c = 2;
        // For every number of beads
        while(case_c < 10)
        {
            // Add corresponding beads to the list of free beads
            for(int i=0; i<atoi(getCaseCSV(tmp, case_c)); i++)
            {
                addHead(mb[c].free, getBille(case_c - 1));

            }
            case_c++;
        }
        free(tmp);
        c++;
    }

    return mb;
}



