#include <QTRSensors.h>
#include <LibRobus.h>

#include "Globales.h"
#include "Enums.h"

#include "Bras.h"
#include "General.h"
#include "SuiveurLigne.h"
#include "DetectMicroSonore.h"
#include "Commande.h"
#include "BLEFinesHerbes.h"
#include "Lumieres.h"
//#include "LCD.h"

void setup()
{
  BoardInit();
  SerialPrint.begin(9600);
  calibrationSuiveurLigne();
  BLESetup();
  //LCD_setup();
  LumieresSetup();
}

void loop()
{
  LumieresLoop();
  //LCD_Tout();

  if (temps_ecoule(g_debut_recv_data_ble) > DELAI_RECV_DATA_BLE) {
    g_debut_recv_data_ble = millis();
    HandleData();
  }

  // On execute la fonction voulue en fonction de l'etat actuel
  switch (g_etat) {
    // Etats initiaux
    case DEPART: {
      SerialPrint.println("");
      SerialPrint.println("=========================");
      SerialPrint.println("==        DEPART       ==");
      SerialPrint.println("=========================");
      SerialPrint.println("SUIVRE_LIGNE_VERS_CUISINE");
      SerialPrint.println("");
      g_etat = SUIVRE_LIGNE_VERS_CUISINE;
      break;
    }

    // Deposer le plateau
    case PRET_DEPOSER_PLATEAU:
    case DEPOSER_PLATEAU:
    case FINI_DEPOSER_PLATEAU: {
      deposer_plateau();
      break;
    }

    // Lever le plateau
    case PRET_LEVER_PLATEAU:
    case LEVER_PLATEAU:
    case FINI_LEVER_PLATEAU: {
      lever_plateau();
      break;
    }

    // Chercher le plat
    case ATTENDRE_PROCHAINE_COMMANDE:
    case TOURNER_VERS_COTE_TABLE_CUISINE:
    case SUIVRE_LIGNE_VERS_COLONNE_CUISINE:
    case TOURNER_VERS_TABLE_CUISINE:
    case SUIVRE_LIGNE_VERS_TABLE_CUISINE:
    case RECULER_DANS_CUISINE:
    case TOURNER_VERS_SORTIE_CUISINE:
    case SUIVRE_LIGNE_VERS_SORTIE_CUISINE:
    case TOURNER_VERS_COLONNE_PRINCIPALE_CUISINE:
    case SUIVRE_LIGNE_VERS_COLONNE_CENTRE_DEPUIS_CUISINE:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE:
    case TOURNER_VERS_TABLES_CLIENT: {
      chercher_commande();
      break;
    }

    // Porter nourriture
    case INITIER_DEPART_LIVRAISON:
    case SUIVRE_LIGNE_VERS_RANGEE:
    case TOURNER_VERS_TABLE_CLIENT:
    case SUIVRE_LIGNE_VERS_TABLE:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT: {
      livraison();
      break;
    }

    // Retour au point de base
    case INITIER_RETOUR_BASE:
    case RECULER_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_LIGNE_CENTRALE:
    case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_CUISINE:
    case SUIVRE_LIGNE_VERS_CUISINE:{
      retourBase();
      break;
    }
  }
}
