#ifndef GLOBALES_H
#define GLOBALES_H

#include <LibRobus.h>
#include <Queue.h>
#include "Constantes.h"
#include "Enums.h"
#include "Types.h"
#include <SoftwareSerial.h>

uint8_t g_etat = DEPART;
uint8_t g_action = CHERCHER_COMMANDE;

// Serial
HardwareSerial& SerialPrint = Serial;
HardwareSerial& SerialBluetooth = Serial3;

// Bluetooth
uint32_t g_debut_recv_data_ble = 0; // En ms, derniere fois que le robot a reçu des données BLE

// Commandes
Queue<Commande*> g_file_commandes;

// Bras
uint32_t g_debut_mouvement_bras = 0; // En ms, moment quand le mouvement à commencé

// Pathfinding
int32_t g_pulses_pour_tourner = 0; // Pulses necessaires pour completer la rotation actuelle
uint32_t g_debut_sortie_de_ligne = 0; // En ms, délai depuis que le robot a franchi une ligne
uint32_t g_debut_deplacement_hardcode = 0; // En ms, deplacements fixes
uint8_t g_cote_client = 0; // Côté où se trouve la table
uint8_t g_cote_cuisine = 0;
int8_t g_rangee_cible = 0; // Les rangées peuvent être négatives, rangée 0 représente le point central entre tables client et cuisine
int8_t g_colonne_cible = 3;
int8_t g_rangee_actuelle = 1;
int8_t g_colonne_actuelle = 3;
Commande* g_commande = nullptr;

#endif // GLOBALES_H
