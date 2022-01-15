//
// Created by alexa on 12/26/2021.
//

#include "hashtable.h"
#include "aide_projet.h"
#ifndef PROJET_MATCHBOXES_H
#define PROJET_MATCHBOXES_H

uint32_t tableTo3(uint8_t table[3][3]);
uint32_t translate10 (uint32_t table);
uint32_t translate3(uint32_t number);
enum billes getBille(uint32_t ind);
enum billes *tableToBilles(uint8_t table[3][3], uint32_t size);
uint32_t freePlaces(uint8_t table[3][3]);
uint32_t freePlacesPointer(uint8_t **table);
//matchbox ** initializeMatchboxes();
uint8_t** threeToTable(uint32_t three);
const char* getCaseCSV(char* line, int num);
matchboxes * readGameState(FILE* file);
void writeGameState(FILE * file, matchboxes *mb);
void printConfigToBilles(FILE * file, uint8_t config[3][3]);
uint32_t tableTo3Pointer(uint8_t **table);

#endif //PROJET_MATCHBOXES_H
