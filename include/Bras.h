#ifndef BRAS_H
#define BRAS_H

#include <LibRobus.h>
#include "General.h"
#include "Globales.h"
#include "Enums.h"

const uint8_t SERVO_BRAS_ID = 0;
const uint8_t ANGLE_SERVO_DEPOSER = 130;
const uint8_t ANGLE_SERVO_LEVER = 180;
const uint16_t DELAI_SERVO_BRAS = 1500;
const uint16_t DELAI_DEPOSER_PLATEAU = 5;

void setup_plateau();
void lever_plateau();
void deposer_plateau();

void setup_plateau()
{
  SERVO_Enable(SERVO_BRAS_ID);
  deposer_plateau();
}

void lever_plateau()
{
  switch (g_etat) {
    // Initiation de la rotation du servo
    case PRET_LEVER_PLATEAU: {
      g_debut_mouvement_bras = millis();
      SERVO_SetAngle(SERVO_BRAS_ID, ANGLE_SERVO_LEVER);
      g_etat = LEVER_PLATEAU;
      break;
    }

    // Attente de la fin de la rotation du servo
    case LEVER_PLATEAU: {
      if (temps_ecoule(g_debut_mouvement_bras) > DELAI_SERVO_BRAS)
        g_etat = FINI_LEVER_PLATEAU;
      break;
    }

    // On specifie le nouvel etat du robot
    case FINI_LEVER_PLATEAU: {
      g_debut_sortie_de_ligne = millis();

      if (g_action == CHERCHER_COMMANDE) {
        g_debut_deplacement_hardcode = millis();
        g_etat = RECULER_DANS_CUISINE;
        g_rangee_cible = -1;
        g_colonne_cible = 3;
        Serial.println("RECULER_DANS_CUISINE");
      }
      else if (g_action == LIVRAISON) {
        g_colonne_cible = (g_cote_client == LEFT) ? 1 : 5;
        Serial.println("SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT");
        g_etat = SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT;
      }
      break; 
    }
  }
}

void deposer_plateau()
{
  switch (g_etat) {
    // Initiation de la rotation du servo
    case PRET_DEPOSER_PLATEAU: {
      g_debut_mouvement_bras = millis();
      SERVO_SetAngle(SERVO_BRAS_ID, ANGLE_SERVO_DEPOSER);
      g_etat = DEPOSER_PLATEAU;
      break;
    }

    // Attente de la fin de la rotation du servo
    case DEPOSER_PLATEAU: {
      if (temps_ecoule(g_debut_mouvement_bras) > DELAI_SERVO_BRAS)
        g_etat = FINI_DEPOSER_PLATEAU;
      break;
    }

    // On specifie le nouvel etat du robot
    case FINI_DEPOSER_PLATEAU: {
      g_debut_sortie_de_ligne = millis();

      if (g_action == CHERCHER_COMMANDE) {
        g_rangee_cible = -2;
        g_etat = SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE;
      }
      else if (g_action == LIVRAISON) {
        arret();
        debug_beep(5, 25);
        delay(60000);
      }
      break;
    }
  }
}

#endif // BRAS_H
