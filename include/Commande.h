#ifndef COMMANDE_H
#define COMMANDE_H

#include <LibRobus.h>
#include <stdint.h>
#include "SuiveurLigne.h"

int getTable() 
{
  return 1;
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
    int table = getTable();
    int rangee = 1;//(int)((table/2)+0.5);
    int cote = table%2;
    
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
    delay(250);
    avancer(0, 0);
    delay(500);
    tourner90(cote);
    arriveTable = true;
    
    while (arriveTable)
    {
        suivreLigne();
    }
    
    

    
}

void retourBase();

#endif // COMMANDE_H
