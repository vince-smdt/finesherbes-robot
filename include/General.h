#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>

// Pour faire tourner le robot
const uint16_t PULSES_TOURNER_90_DEG = 1940;
const float VITESSE_TOURNER = 0.2;

void avancer(float vitesseG, float vitesseD);
void tourner(uint8_t sens, uint16_t angle);
uint32_t temps_ecoule(uint32_t debut);

// Fait avancer le robot
void avancer(float vitesseG, float vitesseD)
{
  MOTOR_SetSpeed(LEFT, vitesseG);
  MOTOR_SetSpeed(RIGHT, vitesseD);
}

void tourner(uint8_t sens, uint16_t angle)
{
  const int32_t PULSES_A_TOURNER = PULSES_TOURNER_90_DEG * (angle/90.0);

  ENCODER_Reset(LEFT);
  ENCODER_Reset(RIGHT);

  while (ENCODER_Read(LEFT) < PULSES_A_TOURNER && ENCODER_Read(RIGHT) < PULSES_A_TOURNER)
  {
    (sens == RIGHT) ? avancer(VITESSE_TOURNER, -VITESSE_TOURNER) : avancer(-VITESSE_TOURNER, VITESSE_TOURNER);
    Serial.print(ENCODER_Read(LEFT));
    Serial.print("\t");
    Serial.print(ENCODER_Read(RIGHT));
    Serial.print("\n");
  }
}

// Retourne le temps ecoule depsuis le temps specifie en param
uint32_t temps_ecoule(uint32_t debut) {
  return millis() - debut;
}

#endif // GENERAL_H
