// External include
#include "config.h"

//Internal include
#include "player.h"



// Déclaration type privé
typedef struct
{
    coordinate_t pos;
    uint8_t size_map_x;
    uint8_t size_map_y;
}player_t;


// Variable privée
static player_t player = { 0 };


void player_init(void)
{
    coordinate_get_random(&player.pos);
}

bool_e player_move(uint8_t dx, uint8_t dy)
{
    /* Valeur de retour, par défaut on échoue à se déplacer */
    bool_e ret = FALSE;

    /* Position après déplacement */
    int8_t new_x = dx + player.pos.x;
    int8_t new_y = dy + player.pos.y;

    /* Check si on est bien dans le tableau */
    if( (new_x >= 0) &&
        (new_x < MAP_WIDTH) &&
        (new_y >= 0) &&
        (new_y < MAP_HEIGHT) )
    {
        player.pos.x = new_x;
        player.pos.y = new_y;
        ret = TRUE;
    }

    return ret;
}

coordinate_t player_get_pos(void)
{
    return player.pos;
}

