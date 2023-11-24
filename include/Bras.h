#ifndef BRAS_H
#define BRAS_H

#include <LibRobus.h>
#include <general.h>

void lever_plateau();
void deposer_plateau();

void test_plateau()
{
  lever_plateau();
  avancer (-0.2f, -0.2f);
  delay(1500);
  avancer (0, 0);
  delay (1500);
  avancer (0.2f, 0.2f);
  delay (1500);
  avancer (0,0);
  delay(1500);
  deposer_plateau();
  delay(1500);
  avancer (-0.2f, -0.2f);
  delay (2000);
  avancer(0,0);
}

void lever_plateau()
{
  SERVO_Enable(0);
  SERVO_SetAngle (0,120);
  delay (1500);
  SERVO_SetAngle (0,180);
  delay (1500);
}

void deposer_plateau()
{
  SERVO_Enable(0);
  SERVO_SetAngle (0,120);
  delay (1500);
}

#endif // BRAS_H
