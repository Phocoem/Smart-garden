#include <SimpleDHT.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include "DHT.h"            
const int DHTPIN = 4;      
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
#define Rx 0
#define Tx 1
SoftwareSerial mySerial(Rx,Tx);
#define cam_bien_muc_nuoc A1
#define cam_bien_muc_nuoc_2 A2
int muc_nuoc = 0;
int muc_nuoc_2 = 0;
int soilValue = 0; // set soil moisture value to 0
int soilPin = A0; // set soil sensor to A0
int chk;
int ldrValue=0;
int redLEDPin = 13; // set red led to pin 13 (water)
int yellowLEDPin = 12; // set yellow led to pin 12 (ldr)
int ldrPin = A5; // set ldr to A5
int motorPin = 3; // set motor to pin 3
int motor_Pin2 = 5;
String status;
int motorspeed=5000;
int lightLevel;
void setup() {
 Serial.begin(9600);
 Serial.setTimeout(50);
 dht.begin();
 pinMode(redLEDPin, OUTPUT);
 pinMode(yellowLEDPin, OUTPUT);
 pinMode(ldrPin, INPUT);
 pinMode(motorPin, OUTPUT);
pinMode(motor_Pin2, OUTPUT);
String ab;
String l_m;
int lm;
int i;
String data;
int a;
 }

void loop() {
 //chk = dht.read(DHTPIN);
 float temp = dht.readTemperature();
 float hum = dht.readHumidity();
 soilValue = analogRead(soilPin);
 ldrValue = analogRead(ldrPin);
 

  Serial.print(temp);
  Serial.print("#");
  Serial.print(hum);
  Serial.print("#");
  soilValue = map(analogRead(soilPin), 0, 1023, 100, 0);
  Serial.print(soilValue);
  Serial.print("#");
  ldrValue = map(analogRead(ldrPin), 0, 1023, 0, 100);
  Serial.print(100-ldrValue);
  Serial.print("#");
  int pop;
  pop=9;

  

 if(ab == "0") {
    Serial.print("muc nuoc be 1  ");
    Serial.println(muc_nuoc);
    Serial.print("muc nuoc be 2  ");
    Serial.println(muc_nuoc_2);
    while (muc_nuoc == 0){
      digitalWrite(motorPin, LOW);
    while (muc_nuoc_2 > 0){
      if (soilValue <= 20 && ldrValue < 50 && temp < 30){
        digitalWrite(motor_Pin2, HIGH);
        
      }
      else{
        digitalWrite(motor_Pin2, LOW);
      }
    }
      break;
    }
    while(muc_nuoc >= 1){
      digitalWrite(motor_Pin2, LOW);
      break;
    }
    while (muc_nuoc == 1){
      if (soilValue <= 20 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 2){
      if ( soilValue <= 30 && ldrValue < 100 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 3){
      if ( soilValue <= 40 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 4){
      if (soilValue <= 50 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 5){
      if ( soilValue <= 50 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
 }
  else if (ab=="1") {
    while(muc_nuoc == 0){
      digitalWrite(motorPin, LOW);
    while(muc_nuoc_2 > 0){
      if ( soilValue <= 30 && ldrValue < 50 && temp <30){
        digitalWrite(motor_Pin2, HIGH);
    }
    else{
      digitalWrite(motor_Pin2, LOW);
    }
    }
      break;
    }
    while(muc_nuoc >= 1){
      digitalWrite(motor_Pin2, LOW);
      break;
    }
    while (muc_nuoc == 1){
      if ( soilValue <= 30 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 2){
      if ( soilValue <= 40 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 3){
      if ( soilValue <= 50 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 4){
      if ( soilValue <= 60 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }
    while (muc_nuoc == 5){
      if ( soilValue <= 70 && ldrValue < 50 && temp <30){
        digitalWrite(motorPin, HIGH);
      }
      else{
        digitalWrite(motorPin, LOW);
      }
      break;
    }

 // Receive data from server
 
if (Serial.available() ) {
 status = Serial.readStringUntil('\n');
 

 if (status == "a") {
 
 analogWrite(motorPin, motorspeed);
 analogWrite(motorPin, HIGH);
 digitalWrite(redLEDPin, HIGH);
 digitalWrite(yellowLEDPin, HIGH);
 pop=1;

 } 
 if (status == "b") {
 
 analogWrite(motorPin, motorspeed);
 digitalWrite(redLEDPin, HIGH);
 digitalWrite(yellowLEDPin, LOW);
 analogWrite(motorPin, LOW);
 pop=2;
}

 if (status == "c") {
 
 analogWrite(motorPin, motorspeed);
 digitalWrite(redLEDPin, LOW);
 digitalWrite(yellowLEDPin, HIGH);
 analogWrite(motorPin, LOW);
 pop=2;

 } 
if (status == "d") {
 
 analogWrite(motorPin, motorspeed);
 digitalWrite(redLEDPin, HIGH);
 digitalWrite(yellowLEDPin, LOW);
 analogWrite(motorPin, LOW);
 pop=2;

 }
  if (status == "n") {
 
 analogWrite(motorPin,motorspeed);
 analogWrite(motorPin, HIGH);
 pop=1;
 
 
 } 
  if (status == "f") {
 
// analogWrite(motorPin, 255);
 analogWrite(motorPin, LOW);
 pop=2;

 }

}




 Serial.print(pop);
 Serial.print("#");

 delay(1000);
}