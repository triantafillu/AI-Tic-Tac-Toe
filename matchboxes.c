#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "aide_projet.h"
#include "math.h"
#include "matchboxes.h"
#include "hashtable.h"
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

uint32_t tableTo3Pointer(uint8_t **table)
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


uint8_t** threeToTable(uint32_t three)
{
    uint8_t **res = malloc(3 * sizeof(uint8_t*));
    for(uint32_t j = 0; j < 3; j++)
    {
        res[j] = malloc(3 * sizeof(uint8_t));
    }
    for (int i = 2; i > -1 ; i--)
    {
        for (int j = 2; j > -1 ; j--)
        {
            res[i][j] = three % 10;
            three /= 10;
        }
    }

    return res;
}

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



// Get a list of free billes for the configuration
void tableToBilles(maillon_mb *mb)
{
    uint8_t base[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    uint32_t counter = 0;
    uint8_t **table;

    for (uint32_t i = 0; i<3; i++)
    {
        for (uint32_t j = 0; j<3; j++)
        {
            table = threeToTable(mb->config);
            if (table[i][j] == 0)
            {
                addHeadMb(mb, getBille(base[i][j]));
                counter++;
            }
            for(uint32_t k = 0; k < 3; k++)
            {
                free(table[k]);
            }
            free(table);
        }
    }

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


uint32_t freePlacesPointer(uint8_t **table)
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


void printConfigToBilles(FILE * file, uint8_t config[3][3])
{
    for (uint32_t i = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            if (config[i][j] == 0)
            {
                if ((i == 2) && (j == 2))
                {
                    fprintf(file, "%d\n", 1);
                }
                else
                {
                    fprintf(file, "%d,", 1);
                }
            }
            else
            {
                if ((i == 2) && (j == 2))
                {
                    fprintf(file, "%d\n", 0);
                }
                else
                {
                    fprintf(file, "%d,", 0);
                }
            }
        }
    }
}


// Intialize buffer to 0 (used in readGameState)
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

matchboxes *readGameState(FILE* file)
{
    matchboxes *th = newMatchboxes(10);
    maillon_mb *mb;

    // Index of matchbox
    uint32_t c = 0;
    // Variable used to read next character
    uint32_t tmp=0;
    // Buffer index
    uint32_t i;
    // Buffer number conversion
    uint32_t nb; 
    // The character read from file
    uint8_t r=0;
    // Buffer to stock characters and transform them to int
    char buffer[9]="";
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
            if( (tmp = fscanf(file,"%c",&r)) < 0){
                perror("Error while reading the file\n"); 
            }

        }
        nb=atoi(buffer);
        addHeadHash(th, nb);
        mb = findMb(th, nb);
        emptyBuffer(buffer, 9);

        // For each cell after 2 (quantities of beads)
        case_c = 2;
        for (int j=0; j<9; j++)
        {
            i = 0;
            // Read the next character after ","
            if( (tmp = fscanf(file,"%c",&r)) < 0){
                perror("Error while reading the file\n"); 
            }

            // Read till ",", if the last cell - read till "\n"
            if (case_c != 10)
            {
                while( r != ',' )
                {
                    buffer[i]=r;
                    i++;
                    if( (tmp = fscanf(file,"%c",&r)) < 0){
                        perror("Error while reading the file\n"); 
                    }
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
                addHeadMb(mb, getBille(case_c - 1)); // Beads correspond to cell in csv file - 1
            }
            case_c++;
        }
        c++;
    }
    return th;
}


// Write game state to the csv file
void writeGameState(FILE * file, matchboxes *mb)
{
    for (uint32_t i = 0; i < mb->size; i++)
    {
        maillon_mb *p = mb->tab[i]->head;

        while(p!=NULL)
        {
            // Print configuration
            fprintf(file, "%d,", p->config);

            // For each bead colour: count beads, print the number
            for (uint32_t j = 1; j<10; j++)
            {
                // If the last line and the last cell
                if ((j == 9) & (i == 304))
                {
                    fprintf(file, "%d", countBilles(p->taken, getBille(j)));
                }

                // If the last cell
                else if (j == 9)
                {
                    fprintf(file, "%d\n", countBilles(p->taken, getBille(j)));
                }


                else
                {
                    fprintf(file, "%d,", countBilles(p->taken, getBille(j)));
                }
            }

            p = p->next;
        }
    }
}
