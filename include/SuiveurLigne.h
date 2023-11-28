#ifndef SUIVEURLIGNE_H
#define SUIVEURLIGNE_H

#include <QTRSensors.h>

#include "Constantes.h"

#include "General.h"
#include "DetectMicroSonore.h"

//initialise tous les capteurs dans le arduino
QTRSensorsAnalog qtra((unsigned char[]) {A7, A6, A5, A4, A3, A2, A1, A0}, NB_CAPTEURS_SUIVEUR_LIGNE, NB_LECTURES_SUIVEUR_LIGNE, SUIVEUR_LIGNE_EMITTER_PIN);
unsigned int valeursCapteur[NB_CAPTEURS_SUIVEUR_LIGNE];

// Propriété du PID
const float kP = 0.0001;
const float kD = 0.001;
float derniereErreur = 0;

void calibrationSuiveurLigne();
void suivreLigne();

void calibrationSuiveurLigne()
{
  pinMode(SUIVEUR_LIGNE_LUMIERE_PIN, OUTPUT);
  digitalWrite(SUIVEUR_LIGNE_LUMIERE_PIN, HIGH);    //active la lumière du arduino
  for (int i = 0; i < 150; i++)  //calibration des capteurs
  {
    qtra.calibrate(); 
  }
  digitalWrite(SUIVEUR_LIGNE_LUMIERE_PIN, LOW);     //éteint la lumière, la calibration est finie

  // print the calibration minimum values measured when emitters were on
  for (int i = 0; i < NB_CAPTEURS_SUIVEUR_LIGNE; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NB_CAPTEURS_SUIVEUR_LIGNE; i++)
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
  // Serial.print("numSensorsHigh: ");
  // Serial.println(qtra.numSensorsHigh(valeursCapteur));
  if (qtra.numSensorsHigh(valeursCapteur) > 4 && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE)
  {
    debug_beep(1, 25);
    g_debut_sortie_de_ligne = millis();

    switch (g_etat)
    {
      case SUIVRE_LIGNE_VERS_RANGEE: {
        g_rangee_actuelle--;
        Serial.print("g_rangee_actuelle--: ");
        Serial.println(g_rangee_actuelle);
        break;
      }

      case SUIVRE_LIGNE_VERS_CUISINE: {
        g_rangee_actuelle++;
        Serial.print("g_rangee_actuelle++: ");
        Serial.println(g_rangee_actuelle);
        break;
      }

      case SUIVRE_LIGNE_VERS_TABLE: {
        g_devant_table = true;
        break;
      }

      case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE: {
        g_devant_table = false;
        break;
      }
    }
  }

  // Calcul la différence entre le milieu des capteurs et la ligne
  int erreur = POSITION_CENTRE_LIGNE - position;
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
