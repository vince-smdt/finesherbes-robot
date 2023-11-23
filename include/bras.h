#ifndef BRAS_H
#define BRAS_H
#include  <LibRobus.h>
#include <stdint.h>
#include <general.h>

void deposer_plateau();
void lever_plateau();

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

#endif BRAS_H