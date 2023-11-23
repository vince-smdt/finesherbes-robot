#include <QTRSensors.h>
#include <Arduino.h>
#include <LibRobus.h>
#include <bras.h>
#include "General.h"
#include "SuiveurLigne.h"

// Defines
#define LEFT 0
#define RIGHT 1


void setup()
{
  BoardInit();
  Serial.begin(9600);
  calibrationSuiveurLigne();
}


void loop()
{
  suivreLigne();
}


