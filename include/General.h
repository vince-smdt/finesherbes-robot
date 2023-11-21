#ifndef GENERAL_H
#define GENERAL_H

#include <LibRobus.h>
#include <stdint.h>

const uint8_t IR_DIST_MIN = 10;
const uint8_t IR_DIST_MAX = 80;

// Converti la valeur analogue d'un capteur infrarouge en cm
// Le param "id" represente IR0 a IR3 (0-3)
float IR_to_cm(uint8_t id) {
  return constrain(5500.0/ROBUS_ReadIR(id), IR_DIST_MIN, IR_DIST_MAX);
}



#endif // GENERAL_H