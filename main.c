#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matchboxes.h"
#include "hashtable.h"
#include "aide_projet.h"
#include "game.h"

void printMenu()
{
    printf("\nChoose an option!\n");
    printf("1. Play against the machine.\n");
    printf("2. Make the machine \"smarter\".\n");
    printf("3. Start the learning from scratch.\n");
    printf("4. Exit.\n");
    printf("\n");
}

int main()
{

    setbuf(stdout, 0);
    uint32_t option;
    uint32_t n;

    while(1)
    {
        printMenu();
        scanf("%d", &option);

        switch(option)
        {
            case 1:
            {
                newGame("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\new_game.txt", 1);
                break;
            }

            case 2:
            {
                printf("How many games against itself you want the machine to play?\n");
                scanf("%d", &n);

                for (uint32_t i = 0; i < n; i++)
                {
                    printf("Game #%d\n", i+1);
                    newGame("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\new_game.txt", 2);
                    printf("\n");
                }
                break;
            }

            case 3:
            {
                FILE *new_file = fopen("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\new_game.txt", "w");
                generateNewGame(new_file);
                fclose(new_file);
                printf("The new file is created.\n");

                break;
            }

            case 4:
            {
                break;
            }

            default:
            {
                printf("There is no such option!\n");
            }
        }

        if (option == 4)
        {
            break;
        }
    }

    return 0;
}
