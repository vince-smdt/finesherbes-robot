#include <QTRSensors.h>
#include <LibRobus.h>

#include "Globales.h"
#include "Enums.h"

#include "Bras.h"
#include "General.h"
#include "SuiveurLigne.h"
#include "DetectMicroSonore.h"
#include "Commande.h"
#include "Lumieres.h"

void setup()
{
  BoardInit();
  Serial.begin(9600);
  calibrationSuiveurLigne();
  // BLESetup();
  // setup_plateau();
  // MicroSonoreSetup();
  LumieresSetup();
}

void loop()
{
  LumieresLoop();
  // livraison();

  // if(MicroSonoreRobot() <= 3){
  //   avancer(0,0);
  // }
  // else{
  //   avancer(0.1, 0.1);
  // }

  // Serial.println("VERIF NON-BLOQUANT"); // Pour s'assurer qu'aucune fonction n'est bloquante

  // On execute la fonction voulue en fonction de l'etat actuel
  switch (g_etat) {
    // Etats initiaux
    case DEPART: {
      g_etat = INITIER_DEPART_COMMANDE;
      break;
    }

    // Lever le plateau
    case PRET_DEPOSER_PLATEAU:
    case DEPOSER_PLATEAU:
    case FINI_DEPOSER_PLATEAU: {
      deposer_plateau();
      break;
    }

    // Deposer le plateau
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
    case SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE: {
      chercher_commande();
      break;
    }

    // Porter nourriture
    case INITIER_DEPART_COMMANDE:
    case SUIVRE_LIGNE_VERS_RANGEE:
    case TOURNER_VERS_TABLE_CLIENT:
    case SUIVRE_LIGNE_VERS_TABLE:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT: {
      livraison();
      break;
    }

    // Retour au point de base
    case TOURNER_VERS_LIGNE_CENTRALE:
    case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_CUISINE:
    case SUIVRE_LIGNE_VERS_CUISINE:{
      retourBase();
      break;
    }
  }
}
