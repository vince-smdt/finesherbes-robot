#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>
#include <stdint.h>
#define GAUCHE              1
#define DROITE              0

const uint8_t IR_DIST_MIN = 10;
const uint8_t IR_DIST_MAX = 80;

// Pour faire tourner le robot
const int PULSES_TOURNER_90_DEG = 1940;
const float VITESSE_TOURNER = 0.2;

// Converti la valeur analogue d'un capteur infrarouge en cm
// Le param "id" represente IR0 a IR3 (0-3)
float IR_to_cm(uint8_t id) {
  return constrain(5500.0/ROBUS_ReadIR(id), IR_DIST_MIN, IR_DIST_MAX);
}

// Fait avancer le robot
void avancer(float vitesseG, float vitesseD) 
{
  MOTOR_SetSpeed(LEFT, vitesseG);
  MOTOR_SetSpeed(RIGHT, vitesseD);
}

void tourner90(int sens)
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  while (ENCODER_Read(0) < PULSES_TOURNER_90_DEG && ENCODER_Read(1) < PULSES_TOURNER_90_DEG)
  {
    (sens == DROITE) ? avancer(VITESSE_TOURNER, -1*VITESSE_TOURNER) : avancer(-1*VITESSE_TOURNER, VITESSE_TOURNER);
    Serial.print(ENCODER_Read(0));
    Serial.print("\t");
    Serial.print(ENCODER_Read(1));
    Serial.print("\n");
  }
  

}


#endif // GENERAL_H