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
/*void initializeMatchboxes()
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

}*/

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

void emptyBuffer(char *buf, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        buf[i] = 0;
    }
}
// Read the matchboxes from file
// File structure:
// config, yellow, red, green, blue, orange, purple, white, black, pink
matchbox ** readGameState(FILE* file)
{
    // Table of matchboxes
    matchbox** mb= malloc(3 * sizeof(matchbox));

    // Initialize empty matchboxes
    for (int l = 0; l<3; l++)
    {
        mb[l] = newMatchbox(0);
    }

    // Index of matchbox
    uint32_t c = 0;
    // Variable used to read next character
    uint32_t tmp;
    // Buffer index
    uint32_t i;
    // The character read from file
    uint8_t r=0;
    // Buffer to stock characters and transform them to int
    uint8_t buffer[9];
    // Number of beads of specific colour
    uint32_t num_of_billes;
    // Current case of csv file
    uint32_t case_c;

    // For each line in file
    while (fscanf(file,"%c",&r) != EOF)
    {
        // First cell - configuration
        i=0;
        while( r != ',' )
        {
            buffer[i]=r;
            i++;
            tmp = fscanf(file,"%c",&r);

        }
        mb[c]->config = atoi(buffer);
        emptyBuffer(buffer, 9);

        // For each cell after 2 (quantities of beads)
        case_c = 2;
        for (int j=0; j<9; j++)
        {
            i = 0;
            // Read the next character after ","
            tmp = fscanf(file,"%c",&r);

            // Read till ",", if the last cell - read till "\n"
            if (case_c != 10)
            {
                while( r != ',' )
                {
                    buffer[i]=r;
                    i++;
                    tmp = fscanf(file,"%c",&r);
                }
            }
            else
            {
                while( r != '\n')
                {
                    buffer[i]=r;
                    i++;

                    // If the "\n" is EOF
                    if (fscanf(file,"%c",&r) == EOF)
                    {
                        break;
                    }
                }
            }
            num_of_billes = atoi(buffer);
            emptyBuffer(buffer, 9);

            // Add beads of this colour
            for(int k = 0; k < num_of_billes; k++)
            {
                addHead(mb[c]->free, getBille(case_c - 1)); // Beads correspond to cell in csv file - 1
            }
            case_c++;
        }
        c++;
    }
    return mb;
}

// Write game state to the csv file
void writeGameState(FILE * file, matchbox **mb)
{
    for (uint32_t i = 0; i < 3; i++)
    {
        // Print configuration
        fprintf(file, "%d,", mb[i]->config);

        // For each bead colour: count beads, print the number
        for (uint32_t j = 0; j<10; j++)
        {
            // If the last line and the last cell
            if ((j == 9) & (i == 2))
            {
                fprintf(file, "%d", countBilles(mb[i]->free, getBille(j)));
            }

            // If the last cell
            else if (j == 9)
            {
                fprintf(file, "%d\n", countBilles(mb[i]->free, getBille(j)));
            }


            else
            {
                fprintf(file, "%d,", countBilles(mb[i]->free, getBille(j)));
            }
        }
    }
}



