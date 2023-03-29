// External include
#include "stddef.h"
#include "map.h"
#include "treasure.h"
#include "player.h"
#include "stdlib.h"
#include "config.h"
#include "stdio.h"
#include "trap.h"

// Internal include
#include "sm.h"


// Déclaration des états
typedef enum
{
    SM_STATE_INIT = 0,
    SM_STATE_GET_INPUT,
    SM_STATE_MOVE,
    SM_STATE_CHECK_VICTORY,
    SM_STATE_COUNT
}sm_state_e;

// Déclaration des actions possibles
typedef enum
{
    // On ne fait rien
    SM_ACTION_NOP = 0,
    // On reset l'emplacement du terrain, on reset la position du joueur
    // et on passe dans l'état "GET_INPUT"
    SM_ACTION_INIT,
    // On retourne juste en attente d'input
    SM_ACTION_WAIT_INPUT,
    // On arrête de jouer
    SM_ACTION_QUIT,
    // Déplacement vers le haut
    SM_ACTION_MOVE_UP,
    // Déplacement vers le bas
    SM_ACTION_MOVE_DOWN,
    // Déplacement à gauche
    SM_ACTION_MOVE_LEFT,
    // Déplacement à droite
    SM_ACTION_MOVE_RIGHT,
    // On vérifie qu'on a gagné et on passe en état "SM_STATE_CHECK_VICTORY"
    SM_ACTION_CHECK_VICTORY,
    // Nombre d'actions possibles
    SM_ACTION_COUNT
}sm_action_e;

// Déclaration d'un type pointeur sur fonction
typedef void (*action_t)(void);


// Déclaration des fonctions privées
static void sm_init_traps(void);
static void sm_clear_traps(void);
static void sm_move(int8_t dx, int8_t dy);

static void sm_action_init(void);
static void sm_action_wait_input(void);
static void sm_action_quit(void);
static void sm_action_move_up(void);
static void sm_action_move_down(void);
static void sm_action_move_left(void);
static void sm_action_move_right(void);
static void sm_action_check_victory(void);



// Association sm_action_e (enum action) avec sm_action_t (fonction action)
static action_t action_function[SM_ACTION_COUNT] =
{
    [SM_ACTION_NOP] = NULL,
    [SM_ACTION_INIT] = sm_action_init,
    [SM_ACTION_WAIT_INPUT] = sm_action_wait_input,
    [SM_ACTION_QUIT] = sm_action_quit,
    [SM_ACTION_MOVE_UP] = sm_action_move_up,
    [SM_ACTION_MOVE_DOWN] = sm_action_move_down,
    [SM_ACTION_MOVE_LEFT] = sm_action_move_left,
    [SM_ACTION_MOVE_RIGHT] = sm_action_move_right,
    [SM_ACTION_CHECK_VICTORY] = sm_action_check_victory,
};

// Associations state + event => actions
static sm_action_e action[SM_STATE_COUNT][SM_EVENT_COUNT] =
{
    // Pour initialier la machine à état
    [SM_STATE_INIT][SM_EVENT_NEXT] = SM_ACTION_INIT,

    // Actions lors d'un appuie sur une touche
    [SM_STATE_GET_INPUT][SM_EVENT_UP] = SM_ACTION_MOVE_UP,
    [SM_STATE_GET_INPUT][SM_EVENT_DOWN] = SM_ACTION_MOVE_DOWN,
    [SM_STATE_GET_INPUT][SM_EVENT_LEFT] = SM_ACTION_MOVE_LEFT,
    [SM_STATE_GET_INPUT][SM_EVENT_RIGHT] = SM_ACTION_MOVE_RIGHT,
    [SM_STATE_GET_INPUT][SM_EVENT_QUIT] = SM_ACTION_QUIT,

    // Action de check de victoire qui suit la réalisation d'un déplacement
    [SM_STATE_MOVE][SM_EVENT_NEXT] = SM_ACTION_CHECK_VICTORY,

    // Si on gagne on recommence sinon on attend la prochaine input
    [SM_STATE_CHECK_VICTORY][SM_EVENT_LOSE] = SM_ACTION_WAIT_INPUT,
    [SM_STATE_CHECK_VICTORY][SM_EVENT_WIN] = SM_ACTION_INIT
};

// Tableau pour stocker les pièges
static trap_ptr_t traps[NB_TRAP] = { 0 };
// Etat de la machine à état
static sm_state_e sm_state = SM_STATE_INIT;

static void sm_init_traps(void)
{
    static bool_e are_traps_created = FALSE;
    if(are_traps_created)
    {
        sm_clear_traps();
    }
    uint8_t t = NB_TRAP;
    while(t--)
    {
        traps[t] = trap_new();
    }
    are_traps_created = TRUE;
}


static void sm_clear_traps(void)
{
    uint8_t t = NB_TRAP;
    while(t--)
    {
        trap_delete(traps[t]);
    }
}

// Définitions des fonctions privées
static void sm_action_init(void)
{
    map_clear();
    sm_init_traps();
    treasure_refresh_pos();
    player_init();
    map_set_car(CHAR_PLAYER, player_get_pos());
    map_print();
    printf("Commençons à jouer !\r\n");
    sm_action_wait_input();
}

static void sm_action_wait_input(void)
{
    printf("Entrez une commande ");
    sm_state = SM_STATE_GET_INPUT;
}

static void sm_action_quit(void)
{
    sm_clear_traps();
    printf("\r\nFin du jeu.\r\n");
    exit(0);
}


static void sm_move(int8_t dx, int8_t dy)
{
    coordinate_t previous_player_coordinate = player_get_pos();
    if( player_move(dx, dy) )
    {
        map_set_car(' ', previous_player_coordinate);
        map_set_car(CHAR_PLAYER, player_get_pos());
        map_print();
        sm_state = SM_STATE_MOVE;
        sm_run(SM_EVENT_NEXT);
    }
}

static void sm_action_move_up(void)
{
    sm_move(0, -1);
}
static void sm_action_move_down(void)
{
    sm_move(0, 1);
}
static void sm_action_move_left(void)
{
    sm_move(-1, 0);
}
static void sm_action_move_right(void)
{
    sm_move(1, 0);
}

static void sm_action_check_victory(void)
{
    sm_state = SM_STATE_CHECK_VICTORY;
    if( treasure_is_coordinate_right(player_get_pos()) == TRUE )
    {
        sm_run(SM_EVENT_WIN);
    }
    else
    {
        sm_run(SM_EVENT_LOSE);
    }
}


// Définitions des fonctions publiques
void sm_run(sm_event_e event)
{
    if(action[sm_state][event] != SM_ACTION_NOP)
    {
        action_function[ action[sm_state][event] ]();
    }
}