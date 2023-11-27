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
  switch (getTable())
  {
  case 1:
    while (numRangee != 1)
    {
        suivreLigne();
    }
    avancer(0, 0);
    
    break;
  
  default:
    break;
  }
}

#endif // COMMANDE_H
