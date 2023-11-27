#include <QTRSensors.h>
#include <LibRobus.h>

#include "Globales.h"
#include "Enums.h"

#include "Bras.h"
#include "General.h"
#include "SuiveurLigne.h"
#include "DetectMicroSonore.h"
#include "Commande.h"

void setup()
{
  BoardInit();
  Serial.begin(9600);
  calibrationSuiveurLigne();
  // BLESetup();
  setup_plateau();
}

void loop()
{
  Serial.print("VERIF ASYNC"); // Pour s'assurer qu'aucune fonction n'est bloquante

  switch (g_etat) {
    // Etats initiaux
    case DEPART:
      g_etat = PRET_DEPOSER_PLATEAU;
      break;

    // Lever le plateau
    case PRET_DEPOSER_PLATEAU:
    case DEPOSER_PLATEAU:
    case FINI_DEPOSER_PLATEAU:
      deposer_plateau();
      break;

    // Deposer le plateau
    case PRET_LEVER_PLATEAU:
    case LEVER_PLATEAU:
    case FINI_LEVER_PLATEAU:
      lever_plateau();
      break;
  }
}


