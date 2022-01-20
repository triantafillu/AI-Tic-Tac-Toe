#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "time.h"
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
        if ((table[0][i] == table[1][i]) && (table[0][i] == table[2][i]) && (table[0][i] == val))
        {
            return 1;
        }
    }

    return 0;
}
_Bool isColumnPointer(uint8_t **table, uint32_t val)
{
    for (uint32_t i = 0; i < 3; i++)
    {
        if ((table[0][i] == table[1][i]) && (table[0][i] == table[2][i]) && (table[0][i] == val))
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
        if ((table[i][0] == table[i][1]) && (table[i][0] == table[i][2]) && (table[i][0] == val))
        {
            return 1;
        }
    }

    return 0;
}

_Bool isRowPointer(uint8_t **table, uint32_t val)
{
    for (uint32_t i = 0; i < 3; i++)
    {
        if ((table[i][0] == table[i][1]) && (table[i][0] == table[i][2]) && (table[i][0] == val))
        {
            return 1;
        }
    }

    return 0;
}

// Returns 1 if 3 in a diagonal of value "val"
_Bool isDiagonal(uint8_t table[3][3], uint32_t val)
{
    if ((table[0][0] == table[1][1]) && (table[0][0] == table[2][2]) && (table[0][0] == val))
    {
        return 1;
    }
    else if ((table[0][2] == table[1][1]) && (table[0][2] == table[2][0]) && (table[0][2] == val))
    {
        return 1;
    }

    return 0;
}

_Bool isDiagonalPointer(uint8_t **table, uint32_t val)
{
    if ((table[0][0] == table[1][1]) && (table[0][0] == table[2][2]) && (table[0][0] == val))
    {
        return 1;
    }
    else if ((table[0][2] == table[1][1]) && (table[0][2] == table[2][0]) && (table[0][2] == val))
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
    if (isColumn(table, 1) || isRow(table,1) || isDiagonal(table, 1))
    {
        return 1;
    }
    if (isColumn(table, 2) || isRow(table,2) || isDiagonal(table, 2))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

uint32_t isWinPointer(uint8_t **table)
{
    if (isColumnPointer(table, 1) || isRowPointer(table,1) || isDiagonalPointer(table, 1))
    {
        return 1;
    }
    if (isColumnPointer(table, 2) || isRowPointer(table,2) || isDiagonalPointer(table, 2))
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
    uint32_t config;
    // The first empty configuration
    uint32_t *matchboxes = malloc(304 * sizeof(uint32_t));
    uint8_t g[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    config = tableTo3(g);
    matchboxes[0] = config;
    fprintf(file, "%d,", config);
    printConfigToBilles(file, g);

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
                config = tableTo3(g);
                matchboxes[counter] = config;
                fprintf(file, "%d,", config);

                printConfigToBilles(file, g);
                //printf("%d\n", translate10(config)%304);
                counter++;
            }
        }
    }
    free(matchboxes);
}

// Transform user's choice to configuration on base 3
uint32_t choiceToConfig(uint32_t choice, uint32_t player)
{
    uint32_t res;
    if (player == 1)
    {
        switch(choice)
        {
            case 1:
                res = 100000000;
                break;

            case 2:
                res = 10000000;
                break;

            case 3:
                res = 1000000;
                break;

            case 4:
                res = 100000;
                break;

            case 5:
                res = 10000;
                break;

            case 6:
                res = 1000;
                break;

            case 7 :
                res = 100;
                break;

            case 8:
                res = 10;
                break;

            case 9:
                res = 1;
                break;

            default:
                res = 0;
                break;
        }
    }
    else if (player == 2)
    {
        switch(choice)
        {
            case 1:
                res = 200000000;
                break;

            case 2:
                res = 20000000;
                break;

            case 3:
                res = 2000000;
                break;

            case 4:
                res = 200000;
                break;

            case 5:
                res = 20000;
                break;

            case 6:
                res = 2000;
                break;

            case 7 :
                res = 200;
                break;

            case 8:
                res = 20;
                break;

            case 9:
                res = 2;
                break;

            default:
                res = 0;
                break;
        }
    }
    else
    {
        res = 0;
    }

    return res;
}

