#include <QTRSensors.h>
#include <LibRobus.h>
#include "bras.h"
#include "General.h"
#include "SuiveurLigne.h"
#include "BLEFinesHerbes.h"

void setup()
{
  BoardInit();
  Serial.begin(115200);
  calibrationSuiveurLigne();
  BLESetup();
}


void loop()
{
  suivreLigne();
}


