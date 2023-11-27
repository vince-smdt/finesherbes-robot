#include <QTRSensors.h>
#include <LibRobus.h>
#include "bras.h"
#include "General.h"
#include "SuiveurLigne.h"
#include "DetectMicroSonore.h"

void setup()
{
   
  BoardInit();
  Serial.begin(9600);
  calibrationSuiveurLigne();
  
}


void loop()
{
 test_plateau();
}


