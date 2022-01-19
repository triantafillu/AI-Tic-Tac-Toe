//
// Created by alexa on 12/30/2021.
//
#include "matchboxes.h"
#ifndef PROJET_GAME_H
#define PROJET_GAME_H

_Bool isColumn(uint8_t table[3][3], uint32_t val);
_Bool isRow(uint8_t table[3][3], uint32_t val);
_Bool isDiagonal(uint8_t table[3][3], uint32_t val);
uint32_t isWin(uint8_t table[3][3]);
uint32_t isWinPointer(uint8_t **table);
_Bool isValid(uint8_t table[3][3]);
void generateNewGame(FILE * file);
uint32_t changeBoard(uint32_t curr_state, uint32_t player, uint32_t choice);
void printBoard(uint32_t config);
_Bool checkFreePosition(uint32_t config, uint32_t choice);
void newGame(char *filename, uint32_t mode);
#endif //PROJET_GAME_H
