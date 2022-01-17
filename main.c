#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "matchboxes.h"
#include "hashtable.h"
#include "aide_projet.h"
#include "game.h"


int main() {
   /* uint8_t table[3][3] = {{2, 1, 1},
                            {1, 2, 1},
                            {0, 1, 2}};

    uint32_t w = isWin(table);*/

    FILE* in = fopen("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\new_game.txt", "rb");
    FILE* out = fopen("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\write.txt", "w");
    /*FILE* out = fopen("C:\\Users\\alexa\\Desktop\\Uni\\Structures\\Projet\\gs_out.csv", "w");
    matchbox** mb = initializeMatchboxes();
    writeGameState(out, mb);
    fclose(out);

    // 210122020*/

    //uint8_t g[3][3] = {{2, 1, 0}, {1, 2, 2}, {0, 2, 0}};
    //checkFreePosition(tableTo3(g), 3);
    //uint32_t res = changeBoard(tableTo3(g), 3);
//
    //print_all_transformations_1d(g, in);
//    while(next_configuration(g)==0)
//    {
//        if (isValid(g))
//        {
//            print_all_transformations_1d(g, in);
//        }
//    }

//    matchboxes *th = readGameState(in);
//    writeGameState(out, th);
    //generateNewGame(in);




    //print_all_transformations_1d(g, in);


    newGame(in, out, 1);
    return 0;
}
