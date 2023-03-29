// External include
#include "stdlib.h"

// Internal include
#include "trap.h"

typedef struct
{
    uint8_t x;
    uint8_t y;
}trap_t;


trap_ptr_t trap_new(void)
{
    trap_t* trap_ptr = (trap_t*)malloc(sizeof(trap_t));
    coordinate_t random_coordinate = { 0 };
    coordinate_get_random(&random_coordinate);
    trap_ptr->x = random_coordinate.x;
    trap_ptr->y = random_coordinate.y;
    return (trap_ptr_t)trap_ptr;
}

void trap_delete(trap_ptr_t trap)
{
    free(trap);
}

bool_e trap_check(trap_ptr_t trap, coordinate_t coordinate_attempt)
{
    bool_e x_is_ok = (((trap_t*)trap)->x == coordinate_attempt.x);
    bool_e y_is_ok = (((trap_t*)trap)->y == coordinate_attempt.y);
    return x_is_ok && y_is_ok;
}