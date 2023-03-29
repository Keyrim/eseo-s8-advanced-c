// External include
#include "stdlib.h"
#include "config.h"

// Internal include
#include "coordinate.h"


void coordinate_get_random(coordinate_t* random_coordinate)
{
    random_coordinate->x = rand() % MAP_WIDTH;
    random_coordinate->y = rand() % MAP_HEIGHT;
}