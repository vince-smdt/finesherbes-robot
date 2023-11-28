#ifndef GLOBALES_H
#define GLOBALES_H

#include <LibRobus.h>
#include "Enums.h"

uint8_t g_etat = DEPART;

// Bras
uint32_t g_debut_mouvement_bras = 0; // En ms, moment quand le mouvement à commencé

// Pathfinding
int32_t g_pulses_pour_tourner = 0; // Pulses necessaires pour completer la rotation actuelle
uint32_t g_debut_sortie_de_ligne = 0; // En ms, délai depuis que le robot a franchi une ligne
uint8_t g_rangee_cible = 0;
uint8_t g_rangee_actuelle = 0;
uint8_t g_cote = 0; // Côté où se trouve la table
uint8_t g_table = 0;
bool g_devant_table = false; // Si on est directement devant la table du client

#endif // GLOBALES_H
