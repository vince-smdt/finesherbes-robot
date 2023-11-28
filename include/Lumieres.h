#ifndef LUMIERES_H__
#define LUMIERES_H__

#include "General.h"
#include "Arduino.h"

unsigned long previous_Millis = 0;
const int interval = 100;
int currentYellow = 50;

void LumieresSetup(){
    pinMode(43, OUTPUT);
    pinMode(44, OUTPUT);

    for (int i = 45; i <= 50; i++)
    {
        pinMode(i, OUTPUT);
    }
}

void LumieresLoop(){
  unsigned long current_Millis = millis();
  

  if(current_Millis - previous_Millis >= interval){
    previous_Millis = current_Millis;
    currentYellow-=1;
    if(currentYellow == 44){
      currentYellow=50;
    }
  }
  
  if(currentYellow==50){
    digitalWrite(45,LOW);
  }else{
    digitalWrite(currentYellow+1, LOW);
  }

  digitalWrite(currentYellow, HIGH);
}

#endif