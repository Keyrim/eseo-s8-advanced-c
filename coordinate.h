#ifndef COORDINATE_H
#define COORDINATE_H

#include "stdint.h"

typedef struct
{
    uint8_t x;
    uint8_t y;
}coordinate_t;

void coordinate_get_random(coordinate_t* random_coordinate);


#endif /* COORDINATE_H */