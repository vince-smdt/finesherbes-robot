#ifndef SONORE_H
#define SONORE_H
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

void MicroSonoreTest(){// Test
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

int MicroSonoreRobot(){//Fonction arret proche table

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 1000000UL);
    distance = duration * 0.034 / 2; // Convertion en Cm

    Serial.println("Distance :" + String(distance));

    return distance; 
}
    #endif