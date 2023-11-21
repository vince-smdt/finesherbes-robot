#include <Arduino.h>
//#include "QTRSensors.h"
//#include "Commande.h"
#include <LibRobus.h>

#define NOIR 1
#define BLANC 0

const int NB_CAPTEUR = 2;
int etatCapteur[NB_CAPTEUR];


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);
}

void loop() {
  while (true)
  {
    Serial.print("DDWD\n"/*analogRead((A4)) + " " + analogRead((A5))*/);
  }
}

