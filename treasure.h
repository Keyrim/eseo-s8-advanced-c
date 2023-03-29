#ifndef TREASURE_H
#define TREASURE_H

#include "common.h"
#include "coordinate.h"

void treasure_refresh_pos(void);

bool_e treasure_is_coordinate_right(coordinate_t coordinate_t);

#endif /* TREASURE_H */