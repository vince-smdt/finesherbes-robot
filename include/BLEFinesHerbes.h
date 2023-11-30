#ifndef BLE_H
#define BLE_H

#include <Arduino.h>
#include "Globales.h"
#include "Types.h"

const byte numChars = 32;
char receivedChars[numChars];

bool newData = false;

void BLESetup() {
  Serial.println("<Arduino ready>");
}

void HandleData(){
  // recvData();
  // printNewData();
}

void recvData(){
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false){
    rc = Serial.read();

    if (rc != endMarker){
      receivedChars[ndx] = rc+48;
      ndx++;
      if(ndx >= numChars){
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

void printNewData(){
  if (newData == true) {
    Serial.print("Received: ");
    if(sizeof(receivedChars)/sizeof(receivedChars[0]) == 3){
      Commande* nouvelle_commande = new Commande();

      nouvelle_commande->NumTable = receivedChars[0];
      nouvelle_commande->NumPlat = receivedChars[1];
      g_file_commandes.push(nouvelle_commande);
    }
    newData = false;
  }
}

#endif // BLE_H
