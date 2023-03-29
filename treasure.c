// External include
#include "stdlib.h"
#include "config.h"

// Internal include
#include "treasure.h"

static coordinate_t treasure_coordinate = { 0 };

void treasure_refresh_pos(void)
{
    coordinate_get_random(&treasure_coordinate);
}

bool_e treasure_is_coordinate_right(coordinate_t coordinate_attempt)
{
    bool_e x_is_ok = (treasure_coordinate.x == coordinate_attempt.x);
    bool_e y_is_ok = (treasure_coordinate.y == coordinate_attempt.y);
    return x_is_ok && y_is_ok;
}