uint32_t getBillesTransormation(maillon_mb *mb, uint32_t config, uint32_t choice)
{
    uint8_t billes_indexes[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    uint8_t base[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    uint32_t transformation = 0;
    uint32_t i, j;
    uint32_t new_choice = 0;

    // Find the transformation for configuration
    for (j = 0; j < 8; j++)
    {
        if (config == mb->modifications[j])
        {
            transformation = j;
            break;
        }
    }

    // Rotate indexes of billes
    for (i = 0; i < transformation + 1; i++)
    {
        appliquer_transformation_base(billes_indexes, ROT_90);
        if(i == 3 || i == 7)
        {
            appliquer_transformation_base(billes_indexes, MIROIR_VERT);
        }

    }

    // Get a new position of a chosen bille
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (choice == billes_indexes[i][j])
            {
                new_choice = base[i][j];
                break;
            }
        }
    }

    return new_choice;
}

// Change the board according to user's choice
uint32_t changeBoard(uint32_t curr_state, uint32_t player, uint32_t choice)
{
    choice = choiceToConfig(choice, player);
    return curr_state + choice;
}

// Check whether the position on board is free
_Bool checkFreePosition(uint32_t config, uint32_t choice)
{
    for (uint32_t i = 0; i < (9 - choice); i++)
    {
        config = config/10;
    }

    uint32_t digit = config%10;
    if(digit == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// Choose a random bead from matchbox
enum billes randomBille(maillon_mb *mb)
{
    maillon_billes *m;
    maillon_billes *prev;

    srand(time(NULL));
    uint32_t nb = rand() % (mb->taken->size);
    uint32_t i = 0;

    m = mb->taken->head;

    while (i < nb && m != NULL)
    {
        prev = m;
        m = m->next;
        i++;
    }


    if(m!=NULL)
    {
        if (nb == 0)
        {
            mb->taken->head = m->next;
        }
        else
        {
            prev->next = m->next;
        }

        mb->taken->size -= 1;

        if(mb->taken->size == 0)
        {
            mb->taken->head = NULL;
        }

        addHeadBilles(mb->free, m);
        return m->bille;
    }

    else
    {
        return -1;
    }
}

// Print the state of board
void printBoard(uint32_t config)
{
    char grille[3][7];
    uint32_t i, j;

    // Fill in the boards
    for (i = 0; i < 3 ; i++)
    {
        for (j = 0; j < 7; j = j + 2)
        {
            grille[i][j] = '|';
        }
    }

    // Fill in x and o
    uint32_t tmp;
    uint32_t power = 100000000;

    for (i = 0; i <3; i++)
    {
        for (j = 1; j < 7; j = j + 2)
        {
            tmp = config / power;

            if (tmp == 2)
            {
                grille[i][j] = 'x';
            }
            else if (tmp == 1)
            {
                grille[i][j] = 'o';
            }
            else if (tmp == 0)
            {
                grille[i][j] = ' ';
            }
            else
            {
                grille[i][j] = '!';
            }

            if(tmp!=0)
                config=config-tmp*power;
            if(power!=1)
                power/=10;
        }
    }

    // Print the resulting board
    for (i = 0; i < 3; i++)
    {
        for ( j = 0; j < 7; j++)
        {
            printf("%c", grille[i][j]);
        }
        printf("\n");
    }


}

// Add billes to matchbox in case of victory
void modifyMbVictory(maillon_mb *mb, enum billes b)
{
    // 1 bille for replacement + 3
    for (uint32_t i = 0; i < 4; i++)
    {
        addHeadMb(mb, b);
    }
}

// Add billes to matchbox in case of draw
void modifyMbDraw(maillon_mb *mb, enum billes b)
{
    // 1 bille for replacement + 1
    addHeadMb(mb, b);
    addHeadMb(mb, b);
}

// Add billes to matchbox in case of loss
void modifyMbLoss(maillon_mb *mb, enum billes b)
{
    // 1 bille for replacement
    addHeadMb(mb, b);
}

uint32_t findLastEmpty(uint8_t **tab)
{
    uint8_t base[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (uint32_t i = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            if (tab[i][j] == 0)
            {
                return base[i][j];
            }
        }
    }
    return 0;
}

// Get free index for random game  
uint32_t getRandIndex(uint8_t** table)
{
    srand(time(NULL)); 
    uint32_t free=freePlacesPointer(table);
    uint32_t base[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    //printf("%d\n",free);
    uint32_t r[free]; 
    int tmp=0; 

    for(uint32_t i=0; i<3; i++){
        for(uint32_t j=0; j<3; j++){
            if(table[i][j]==0){
                r[tmp]=base[i][j]; 
                tmp++;
            }
        }
    }
    // for(int i=0; i<free; i++){
    //     printf("%d\n",r[i]);
    // }
    return r[rand()%free]; 
}

// mode: 1 - user/machine; 2 - machine/machine
void newGame(char *filename, uint32_t mode)
{
    FILE *file = fopen(filename, "rb");

    setbuf(stdout, 0);
    // Load file with matchboxes
    matchboxes *th = readGameState(file);

    // Print empty board
    printf("New game!\n");
    printBoard(0);

    // The choice of the bille
    uint32_t choice;

    // Current matchbox
    maillon_mb *curr_state = findMb(th, 0);

    // Current configuration
    uint32_t curr_config = curr_state->config;

    // To store used matchboxes and billes from them
    maillon_mb *mb_tab[5];
    enum billes billes_tab[5] = {0};
    enum billes curr_bille;
    uint32_t used_counter = 0;
    uint8_t **table = threeToTable(curr_config);
    

    // If user - machine
    if (mode == 1)
    {
        // turn: 2 - machine; 1 - user
        // Machine always plays first
        uint32_t turn = 2;

        // While the game is on
        while(1)
        {
            // If it' a turn of machine
            if (turn == 2)
            {
                // If there's only one place left on board (the case is not included into 304 matchboxes
                if (freePlacesPointer(table) == 1)
                {
                    // Put cross into the last free case
                    printf("Machine's move:\n");
                    curr_config = changeBoard(curr_config, turn, findLastEmpty(table));
                }
                else if(curr_state != NULL)
                {
                    // Get a random bead
                    curr_bille = randomBille(curr_state);
                    choice = getBilleIndex(curr_bille);

                    // Update the list of used maillons and billes
                    mb_tab[used_counter] = curr_state;
                    billes_tab[used_counter] = curr_bille;
                    used_counter++;

                    // Change the state of board

                    // If current configuration is a modification of current matchbox
                    if (curr_config != curr_state->config)
                    {
                        curr_config = changeBoard(curr_config, turn,
                                                  getBillesTransormation(curr_state, curr_config, choice));
                    }
                    // If a basic matchbox
                    else
                    {
                        curr_config = changeBoard(curr_config, turn, choice);
                    }

                    // Change the turn to player
                    turn = 1;

                    printf("Machine's move:\n");
                }
                
            }

            // If it' a turn of user
            else
            {
                // Get the choice of user and check whether the place is empty
                do
                {   // Free the standard entry 
                    fflush(stdin); 
                    printf("Choose the next move (1-9):\n");
                    scanf("%d", &choice);
                } while (!checkFreePosition(curr_config, choice) || (choice<0 || choice >9));

                // Change the state of board
                curr_config = changeBoard(curr_config, turn, choice);

                // Change the turn to machine
                turn = 2;
                
            }
            for(uint32_t k = 0; k < 3; k++)
            {
                free(table[k]);
            }
            free(table);
            table = threeToTable(curr_config);

            // Print the current state of board
            printBoard(curr_config);

            // If the player won
            if (isWinPointer(table) == 1)
            {
                printf("The player won!\n");

                //Update beads in matchboxes
                for (uint32_t i = 0; i < 5; i++)
                {
                    if (billes_tab[i] == 0)
                    {
                        break;
                    }
                    if (mb_tab[i]->taken->size == 0)
                    {
                        tableToBilles(mb_tab[i]);
                    }
                }
                break;
            }

            // If the machine won
            else if (isWinPointer(table) == 2)
            {
                printf("The machine won!\n");

                // Update beads in matchboxes
                for (uint32_t i = 0; i < 5; i++)
                {
                    if (billes_tab[i]!=0)
                        modifyMbVictory(mb_tab[i], billes_tab[i]);
                }
                break;
            }

            else
            {
                // There's no more places - draw
                if (freePlacesPointer(table) == 0)
                {
                    printf("Draw!\n");

                    // Update beads in matchboxes
                    for (uint32_t i = 0; i < 5; i++)
                    {
                        if (billes_tab[i]!=0)
                            modifyMbDraw(mb_tab[i], billes_tab[i]);
                    }
                    break;
                }
                // Change the matchbox (only after user's move)
                else if(turn == 2)
                { 
                    curr_state = findMb(th, curr_config);
                    // If configuration is not basic configuration
                    if (curr_state == NULL)
                    {
                        curr_state = findBaseConfiguration(th, curr_config);
                    }
                }
            }   
        }
         for(uint32_t k = 0; k < 3; k++)
        {
            free(table[k]);
        }
        free(table); 
    }

    // If machine - machine
    else
    {
        // turn: 2 - machine(tracked); 1 - machine
        // Machine always plays first
        uint32_t turn = 2;

        // While the game is on
        while(1)
        {
            // If it' a turn of machine
            if (turn == 2)
            {
                // If there's only one place left on board (the case is not included into 304 matchboxes
                if (freePlacesPointer(table) == 1)
                {
                    // Put cross into the last free case
                    printf("Machine's move:\n");
                    curr_config = changeBoard(curr_config, turn, findLastEmpty(table));
                }
                else if(curr_state != NULL)
                {
                    // Get a random bead
                    curr_bille = randomBille(curr_state);
                    choice = getBilleIndex(curr_bille);

                    // Update the list of used maillons and billes
                    mb_tab[used_counter] = curr_state;
                    billes_tab[used_counter] = curr_bille;
                    used_counter++;

                    // Change the state of board

                    // If current configuration is a modification of current matchbox
                    if (curr_config != curr_state->config)
                    {
                        curr_config = changeBoard(curr_config, turn,
                                                  getBillesTransormation(curr_state, curr_config, choice));
                    }
                        // If a basic matchbox
                    else
                    {
                        curr_config = changeBoard(curr_config, turn, choice);
                    }

                    // Change the turn to player
                    turn = 1;

                    printf("First machine's move:\n");
                }
            }

            // If it' a turn of user
            else
            {
                // Get the choice of user and check whether the place is empty
                // do
                // {
                //     srand(time(NULL));
                //     choice = rand() % 8 + 1;
                // } while (!checkFreePosition(curr_config, choice));
                choice=getRandIndex(table);
                // Change the state of board
                curr_config = changeBoard(curr_config, turn, choice);

                // Change the turn to machine
                turn = 2;

                printf("Second machine's move:\n");
            }
            // Free the memory
            for(uint32_t k = 0; k < 3; k++)
            {
                free(table[k]);
            }
            free(table);

            table = threeToTable(curr_config);

            // Print the current state of board
            printBoard(curr_config);

            // If the machine 2 won
            if (isWinPointer(table) == 1)
            {
                printf("The machine 2 won!\n");

                //Update beads in matchboxes
                for (uint32_t i = 0; i < 5; i++)
                {
                    if (billes_tab[i]!=0)
                    {
                        if (mb_tab[i]->taken->size == 0)
                        {
                            tableToBilles(mb_tab[i]);
                        }
                    }
                }
                break;
            }

            // If the machine 1 won
            else if (isWinPointer(table) == 2)
            {
                printf("The machine 1 won!\n");

                // Update beads in matchboxes
                for (uint32_t i = 0; i < 5; i++)
                {
                    if (billes_tab[i]!=0)
                        modifyMbVictory(mb_tab[i], billes_tab[i]);
                }
                break;
            }

            else
            {
                // There's no more places - draw
                if (freePlacesPointer(table) == 0)
                {
                    printf("Draw!\n");

                    // Update beads in matchboxes
                    for (uint32_t i = 0; i < 5; i++)
                    {
                        if (billes_tab[i]!=0)
                            modifyMbDraw(mb_tab[i], billes_tab[i]);
                    }
                    break;
                }

                // Change the matchbox (only after user's move)
                else if(turn == 2)
                {
                    curr_state = findMb(th, curr_config);
                    // If configuration is not basic configuration
                    if (curr_state == NULL)
                    {
                        curr_state = findBaseConfiguration(th, curr_config);
                    }
                }
            }
        }
        // Free the memory 
        for(uint32_t k = 0; k < 3; k++)
        {
            free(table[k]);
        }
        free(table);
        
    }
   
    

    fclose(file);
    FILE *f = fopen(filename, "w");

    writeGameState(f, th);

    fclose(f);
    freeHashTable(th);

}