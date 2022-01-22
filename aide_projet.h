//
// Created by alexa on 12/26/2021.
//

#ifndef PROJET_AIDE_PROJET_H
#define PROJET_AIDE_PROJET_H

typedef enum transformation{ID, ROT_90, ROT_180, ROT_270, MIROIR_VERT, MIROIR_HORIZ} transformation;
void appliquer_transformation_base(uint8_t grille[3][3], transformation t);
void appliquer_transformation_base_pointer(uint8_t **grille, transformation tr);
uint8_t next_configuration(uint8_t grille[3][3]);
_Bool isConfiguration(uint32_t t1, uint32_t t2);
void getConfigurations(uint32_t config, uint32_t tab[7]);


#endif //PROJET_AIDE_PROJET_H

