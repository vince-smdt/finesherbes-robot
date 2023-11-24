#include <QTRSensors.h>
#include <LibRobus.h>
#include "bras.h"
#include "General.h"
#include "SuiveurLigne.h"
#include "DetectMicroSonore.h"

void setup()
{
   
  BoardInit();
  Serial.begin(9600);
  calibrationSuiveurLigne();
  
}


void loop()
{
  //calcul la position de la ligne (entre 0 et 7000) selon les lectures des capteurs
  unsigned int position = qtra.readLine(valeursCapteur);
  Serial.print("Position : ");
  Serial.print(position);
  
  //calcul la différence entre le milieu des capteurs et la ligne
  int erreur = OBJECTIF - position;
  Serial.print("\tErreur : ");
  Serial.print(erreur);

  //calcul un coefficient à mettre devant la vitesse de moteurs pour ajuster la trajectoire
  float ajustement = (kP * erreur) + (kD * (erreur - derniereErreur));
  Serial.print("\tAjustement : ");
  Serial.print(ajustement);
  Serial.print("\n");
  
  //garde en mémoire la dernière erreur 
  derniereErreur = erreur;

  float vitesseG = constrain(VITESSE_MAX + ajustement, 0 , VITESSE_MAX);
  float vitesseD = constrain(VITESSE_MAX - ajustement, 0 , VITESSE_MAX);

  Serial.print("Vitesse Gauche : ");
  Serial.print(vitesseG);
  Serial.print("\tVitesse Droite : ");
  Serial.print(vitesseD);
  Serial.print("\n");

  avancer(vitesseG, vitesseD);
}


