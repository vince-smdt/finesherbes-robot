#ifndef BRAS_H
#define BRAS_H

#include <LibRobus.h>
#include "General.h"
#include "Globales.h"
#include "Enums.h"

const uint8_t SERVO_BRAS_ID = 0;
const uint8_t ANGLE_SERVO_DEPOSER = 120;
const uint8_t ANGLE_SERVO_LEVER = 180;
const uint16_t DELAI_SERVO_BRAS = 1500;
const uint16_t DELAI_DEPOSER_PLATEAU = 5;

void setup_plateau();
void lever_plateau();
void deposer_plateau();

void setup_plateau()
{
  SERVO_Enable(SERVO_BRAS_ID);
  deposer_plateau();
}

void lever_plateau()
{
  switch (g_etat) {
    case PRET_LEVER_PLATEAU:
    { 
      g_duree_mouvement_bras = millis();
      SERVO_SetAngle(SERVO_BRAS_ID, ANGLE_SERVO_LEVER);
      g_etat = LEVER_PLATEAU;
      break;
    }
    case LEVER_PLATEAU:
    {
      if ((millis() - g_duree_mouvement_bras) > DELAI_SERVO_BRAS)
        g_etat = FINI_LEVER_PLATEAU;
      break;
    }
    case FINI_LEVER_PLATEAU:
    {
      g_etat = PRET_DEPOSER_PLATEAU;
      break; 
    }
  }
}

void deposer_plateau()
{
  switch (g_etat) {
    case PRET_DEPOSER_PLATEAU:
    { 
      g_duree_mouvement_bras = millis();
      SERVO_SetAngle(SERVO_BRAS_ID, ANGLE_SERVO_DEPOSER);
      g_etat = DEPOSER_PLATEAU;
      break;
    }
    case DEPOSER_PLATEAU:
    {
      if ((millis() - g_duree_mouvement_bras) > DELAI_SERVO_BRAS)
        g_etat = FINI_DEPOSER_PLATEAU;
      break;
    }
    case FINI_DEPOSER_PLATEAU:
    {
      g_etat = PRET_LEVER_PLATEAU;
      break; 
    }
  }
}

#endif // BRAS_H
