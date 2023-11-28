#ifndef SUIVEURLIGNE_H
#define SUIVEURLIGNE_H

#include <QTRSensors.h>
#include "General.h"
#include "DetectMicroSonore.h"

uint8_t rangeeCible;
uint8_t cote;

const uint8_t NB_CAPTEURS = 8;
const uint8_t NB_LECTURES = 4; //Calcul la moyenne de 4 lectures d'un capteur pour normaliser la valeur
const uint8_t EMITTER_PIN = QTR_NO_EMITTER_PIN; //Pas d'emetteur
const uint8_t LUMIERE_PIN = 13;

#define VERS_LA_BASE        0
#define VERS_LES_TABLES     1

uint8_t rangeeActuelle = 0;
uint8_t positionCible = VERS_LES_TABLES;
bool arriveTable = false;

//initialise tous les capteurs dans le arduino
QTRSensorsAnalog qtra((unsigned char[]) {A7, A6, A5, A4, A3, A2, A1, A0}, NB_CAPTEURS, NB_LECTURES, EMITTER_PIN);
unsigned int valeursCapteur[NB_CAPTEURS];

//Constante et propriété du PID
const uint16_t OBJECTIF = 3500;
const float VITESSE_MAX = 0.3;

const float kP = 0.0001;
const float kD = 0.001;
float derniereErreur = 0;

void calibrationSuiveurLigne();
void retourBase();
void suivreLigne();

void calibrationSuiveurLigne()
{
  pinMode(LUMIERE_PIN, OUTPUT);
  digitalWrite(LUMIERE_PIN, HIGH);    //active la lumière du arduino
  for (int i = 0; i < 150; i++)  //calibration des capteurs
  {
    qtra.calibrate(); 
  }
  digitalWrite(LUMIERE_PIN, LOW);     //éteint la lumière, la calibration est finie

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

void retourBase()
{
  arriveTable = false;
  Serial.println("Tourner 180 dans retourbase");
  tourner(LEFT, 180);
  positionCible = VERS_LA_BASE;
  //Tant qu'il ne coise pas la ligne, il suit la ligne
  while (qtra.numSensorsHigh(valeursCapteur) < 6)
  {
    suivreLigne();
  }
  Serial.print("\n");

  //numRangee--;
  Serial.print(rangeeActuelle);
  avancer(0, 0);
  delay(1000);
  //tourne dans la direction opposé à celle q'il a tourné précédamment pour se rendre à la table
  (cote == RIGHT) ? tourner(LEFT, 90) : tourner(RIGHT, 90);

  //tant qu'il n'est pas au départ il suit la ligne
  while (rangeeActuelle != 0)
  {
    suivreLigne();
  }

  avancer(0,0);
}

void suivreLigne()
{
  //calcul la position de la ligne (entre 0 et 7000) selon les lectures des capteurs
  unsigned int position = qtra.readLine(valeursCapteur);
  //Serial.print("Position : ");
  //Serial.print(position);

  //lorsqu'au moins 6 capteurs détectent une ligne, cela veut dire qu'il a atteint une ligne perpendiculaire
  // Serial.print("numSensorsHigh: ");
  // Serial.println(qtra.numSensorsHigh(valeursCapteur));
  if (qtra.numSensorsHigh(valeursCapteur) > 4)
  {
    while (qtra.numSensorsHigh(valeursCapteur) > 4)
    {
      avancer(0.2, 0.2);
    }

    if (arriveTable == false)
    {
      switch (positionCible)
      {
        case VERS_LA_BASE:
          rangeeActuelle--;
          Serial.print("numrangee--: ");
          Serial.println(rangeeActuelle);
          break;

        case VERS_LES_TABLES:
          rangeeActuelle++;
          Serial.print("numrangee++: ");
          Serial.println(rangeeActuelle);
          break;

        default:
          break;
      }
    }
    else
    {
      avancer(0, 0);
      //met le cabaret sur la table
      retourBase();
    }
  }

  // Calcul la différence entre le milieu des capteurs et la ligne
  int erreur = OBJECTIF - position;
  //Serial.print("\tErreur : ");
  //Serial.print(erreur);

  // Calcul un coefficient à mettre devant la vitesse de moteurs pour ajuster la trajectoire
  float ajustement = (kP * erreur) + (kD * (erreur - derniereErreur));
  //Serial.print("\tAjustement : ");
  //Serial.print(ajustement);
  //Serial.print("\t");

  // Garde en mémoire la dernière erreur
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

  /*for (unsigned char i = 0; i < NB_CAPTEURS; i++)
  {
    Serial.print(valeursCapteur[i]);
    Serial.print('\t');
  }
  Serial.println(position); // comment this line out if you are using raw values
  */
}

#endif // SUIVEURLIGNE_H
