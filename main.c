#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "aide_projet.c"
#include "arraylist.c"
#include "game.c"





int main() {
    uint8_t table[3][3] = {{2, 1, 1},
                            {1, 2, 1},
                            {0, 1, 2}};

    uint32_t w = isWin(table);
    // 210122020
    return 0;
}
