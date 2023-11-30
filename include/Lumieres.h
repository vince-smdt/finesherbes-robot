#ifndef LUMIERES_H
#define LUMIERES_H

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
void ResetRedGreenYellow();

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
  
  ResetRedGreenYellow();

  switch (g_etat)
  {
    case INITIER_DEPART_LIVRAISON:
    case SUIVRE_LIGNE_VERS_RANGEE:
    case TOURNER_VERS_TABLE_CLIENT:
    case SUIVRE_LIGNE_VERS_TABLE:
    case PRET_LEVER_PLATEAU:
    case LEVER_PLATEAU:
    case FINI_LEVER_PLATEAU:
    case TOURNER_VERS_COTE_TABLE_CUISINE:
    case SUIVRE_LIGNE_VERS_COLONNE_CUISINE:
    case TOURNER_VERS_TABLE_CUISINE:
    case SUIVRE_LIGNE_VERS_TABLE_CUISINE:
    case RECULER_DANS_CUISINE:
    case TOURNER_VERS_SORTIE_CUISINE:
    case SUIVRE_LIGNE_VERS_SORTIE_CUISINE:
    case TOURNER_VERS_COLONNE_PRINCIPALE_CUISINE:
    case SUIVRE_LIGNE_VERS_COLONNE_CENTRE_DEPUIS_CUISINE:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE:
    case TOURNER_VERS_TABLES_CLIENT: {
      StartYellow(current_Millis);
      break;
    }
  
    case PRET_DEPOSER_PLATEAU:
    case DEPOSER_PLATEAU:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT: {
      StartRed();
      break;
    }

    case FINI_DEPOSER_PLATEAU:
    case DEPART:
    case ATTENDRE_PROCHAINE_COMMANDE:
    case INITIER_RETOUR_BASE:
    case RECULER_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_LIGNE_CENTRALE:
    case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_CUISINE:
    case SUIVRE_LIGNE_VERS_CUISINE: {
      StartGreen();
      break;
    }
  }
}

void ResetRedGreenYellow(){
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
  for (int i = 40; i <= 45; i++)
  {
    digitalWrite(i, LOW);
  }
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

#endif // LUMIERES_H
