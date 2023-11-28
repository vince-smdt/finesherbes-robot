#ifndef COMMANDE_H
#define COMMANDE_H

#include <LibRobus.h>
#include "SuiveurLigne.h"
#include "BLEFinesHerbes.h"

void chercher_commande();
void livraison();
void retourBase();

void chercher_commande()
{
  switch (g_etat) {
    case ATTENDRE_PROCHAINE_COMMANDE: {
      // g_commande = liste_Commandes.front();
      // liste_Commandes.pop();
      g_commande.NumTable = 1;
      g_commande.NumPlat = 4;

      g_colonne_cible = g_commande.NumPlat + (g_commande.NumPlat > 2); // Pour les plats 3&4, leur colonne et 4&5 donc on l'incrémente

      g_cote_cuisine = (g_commande.NumPlat < 3) ? LEFT : RIGHT;
      commencerTourner(g_cote_cuisine, 90);
      g_etat = TOURNER_VERS_COTE_TABLE_CUISINE;
      break;
    }

    case TOURNER_VERS_COTE_TABLE_CUISINE: {
      if (finiTourner()) {
        Serial.println("SUIVRE_LIGNE_VERS_COLONNE_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_COLONNE_CUISINE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_COLONNE_CUISINE: {
      if (suivreLigne())
        g_colonne_actuelle += (g_cote_cuisine == LEFT) ? -1 : 1;

      if (g_colonne_actuelle == g_colonne_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(!g_cote_cuisine, 90);
        Serial.println("TOURNER_VERS_TABLE_CUISINE");
        g_etat = TOURNER_VERS_TABLE_CUISINE;
      }
      break;
    }

    case TOURNER_VERS_TABLE_CUISINE: {
      if (finiTourner()) {
        Serial.println("SUIVRE_LIGNE_VERS_TABLE_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_TABLE_CUISINE;
        g_rangee_cible = -1;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_TABLE_CUISINE: {
      if (suivreLigne())
        g_rangee_actuelle--;

      if (g_rangee_actuelle == g_rangee_cible) {
        arret();
        Serial.println("PRET_DEPOSER_PLATEAU");
        g_etat = PRET_DEPOSER_PLATEAU;
      }
      break;
    }

    case SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU: {
      if (suivreLigne())
        g_rangee_actuelle--;

      if (g_rangee_actuelle == g_rangee_cible) {
        arret();
        Serial.println("PRET_LEVER_PLATEAU");
        g_etat = PRET_LEVER_PLATEAU;
      }
      break;
    }
  }
}

void livraison()
{
  switch (g_etat) {
    case INITIER_DEPART_COMMANDE: {
      Serial.println("INITIER_COMMANDE");
      chercher_commande();
      g_rangee_cible = round(g_commande.NumTable/2.0);
      g_cote_client = g_commande.NumTable%2;

      Serial.println("SUIVRE_LIGNE_VERS_RANGEE");
      g_etat = SUIVRE_LIGNE_VERS_RANGEE;
      break;
    }

    case SUIVRE_LIGNE_VERS_RANGEE: {
      suivreLigne();
      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(g_cote_client, 90);
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
        Serial.println("ATTENDRE_PROCHAINE_COMMANDE");
        g_etat = ATTENDRE_PROCHAINE_COMMANDE;
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
        commencerTourner(!g_cote_client, 90);
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
      if (suivreLigne())
        g_rangee_actuelle--;

      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        Serial.println("ATTENDRE_PROCHAINE_COMMANDE");
        g_etat = ATTENDRE_PROCHAINE_COMMANDE;
      }
      break;
    }
  }
}

#endif // COMMANDE_H
