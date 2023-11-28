#ifndef COMMANDE_H
#define COMMANDE_H

#include <LibRobus.h>
#include "SuiveurLigne.h"

void setTable();
void pickCommande();
void livraison();
void retourBase();

void setTable()
{
  g_table = 1;
}

int getPlat()
{
  return 1;
}

void pickCommande()
{
  //ramasse la commande
  //hardcode?
}

void livraison()
{
  switch (g_etat) {
    case INITIER_COMMANDE: {
      Serial.println("INITIER_COMMANDE");
      setTable();
      g_rangee_cible = round(g_table/2.0);
      g_cote = g_table%2;

      Serial.println("SUIVRE_LIGNE_VERS_RANGEE");
      g_etat = SUIVRE_LIGNE_VERS_RANGEE;
      break;
    }

    case SUIVRE_LIGNE_VERS_RANGEE: {
      suivreLigne();
      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(g_cote, 90);
        g_etat = TOURNER_VERS_TABLE_CLIENT;
      }
      break;
    }

    case TOURNER_VERS_TABLE_CLIENT: {
      if (finiTourner()) {
        Serial.println("SUIVRE_LIGNE_VERS_TABLE");
        g_etat = SUIVRE_LIGNE_VERS_TABLE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_TABLE: {
      suivreLigne();
      if (g_devant_table) {
        commencerTourner(!g_cote, 180);
        Serial.println("TOURNER_VERS_LIGNE_CENTRALE");
        g_etat = TOURNER_VERS_LIGNE_CENTRALE;
      }
      break;
    }
  }
}

void retourBase() {
  switch (g_etat) {
    case TOURNER_VERS_LIGNE_CENTRALE: {
      if (finiTourner()) {
        Serial.println("SUIVRE_LIGNE_VERS_TABLE");
        g_etat = SUIVRE_LIGNE_VERS_LIGNE_CENTRALE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE: {
      suivreLigne();
      if (!g_devant_table) {
        commencerTourner(!g_cote, 90);
        Serial.println("TOURNER_VERS_CUISINE");
        g_etat = TOURNER_VERS_CUISINE;
      }
      break;
    }

    case TOURNER_VERS_CUISINE: {
      if (finiTourner()) {
        g_rangee_cible = 0;
        Serial.println("SUIVRE_LIGNE_VERS_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_CUISINE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_CUISINE: {
      suivreLigne();
      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        arret();
        debug_beep(5, 25);
        delay(10000);
      }
      break;
    }
  }
}

#endif // COMMANDE_H
