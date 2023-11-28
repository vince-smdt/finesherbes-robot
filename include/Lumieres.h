#ifndef LUMIERES_H__
#define LUMIERES_H__

#include "General.h"
#include "Arduino.h"

const int INTERVAL = 100;
const int GREEN_PIN = 38;
const int RED_PIN = 39;

unsigned long previous_Millis = 0;
int currentYellow = 45;


void StartYellow(unsigned long current_Millis);
void StartGreen();
void StartRed();
void ResetRedGreen();

void LumieresSetup(){
    pinMode(43, OUTPUT);
    pinMode(44, OUTPUT);

    for (int i = 40; i <= 45; i++)
    {
        pinMode(i, OUTPUT);
    }
}

void LumieresLoop(){
  unsigned long current_Millis = millis();
  
  ResetRedGreen();

  switch (g_etat)
  {
  case INITIER_COMMANDE:
  case SUIVRE_LIGNE_VERS_RANGEE:
  case TOURNER_VERS_TABLE_CLIENT:
  case SUIVRE_LIGNE_VERS_TABLE:
  case PRET_LEVER_PLATEAU:
  case LEVER_PLATEAU:
      StartYellow(current_Millis);
    break;
  
  case PRET_DEPOSER_PLATEAU:
  case DEPOSER_PLATEAU:
    StartRed();
    break;

  case FINI_DEPOSER_PLATEAU:
    StartGreen();
    break;
  default:
    break;
  }
}

void ResetRedGreen(){
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
}

void StartYellow(unsigned long current_Millis){
  if(current_Millis - previous_Millis >= INTERVAL){
    previous_Millis = current_Millis;
    currentYellow-=1;
    if(currentYellow == 39){
      currentYellow=45;
    }
  }
  
  if(currentYellow==45){
    digitalWrite(40,LOW);
  }else{
    digitalWrite(currentYellow+1, LOW);
  }

  digitalWrite(currentYellow, HIGH);
}

void StartRed(){
  digitalWrite(RED_PIN, HIGH);
}

void StartGreen(){
  digitalWrite(GREEN_PIN, HIGH);
}

#endif