#ifndef SUIVEURLIGNE_H
#define SUIVEURLIGNE_H

#include <QTRSensors.h>
#include "General.h"
#include "DetectMicroSonore.h"

#define NB_CAPTEURS         8
#define NB_LECTURES         4  //Calcul la moyenne de 4 lectures d'un capteur pour normaliser la valeur
#define EMITTER_PIN         QTR_NO_EMITTER_PIN  //Pas d'emetteur

#define VERS_LA_BASE        0
#define VERS_LES_TABLES     1

#define GAUCHE              1
#define DROITE              0

int numRangee = 0;
int etat = VERS_LES_TABLES;
bool arriveTable = false;

//initialise tous les capteurs dans le arduino
QTRSensorsAnalog qtra((unsigned char[]) {A7, A6, A5, A4, A3, A2, A1, A0}, NB_CAPTEURS, NB_LECTURES, EMITTER_PIN);
unsigned int valeursCapteur[NB_CAPTEURS];


//Constante et propriété du PID
const int OBJECTIF = 3500;
#define VITESSE_MAX  0.3

const float kP = 0.0001;
const float kD = 0.001;
float derniereErreur = 0;

void calibrationSuiveurLigne()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    //active la lumière du arduino
  for (int i = 0; i < 150; i++)  //calibration des capteurs
  {
    qtra.calibrate(); 
  }
  digitalWrite(13, LOW);     //éteint la lumière, la calibration est finie

  // print the calibration minimum values measured when emitters were on
  for (int i = 0; i < NB_CAPTEURS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NB_CAPTEURS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
}

void suivreLigne()
{
  //calcul la position de la ligne (entre 0 et 7000) selon les lectures des capteurs
  unsigned int position = qtra.readLine(valeursCapteur);
  //Serial.print("Position : ");
  //Serial.print(position);
  
  //lorsqu'au moins 6 capteurs détectent une ligne, cela veut dire qu'il a atteint une ligne perpendiculaire
    if (qtra.numSensorsHigh(valeursCapteur) > 6)
    {
        if (arriveTable == false)
        {
            switch (etat)
            {
            case VERS_LA_BASE:
                numRangee--;
                break;

            case VERS_LES_TABLES:
                numRangee++;
                break;

            default:
                break;
            }
        }
        
        
        else
        {
            avancer(0, 0);
            delay(1000);
            //met le cabaret sur la table
            retourBase();
        }

    }
  
  

  //calcul la différence entre le milieu des capteurs et la ligne
  int erreur = OBJECTIF - position;
  //Serial.print("\tErreur : ");
  //Serial.print(erreur);

  //calcul un coefficient à mettre devant la vitesse de moteurs pour ajuster la trajectoire
  float ajustement = (kP * erreur) + (kD * (erreur - derniereErreur));
  //Serial.print("\tAjustement : ");
  //Serial.print(ajustement);
  //Serial.print("\t");
  
  //garde en mémoire la dernière erreur 
  derniereErreur = erreur;

  float vitesseG = constrain(VITESSE_MAX + ajustement, 0 , VITESSE_MAX);
  float vitesseD = constrain(VITESSE_MAX - ajustement, 0 , VITESSE_MAX);
  avancer(vitesseG, vitesseD);
  //Serial.print("Vitesse Gauche : ");
  //Serial.print(vitesseG);
  //Serial.print("\tVitesse Droite : ");
  //Serial.print(vitesseD);
  //Serial.print("\n");
  
  //Tant qu'il y a un objet à moins de 15cm du sonor, il ne bouge plus
  /*while (distanceMur < 15)
  {
    avancer(0, 0);
  }
*/

 
  for (unsigned char i = 0; i < NB_CAPTEURS; i++)
  {
    Serial.print(valeursCapteur[i]);
    Serial.print('\t');
  }
  Serial.println(position); // comment this line out if you are using raw values

  //delay(500);
}


#endif // SUIVEURLIGNE_H