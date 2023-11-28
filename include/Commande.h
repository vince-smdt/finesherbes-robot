#ifndef COMMANDE_H
#define COMMANDE_H

#include <LibRobus.h>
#include "SuiveurLigne.h"

uint8_t table = 0;
uint32_t tempsLigne = 0;

void setTable();
void pickCommande();
void livraison();
void retourBase();

void setTable()
{
  table = 1;
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
      rangeeCible = round(table/2.0);
      cote = table%2;

      Serial.println("SUIVRE_LIGNE_VERS_RANGEE");
      g_etat = SUIVRE_LIGNE_VERS_RANGEE;
      break;
    }

    case SUIVRE_LIGNE_VERS_RANGEE: {
      suivreLigne();
      if (rangeeActuelle == rangeeCible) {
        Serial.print("Actuel: ");
        Serial.print(rangeeActuelle);
        Serial.print("\t");
        Serial.print("Cible: ");
        Serial.println(rangeeCible);
        Serial.println("TOURNER_VERS_TABLE_CLIENT");
        g_etat = TOURNER_VERS_TABLE_CLIENT;
      }
      break;
    }

    case TOURNER_VERS_TABLE_CLIENT: {
      // Serial.println("Tourner 90 dans livraison");

      if (!tourner(cote, 90)) {
        arriveTable = true; // On n'ajoute pas au compte de rangée lorsqu'on rencontre un bout de tape car on est déjà sur la bonne rangée
        Serial.println("SUIVRE_LIGNE_VERS_TABLE");
        g_etat = SUIVRE_LIGNE_VERS_TABLE;
      }
      break;
    }

    case SUIVRE_LIGNE_VERS_TABLE: {
      suivreLigne();
      if (!arriveTable) {
        Serial.println("LOOP - INITIER_COMMANDE");
        g_etat = INITIER_COMMANDE;
      }
    }
  }

}

#endif // COMMANDE_H
