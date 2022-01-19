//
// Created by alexa on 12/30/2021.
//
#include "matchboxes.h"
#ifndef PROJET_GAME_H
#define PROJET_GAME_H

_Bool isColumn(uint8_t table[3][3], uint32_t val);
_Bool isColumnPointer(uint8_t **table, uint32_t val);
_Bool isRow(uint8_t table[3][3], uint32_t val);
_Bool isRowPointer(uint8_t **table, uint32_t val);
_Bool isDiagonal(uint8_t table[3][3], uint32_t val);
_Bool isDiagonalPointer(uint8_t **table, uint32_t val);
uint32_t isWin(uint8_t table[3][3]);
uint32_t isWinPointer(uint8_t **table);
_Bool isValid(uint8_t table[3][3]);
void generateNewGame(FILE * file);
uint32_t choiceToConfig(uint32_t choice, uint32_t player);
uint32_t getBillesTransormation(maillon_mb *mb, uint32_t config, uint32_t choice);
_Bool checkFreePosition(uint32_t config, uint32_t choice);
enum billes randomBille(maillon_mb *mb);
uint32_t changeBoard(uint32_t curr_state, uint32_t player, uint32_t choice);
void printBoard(uint32_t config);
_Bool checkFreePosition(uint32_t config, uint32_t choice);
void modifyMbVictory(maillon_mb *mb, enum billes b);
void modifyMbDraw(maillon_mb *mb, enum billes b);
uint32_t findLastEmpty(uint8_t **tab);
void newGame(char *filename, uint32_t mode);
#endif //PROJET_GAME_H
