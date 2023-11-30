#ifndef SUIVEURLIGNE_H
#define SUIVEURLIGNE_H

#include <QTRSensors.h>

#include "Constantes.h"
#include "Globales.h"

#include "General.h"
#include "DetectMicroSonore.h"

//initialise tous les capteurs dans le arduino
QTRSensorsAnalog qtra((unsigned char[]) {A7, A6, A5, A4, A3, A2, A1, A0}, NB_CAPTEURS_SUIVEUR_LIGNE, NB_LECTURES_SUIVEUR_LIGNE, SUIVEUR_LIGNE_EMITTER_PIN);
unsigned int valeursCapteur[NB_CAPTEURS_SUIVEUR_LIGNE];

// Dernière erreur du suiveur de ligne
float derniereErreur = 0;

void calibrationSuiveurLigne();
bool suivreLigne(float p_vitesse);

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
    SerialPrint.print(qtra.calibratedMinimumOn[i]);
    SerialPrint.print(' ');
  }
  SerialPrint.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NB_CAPTEURS_SUIVEUR_LIGNE; i++)
  {
    SerialPrint.print(qtra.calibratedMaximumOn[i]);
    SerialPrint.print(' ');
  }
}

bool suivreLigne(float p_vitesse)
{
  bool ligneDetectee = false;
  
  // Calcul la position de la ligne (entre 0 et 7000) selon les lectures des capteurs
  unsigned int position = qtra.readLine(valeursCapteur);

  //lorsqu'au moins 6 capteurs détectent une ligne, cela veut dire qu'il a atteint une ligne perpendiculaire
  if (qtra.numSensorsHigh(valeursCapteur) > 4 && temps_ecoule(g_debut_sortie_de_ligne) > DELAI_SORTIE_DE_LIGNE)
  {
    // debug_beep(1, 25);
    g_debut_sortie_de_ligne = millis();
    ligneDetectee = true;
  }

  // Calcul la différence entre le milieu des capteurs et la ligne
  int erreur = POSITION_CENTRE_LIGNE - position;

  // Calcul un coefficient à mettre devant la vitesse de moteurs pour ajuster la trajectoire
  float ajustement = (kP * erreur) + (kD * (erreur - derniereErreur));

  // Garde en mémoire la dernière erreur
  derniereErreur = erreur;

  // Corrige la vitesse des deux moteurs
  float vitesseG = constrain(p_vitesse + ajustement, 0 , p_vitesse);
  float vitesseD = constrain(p_vitesse - ajustement, 0 , p_vitesse);
  avancer(vitesseG, vitesseD);

  return ligneDetectee;
}

#endif // SUIVEURLIGNE_H
