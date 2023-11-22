#include <QTRSensors.h>
#include <Arduino.h>
#include <LibRobus.h>

// Defines
#define LEFT 0
#define RIGHT 1

#define NB_CAPTEURS       8
#define NB_LECTURES       4  //Calcul la moyenne de 4 lectures d'un capteur pour normaliser la valeur
#define EMITTER_PIN       QTR_NO_EMITTER_PIN  //Pas d'emetteur

//initialise tous les capteurs dans le arduino
QTRSensorsAnalog qtra((unsigned char[]) {A7, A6, A5, A4, A3, A2, A1, A0}, NB_CAPTEURS, NB_LECTURES, EMITTER_PIN);
unsigned int valeursCapteur[NB_CAPTEURS];


//Constante et propriété du PID
const int OBJECTIF = 3500;
#define VITESSE_MAX  0.3

const float kP = 0.0001;
const float kD = 0.0002;
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
  Serial.begin(9600);
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

// Fait avancer le robot avec l'ajustement PID et ajuste les coefficients de correction
void avancer(float vitesseG, float vitesseD) {
  MOTOR_SetSpeed(LEFT, vitesseG);
  MOTOR_SetSpeed(RIGHT, vitesseD);
}


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


