#ifndef MAP_H
#define MAP_H

#include "stdint.h"
#include "coordinate.h"

void map_init(void);
void map_print(void);
char map_get_char(coordinate_t coordinate);
void map_set_car(char c, coordinate_t coordinate);
void map_get_size(uint8_t* nb_column, uint8_t* nb_ligne);
void map_clear(void);



#endif /* MAP_H */