#ifndef TRAP_H
#define TRAP_H

// Internal include
#include "coordinate.h"
#include "common.h"

// Déclaration type publique
typedef void* trap_ptr_t;

// Création d'un piège
trap_ptr_t trap_new(void);

// Suppresion d'un piège
void trap_delete(trap_ptr_t trap);

bool_e trap_check(trap_ptr_t trap, coordinate_t coordinate_attempt);

#endif /* TRAP_H */