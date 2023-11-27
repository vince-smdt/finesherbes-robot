#ifndef BRAS_H
#define BRAS_H

#include <LibRobus.h>
#include <general.h>

const uint8_t SERVO_BRAS_ID = 0;
const uint8_t ANGLE_SERVO_DEPOSER = 130;
const uint8_t ANGLE_SERVO_LEVER = 180;
const uint16_t DELAI_SERVO_BRAS = 1500;
const uint16_t DELAI_DEPOSER_PLATEAU = 5;

uint8_t g_angle_servo_bras = 0;

void setup_plateau();
void test_plateau();
void lever_plateau();
void deposer_plateau();

void setup_plateau()
{
  SERVO_Enable(SERVO_BRAS_ID);
  deposer_plateau();
}

void test_plateau()
{
  lever_plateau();
  lever_plateau();
  deposer_plateau();
  deposer_plateau();

  // lever_plateau();
  // avancer (-0.2f, -0.2f);
  // delay(1500);
  // avancer (0, 0);
  // delay (1500);
  // avancer (0.2f, 0.2f);
  // delay (1500);
  // avancer (0,0);
  // delay(1500);
  // deposer_plateau();
  // delay(1500);
  // avancer (-0.2f, -0.2f);
  // delay (2000);
  // avancer(0,0);
}

void lever_plateau()
{
  // On quitte la fonction si le bras est déjà levé
  if (g_angle_servo_bras >= ANGLE_SERVO_LEVER) {
    Serial.println("Le plateau est deja leve!");
    return;
  }

  SERVO_SetAngle(SERVO_BRAS_ID, ANGLE_SERVO_LEVER);
  delay(DELAI_SERVO_BRAS);
  g_angle_servo_bras = ANGLE_SERVO_LEVER;
}

void deposer_plateau()
{
  // On quitte la fonction si le bras est déjà baissé
  if (g_angle_servo_bras <= ANGLE_SERVO_DEPOSER) {
    Serial.println("Le plateau est deja depose!");
    return;
  }

  for (uint8_t angle = g_angle_servo_bras; angle > ANGLE_SERVO_DEPOSER; angle--) {
    SERVO_SetAngle(SERVO_BRAS_ID, angle);
    delay(DELAI_DEPOSER_PLATEAU);
  }
  delay(DELAI_SERVO_BRAS / 2);
  g_angle_servo_bras = ANGLE_SERVO_DEPOSER;
}

#endif // BRAS_H
