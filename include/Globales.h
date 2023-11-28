#ifndef GLOBALES_H
#define GLOBALES_H

#include <LibRobus.h>
#include "Enums.h"

uint8_t g_etat = DEPART;

uint32_t g_debut_mouvement_bras = 0; // En ms, moment quand le mouvement à commencé
int32_t g_pulses_pour_tourner = 0; // Pulses necessaires pour completer la rotation actuelle

#endif // GLOBALES_H
