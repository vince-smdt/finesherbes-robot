#ifndef GLOBALES_H
#define GLOBALES_H

#include <LibRobus.h>
#include "Enums.h"

uint8_t g_etat = DEPART;

// Bras
uint32_t g_debut_mouvement_bras = 0; // En ms, moment quand le mouvement à commencé

// Pathfinding
uint32_t g_debut_sortie_de_ligne = 0; // En ms, délai depuis que le robot a franchi une ligne
int32_t g_pulses_pour_tourner = 0; // Pulses necessaires pour completer la rotation actuelle
bool g_bonne_rangee = false; // Si on est dans la même rangée que la table client cible
bool g_devant_table = false; // Si on est directement devant la table du client

#endif // GLOBALES_H
