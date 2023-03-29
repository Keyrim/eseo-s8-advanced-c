#ifndef PLAYER_H
#define PLAYER_H

#include "stdint.h"
#include "coordinate.h"
#include "common.h"

void player_init(void);
bool_e player_move(uint8_t dx, uint8_t dy);
coordinate_t player_get_pos(void);



#endif /* PLAYER_H */