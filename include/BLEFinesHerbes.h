#ifndef BLE_H
#define BLE_H

#include <Arduino.h>
#include <Queue.h>
#include "Types.h"
#include "Globales.h"
#include <SoftwareSerial.h>

const byte numChars = 4;
int receivedChars[numChars];

Queue<Commande> liste_Commandes;

bool newData = false;

void recvData();
void printNewData();

void BLESetup() {
  Serial2.begin(9600);
}

void HandleData(){
  recvData();
  printNewData();
}

void recvData(){
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial2.available() > 0 && newData == false){
    rc = Serial2.read();
    if (rc != endMarker){
      receivedChars[ndx] = rc - 48;
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
    if(receivedChars[0] >= 1 && receivedChars[0] <= 6 && receivedChars[1] >= 1 && receivedChars[1] <= 6){
      Commande* nouvelle_Commande = new Commande();

      nouvelle_Commande->NumTable = receivedChars[0];
      nouvelle_Commande->NumPlat = receivedChars[1];
      liste_Commandes.push(nouvelle_Commande);
    }
    newData = false;
  }
}

#endif // BLE_H
