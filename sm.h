#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


typedef enum
{
    SM_EVENT_UP = 0,
    SM_EVENT_DOWN,
    SM_EVENT_LEFT,
    SM_EVENT_RIGHT,
    SM_EVENT_QUIT,
    SM_EVENT_NEXT,     // Utilisation réservée en terme de la machine à état
    SM_EVENT_WIN,
    SM_EVENT_LOSE,
    SM_EVENT_COUNT
}sm_event_e;

void sm_run(sm_event_e event);

#endif /* STATE_MACHINE_H */