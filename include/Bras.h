#include <LibRobus.h>
#include <stdint.h>

void plateau(){
  SERVO_Enable(1);
  int position;
  SERVO_SetAngle(1, 180);
  if( (MOTOR_SetSpeed(0, 0) || MOTOR_SetSpeed(1, 0)) ){
      for (position = 100; position <= 50; position -= 1){
        SERVO_SetAngle(1, position);
        delay(1);
      }
      delay(200);
    }
    else () {
        for (position = 50; position <= 100; position += 1){
            SERVO_SetAngle(1, position);
            delay(1);
        }
        delay(200);
    }
}
#endif // plateau
