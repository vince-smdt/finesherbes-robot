#ifndef COMMANDE_H
#define COMMANDE_H

#include <LibRobus.h>
#include "SuiveurLigne.h"

void chercher_commande();
void livraison();
void retourBase();

void chercher_commande()
{
  switch (g_etat) {
    case ATTENDRE_PROCHAINE_COMMANDE: {
      arret();

      if (g_file_commandes.size() > 0) {
        // On prend la prochaine commande
        if (g_commande)
          delete g_commande;
        g_commande = g_file_commandes.front();
        g_file_commandes.pop();

        // On vérifie que la commande contient des valeurs valides
        if (g_commande->NumPlat < PLAT_MIN || g_commande->NumPlat > PLAT_MAX
            || g_commande->NumTable < TABLE_MIN || g_commande->NumTable > TABLE_MAX) {
              SerialPrint.print("VALEURS DE COMMANDE INVALIDE: Plat - ");
              SerialPrint.print(g_commande->NumPlat);
              SerialPrint.print(", Table - ");
              SerialPrint.println(g_commande->NumTable);

              debug_beep(3, 1000);
              break;
         }

        g_colonne_cible = g_commande->NumPlat + (g_commande->NumPlat > 2); // Pour les plats 3&4, leur colonne et 4&5 donc on l'incrémente
        g_cote_cuisine = (g_commande->NumPlat < 3) ? RIGHT : LEFT;

        commencerTourner(g_cote_cuisine, 90);
        SerialPrint.println("TOURNER_VERS_COTE_TABLE_CUISINE");
        g_etat = TOURNER_VERS_COTE_TABLE_CUISINE;
      }
      break;
    }

    case TOURNER_VERS_COTE_TABLE_CUISINE: {
      if (finiTourner()) {
        SerialPrint.println("SUIVRE_LIGNE_VERS_COLONNE_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_COLONNE_CUISINE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_COLONNE_CUISINE: {
      if (suivreLigne(VITESSE_MAX)) {
        g_colonne_actuelle += (g_cote_cuisine == LEFT) ? 1 : -1;
        SerialPrint.println(g_colonne_actuelle);
      }

      if (g_colonne_actuelle == g_colonne_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(!g_cote_cuisine, 90);
        SerialPrint.println("TOURNER_VERS_TABLE_CUISINE");
        g_etat = TOURNER_VERS_TABLE_CUISINE;
      }
      break;
    }

    case TOURNER_VERS_TABLE_CUISINE: {
      if (finiTourner()) {
        SerialPrint.println("SUIVRE_LIGNE_VERS_TABLE_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_TABLE_CUISINE;
        g_rangee_cible = -1;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_TABLE_CUISINE: {
      if (suivreLigne(VITESSE_MAX))
        g_rangee_actuelle--;

      if (g_rangee_actuelle == g_rangee_cible) {
        arret();
        SerialPrint.println("PRET_DEPOSER_PLATEAU");
        g_etat = PRET_DEPOSER_PLATEAU;
      }
      break;
    }

    case SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE: {
      if (suivreLigne(VITESSE_MAX))
        g_rangee_actuelle--;

      if (g_rangee_actuelle == g_rangee_cible) {
        arret();
        SerialPrint.println("PRET_LEVER_PLATEAU");
        g_etat = PRET_LEVER_PLATEAU;
      }
      break;
    }

    case RECULER_DANS_CUISINE: {
      avancer(-0.1, -0.1);
      
      if (temps_ecoule(g_debut_deplacement_hardcode) > 1500) {
        arret();
        g_rangee_actuelle++;
        commencerTourner(LEFT, 180);
        SerialPrint.println("TOURNER_VERS_SORTIE_CUISINE");
        g_etat = TOURNER_VERS_SORTIE_CUISINE;
      }
      break;
    }

    case TOURNER_VERS_SORTIE_CUISINE:{
      if (finiTourner())
      {
        arret();
        g_action = LIVRAISON;
        g_rangee_cible = 0;
        SerialPrint.println("SUIVRE_LIGNE_VERS_SORTIE_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_SORTIE_CUISINE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_SORTIE_CUISINE:{
      if (suivreLigne(VITESSE_MAX))
        g_rangee_actuelle++;
      
      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE)
      {
        SerialPrint.println("TOURNER_VERS_COLONNE_PRINCIPALE_CUISINE");
        g_etat = TOURNER_VERS_COLONNE_PRINCIPALE_CUISINE;
        commencerTourner(g_cote_cuisine, 90);
      }
      break;
    }

    case TOURNER_VERS_COLONNE_PRINCIPALE_CUISINE:{
      if (finiTourner())
      {
        g_colonne_cible = 3;
        SerialPrint.println("SUIVRE_LIGNE_VERS_COLONNE_CENTRE_DEPUIS_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_COLONNE_CENTRE_DEPUIS_CUISINE;
        arret();
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_COLONNE_CENTRE_DEPUIS_CUISINE: {
      if (suivreLigne(VITESSE_MAX)) {
        g_colonne_actuelle += (g_cote_cuisine == LEFT) ? -1 : 1;
        SerialPrint.println(g_colonne_actuelle);
      }

      if (g_colonne_actuelle == g_colonne_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(!g_cote_cuisine, 90);
        SerialPrint.println("TOURNER_VERS_TABLES_CLIENT");
        g_etat = TOURNER_VERS_TABLES_CLIENT;
      }
      break;
    }

    case TOURNER_VERS_TABLES_CLIENT: {
      if (finiTourner()) {
        SerialPrint.println("INITIER_DEPART_LIVRAISON");
        g_etat = INITIER_DEPART_LIVRAISON;
      }
      break;
    }
  }
}

void livraison()
{
  switch (g_etat) {
    case INITIER_DEPART_LIVRAISON: {
      g_rangee_cible = round(g_commande->NumTable/2.0);
      g_cote_client = g_commande->NumTable%2;

      SerialPrint.println("SUIVRE_LIGNE_VERS_RANGEE");
      g_etat = SUIVRE_LIGNE_VERS_RANGEE;
      break;
    }

    case SUIVRE_LIGNE_VERS_RANGEE: {
      if (suivreLigne(VITESSE_MAX))
        g_rangee_actuelle++;

      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(g_cote_client, 90);
        SerialPrint.println("TOURNER_VERS_TABLE_CLIENT");
        g_etat = TOURNER_VERS_TABLE_CLIENT;
      }
      break;
    }

    case TOURNER_VERS_TABLE_CLIENT: {
      if (finiTourner()) {
        g_colonne_cible = (g_cote_client == LEFT) ? 2 : 4;
        SerialPrint.println("SUIVRE_LIGNE_VERS_TABLE");
        g_etat = SUIVRE_LIGNE_VERS_TABLE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_TABLE: {
      if (suivreLigne(VITESSE_MAX))
        g_colonne_actuelle += (g_cote_client == LEFT) ? -1 : 1;

      if (g_colonne_actuelle == g_colonne_cible) {
        arret();
        SerialPrint.println("PRET_LEVER_PLATEAU");
        g_etat = PRET_LEVER_PLATEAU;
      }
      break;
    }

    case SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT: {
      if (suivreLigne(VITESSE_MAX))
        g_colonne_actuelle += (g_cote_client == LEFT) ? -1 : 1;

      if (g_colonne_actuelle == g_colonne_cible) {
        arret();
        SerialPrint.println("PRET_DEPOSER_PLATEAU");
        g_etat = PRET_DEPOSER_PLATEAU;
      }
      break;
    }
  }
}

void retourBase() {
  switch (g_etat) {
    case INITIER_RETOUR_BASE: {
      SerialPrint.println("INITIER_RETOUR_BASE");
      g_debut_deplacement_hardcode = millis();
      SerialPrint.println("RECULER_VERS_LIGNE_CENTRALE");
      g_etat = RECULER_VERS_LIGNE_CENTRALE;
      break;
    }

    case RECULER_VERS_LIGNE_CENTRALE: {
      avancer(-0.1, -0.1);

      if (temps_ecoule(g_debut_deplacement_hardcode) > 1500) {
        SerialPrint.println("TOURNER_VERS_LIGNE_CENTRALE");
        commencerTourner(RIGHT, 180);
        g_colonne_actuelle = (g_cote_client == LEFT) ? 2 : 4;
        g_etat = TOURNER_VERS_LIGNE_CENTRALE;
      }
      break;
    }

    case TOURNER_VERS_LIGNE_CENTRALE: {
      if (finiTourner()) {
        g_colonne_cible = 3;
        SerialPrint.println("SUIVRE_LIGNE_VERS_LIGNE_CENTRALE");
        g_etat = SUIVRE_LIGNE_VERS_LIGNE_CENTRALE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE: {
      if (suivreLigne(VITESSE_MAX))
        g_colonne_actuelle += (g_cote_client == LEFT) ? 1 : -1;

      if (g_colonne_actuelle == g_colonne_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        commencerTourner(!g_cote_client, 90);
        SerialPrint.println("TOURNER_VERS_CUISINE");
        g_etat = TOURNER_VERS_CUISINE;
      }
      break;
    }

    case TOURNER_VERS_CUISINE: {
      if (finiTourner()) {
        g_rangee_cible = 0;
        SerialPrint.println("SUIVRE_LIGNE_VERS_CUISINE");
        g_etat = SUIVRE_LIGNE_VERS_CUISINE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_CUISINE: {
      if (suivreLigne(VITESSE_MAX))
        g_rangee_actuelle--;

      if (g_rangee_actuelle == g_rangee_cible && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE) {
        SerialPrint.println("ATTENDRE_PROCHAINE_COMMANDE");
        g_etat = ATTENDRE_PROCHAINE_COMMANDE;
      }
      break;
    }
  }
}

#endif // COMMANDE_H
