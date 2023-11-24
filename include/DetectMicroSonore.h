#ifndef GENERAL_H
#define GENERAL_H
#include <Arduino.h>
#include <LibRobus.h>



//SANS LCD
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void MicroSonoreSetup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void MicroSonoreTest(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 1000000UL);
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.println(distance);
    
}

int MicroSonoreRobot(){
  //MOTOR_SetSpeed(RIGHT, 0.2);
  //MOTOR_SetSpeed(LEFT, 0.2);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 1000000UL);
    distance = duration * 0.034 / 2;

    Serial.println("Distance :" + String(distance));

    return distance;
}
//AVEC LCD
/*
#include <LiquidCrystal.h>
LiquidCrystal lcd(1,2,4,5,6,7);
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;

unsigned long previousMillis = 0;

void setup(){
    lcd.begin(16,2);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}
void loop(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * 0.034/2;
    distanceInch = duration * 0.0133/2;
    lcd. setCursor(0,0);
    lcd.print("Distance:");
    lcd.print(distanceCm);
    delay(10);
    lcd.print(" cm"); 
    
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.print(distanceInch);
    delay(10);
    lcd.print(" inch");*/
    #endif