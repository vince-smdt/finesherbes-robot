#ifndef COMMANDE_H
#define COMMANDE_H

#include <LibRobus.h>
#include <stdint.h>
#include "SuiveurLigne.h"

int table;
int rangee;
int cote;

int periode = 250;
unsigned long tempsLigne = 0;

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
    

    if(millis() >= tempsLigne + periode){
        
        Serial.println("Hello");
    }
    
    tempsLigne += periode;
    


    avancer(0, 0);
    delay(500);
    tourner90(cote);
    arriveTable = true;
    
    while (arriveTable)
    {
        suivreLigne();
    }
    
    

    
}

void retourBase()
{
    arriveTable = false;
    tourner90(GAUCHE);
    tourner90(GAUCHE);
    etat = VERS_LA_BASE;
    
}


#endif // COMMANDE_H
