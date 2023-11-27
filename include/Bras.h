#ifndef BRAS_H
#define BRAS_H
#include  <LibRobus.h>
#include <stdint.h>
#include <general.h>

void lever_plateau();
void deposer_plateau();

void test_plateau ()
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

void test_plateau1()
{
    SERVO_Enable(0);
    SERVO_SetAngle (0,120);
    delay (1500);
    SERVO_SetAngle (0,180);
    delay (1500);
    SERVO_SetAngle (0,120);
    delay (1500);
    // SERVO_SetAngle(0, 180);
    // Serial.print ("180");
    // delay (3000);
    // SERVO_SetAngle(0, 175);
    // Serial.print ("175");
    // delay (3000);
    // SERVO_SetAngle(0, 170);
    // Serial.print ("170");
    // delay (3000);
    // SERVO_SetAngle(0, 165);
    // Serial.print ("165");
    // delay (3000);
    // SERVO_SetAngle(0, 160);
    // Serial.print ("160");
    // delay (3000);
    // SERVO_SetAngle(0, 155);
    // Serial.print ("155");
    // SERVO_SetAngle(0, 150);
    // Serial.print ("150");
    // delay (3000);
    // SERVO_SetAngle(0, 145);
    // Serial.print ("145");
    // delay (3000);
    // SERVO_SetAngle(0, 140);
    // Serial.print ("140");
    // delay (3000);
    // SERVO_SetAngle(0, 135);
    // Serial.print ("135");
    // delay (3000);
    // SERVO_SetAngle(0, 130);
    // Serial.print ("130");
    // delay (3000);
    // SERVO_SetAngle(0, 125);
    // Serial.print ("125");
    // delay (3000);
    // SERVO_SetAngle(0, 120);
    // Serial.print ("120");
    // delay (3000);
    // SERVO_SetAngle(0, 115);
    // Serial.print ("115");
    // delay (3000);
    // SERVO_SetAngle(0, 110);
    // Serial.print ("110");
    // delay (3000);
    // SERVO_SetAngle(0, 105);
    // Serial.print ("105");
    // delay (3000);
    // SERVO_SetAngle(0, 100);
    // Serial.print ("100");
    // delay (3000);
    // SERVO_SetAngle(0, 95);
    // Serial.print ("95");
    // delay (3000);
    // SERVO_SetAngle(0, 90);
    // Serial.print ("90");
    // delay (3000);
    // SERVO_SetAngle(0, 85);
    // Serial.print ("85");
    // delay (3000);
    // SERVO_SetAngle(0, 80);
    // Serial.print ("80");
    // delay (3000);
}

// void plateau(){
//   SERVO_Enable(1);
//   int position;
//   SERVO_SetAngle(1, 50);
//   if( (MOTOR_SetSpeed(0, 0) || MOTOR_SetSpeed(1, 0)) ){
//       for (position = 100; position <= 50; position -= 1){
//         SERVO_SetAngle(1, position);
//         delay(1);
//       }
//       delay(200);
//     }
//     else () {
//         for (position = 50; position <= 100; position += 1){
//             SERVO_SetAngle(1, position);
//             delay(1);
//         }
//         delay(200);
//     }
// }

// plateau

// #include "General.h"
// // Detecter la balle et fait tomber le verre sur la balle
// void pousserleverre(){
//   Serial.print ("debut pousser le verre");
//   SERVO_Enable (2);
//   SERVO_SetAngle(1, 0);
// }

// #endif // BALLE_H

#endif //BRAS_H