#ifndef BLE_H
#define BLE_H

#include <LibRobus.h>
#include "Globales.h"
#include "Types.h"
#include "Globales.h"

const byte numChars = 4;
int receivedChars[numChars];
bool newData = false;

void blerecvData();
void saveNewData();

void BLESetup() {
  SerialBluetooth.begin(9600);
}

void HandleData(){
  blerecvData();
  saveNewData();
}

void blerecvData(){
  byte ndx = 0;
  char endMarker = '\n';
  char rc;

  SerialPrint.println(SerialBluetooth.available());
  while (SerialBluetooth.available() > 0 && newData == false){
    rc = SerialBluetooth.read();
    if (rc != endMarker){
      receivedChars[ndx] = rc - 48;
      ndx++;
      if (ndx >= numChars){
        ndx = numChars - 1;
      }
    }
    else{
      receivedChars[ndx] = '\0';
      ndx = 0;
      newData = true;
    }
  }
}

void saveNewData(){
  if (newData == true) {
    if(receivedChars[0] >= 1 && receivedChars[0] <= 6 && receivedChars[1] >= 1 && receivedChars[1] <= 6){
      Commande* nouvelle_Commande = new Commande();

      SerialPrint.print("Received: ");
      SerialPrint.print(receivedChars[0]);
      SerialPrint.print(" ");
      SerialPrint.println(receivedChars[1]);

      nouvelle_Commande->NumTable = receivedChars[0];
      nouvelle_Commande->NumPlat = receivedChars[1];
      g_file_commandes.push(nouvelle_Commande);
    }
    newData = false;
  }
}

#endif // BLE_H
