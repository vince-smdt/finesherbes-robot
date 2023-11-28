#ifndef BLE_H
#define BLE_H

#include <Arduino.h>
#include <Queue.h>

const byte numChars = 32;
char receivedChars[numChars];

Queue<Commande> liste_Commandes;

struct Commande
{
  int NumTable;
  int NumPlat;
};


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
      Commande nouvelle_Commande;
      nouvelle_Commande.NumTable = receivedChars[1];
      nouvelle_Commande.NumPlat = receivedChars[2];
      liste_Commandes.push(nouvelle_Commande);
    }
    newData = false;
  }
}

#endif // BLE_H
