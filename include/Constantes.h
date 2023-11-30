#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <LibRobus.h>

// Bluetooth
const uint8_t DELAI_RECV_DATA_BLE = 100; // En ms, delai de temps avant de recevoir les prochaines données bluetooth

// Pathfinding
const float VITESSE_MAX = 0.3;
const float VITESSE_RECULONS = -0.3;
const uint16_t POSITION_CENTRE_LIGNE = 3500; // Position du robot voulue sur la ligne (0-7000)
const uint8_t DELAI_SORTIE_DE_LIGNE = 250; // Après avoir franchi une ligne, temps que ça prend avant de redétecter des lignes pour sortir de la ligne actuelle
const uint8_t NB_CAPTEURS_SUIVEUR_LIGNE = 8;
const uint8_t NB_LECTURES_SUIVEUR_LIGNE = 4; //Calcul la moyenne de 4 lectures d'un capteur pour normaliser la valeur

// Pins
const uint8_t SUIVEUR_LIGNE_EMITTER_PIN = QTR_NO_EMITTER_PIN; //Pas d'emetteur
const uint8_t SUIVEUR_LIGNE_LUMIERE_PIN = 13;

// Limites
const uint8_t TABLE_MIN = 1;
const uint8_t TABLE_MAX = 6;
const uint8_t PLAT_MIN = 1;
const uint8_t PLAT_MAX = 4;

#endif // CONSTANTES_H