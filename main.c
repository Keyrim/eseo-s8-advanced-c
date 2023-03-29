#include "stdio.h"
#include "map.h"
#include "player.h"
#include "getch.h"
#include "sm.h"

#define EVENT_INVALID_CHAR  255

static sm_event_e event_from_input(char input)
{
    sm_event_e ret = EVENT_INVALID_CHAR;
    switch(input)
    {
        case 'i':
        case 'I':
            ret = SM_EVENT_UP;
            break;
        case 'k':
        case 'K':
            ret = SM_EVENT_DOWN;
            break;
        case 'l':
        case 'L':
            ret = SM_EVENT_RIGHT;
            break;
        case 'j':
        case 'J':
            ret = SM_EVENT_LEFT;
            break;
        case 'q':
        case 'Q':
            ret = SM_EVENT_QUIT;
            break;
    }
    return ret;
}

int main(int argc, char* argv[])
{
    // Initialisation des modules
    map_init();

    sm_run(SM_EVENT_NEXT);

    // Boucle
    for(;;)
    {
        // Get next move
        sm_event_e event = event_from_input(getch());
        if(event != EVENT_INVALID_CHAR)
        {
            sm_run(event);
        }
    }
    return 0;
}
