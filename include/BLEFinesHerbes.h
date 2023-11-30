#ifndef BLE_H
#define BLE_H

#include <LibRobus.h>
#include "Globales.h"
#include "Types.h"
#include <SoftwareSerial.h>

const byte numChars = 4;
int receivedChars[numChars];

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
    Serial.print("Received: ");
    if(sizeof(receivedChars)/sizeof(receivedChars[0]) == 3){
      Commande* nouvelle_commande = new Commande();
      Serial.print(receivedChars[0]);
      Serial.print(" ");
      Serial.println(receivedChars[1]);
      nouvelle_commande->NumTable = receivedChars[0];
      nouvelle_commande->NumPlat = receivedChars[1];
      g_file_commandes.push(nouvelle_commande);
    }
    newData = false;
  }
}

#endif // BLE_H
