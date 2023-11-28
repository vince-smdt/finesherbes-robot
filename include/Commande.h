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
  setTable();
  rangee = round(table/2);
  cote = table%2;

  Serial.print("rangee : ");
  Serial.print(rangee);
  Serial.print("\t");
  Serial.print("coté : ");
  Serial.print(cote);
  Serial.print("\n");

  while (numRangee != rangee)
  {
    suivreLigne();
  }

  avancer(0, 0);
  delay(500);
  tourner(cote, 90);
  arriveTable = true;

  while (arriveTable)
  {
    suivreLigne();
  }
}

#endif // COMMANDE_H
