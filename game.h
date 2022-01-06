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
_Bool isValid(uint8_t table[3][3]);
void generateNewGame(FILE * file);
#endif //PROJET_GAME_H
