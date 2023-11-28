#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>

// Pour faire tourner le robot
const uint16_t PULSES_TOURNER_90_DEG = 1940;
const float VITESSE_TOURNER = 0.2;

void avancer(float vitesseG, float vitesseD);
void commencerTourner(uint8_t sens, uint16_t angle);
bool finiTourner();
void arret();
uint32_t temps_ecoule(uint32_t debut);
void debug_beep(int count, int ms);

// Fait avancer le robot
void avancer(float vitesseG, float vitesseD)
{
  MOTOR_SetSpeed(LEFT, vitesseG);
  MOTOR_SetSpeed(RIGHT, vitesseD);
}

void commencerTourner(uint8_t sens, uint16_t angle)
{
  ENCODER_Reset(LEFT);
  ENCODER_Reset(RIGHT);

  g_pulses_pour_tourner = PULSES_TOURNER_90_DEG * (angle/90.0);
  (sens == RIGHT) ? avancer(VITESSE_TOURNER, -VITESSE_TOURNER) : avancer(-VITESSE_TOURNER, VITESSE_TOURNER);
}

// Retourne false si on a fini de tourner
bool finiTourner()
{
  return ENCODER_Read(LEFT) >= g_pulses_pour_tourner || ENCODER_Read(RIGHT) >= g_pulses_pour_tourner;
}

void arret() {
  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);
}

// Retourne le temps ecoule depsuis le temps specifie en param
uint32_t temps_ecoule(uint32_t debut) {
  return millis() - debut;
}

// Fait beeper le robot, seulement utiliser pour debugger
void debug_beep(int count, int ms){
  for(int i = 0; i < count; i++) {
    AX_BuzzerON();
    delay(ms);
    AX_BuzzerOFF();
    delay(ms);
  }
}

#endif // GENERAL_H
