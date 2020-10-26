//#include <Servo.h> 
#include "ServoEasing.h"

ServoEasing servo;

int angle = 0;
int intensityPot = A0;
int restPot = A1;
int intensity = 10;
int del = 10;
int bursts = 5;
int minVinkel = 20, maxVinkel = 180;
int led = 3;

unsigned long lastCheck = millis();
int rest = 1000;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
  Serial.begin(115200);
  servo.attach(11);
  servo.write(angle);
  servo.setEasingType(EASE_CUBIC_IN_OUT);
  delay(500); 
}

void loop() {
  
  /*
  int intensityReading = analogRead(intensityPot);
  int restReading = analogRead(restPot);
  
  Serial.print("intens: ");
  Serial.print(intensityReading);
  Serial.print(" rest: ");
  Serial.print(restReading);

  int angle = map(intensityReading,1023,0,0,180);

  Serial.print(" angle: ");
  Serial.println(angle);
  
  servo.setSpeed(100);
  servo.startEaseTo(angle);
  */
  
  if (millis() > lastCheck + rest) {
    int intensityReading = analogRead(intensityPot);
    int restReading = analogRead(restPot);
    intensity = map(intensityReading,1023,0,5,100);
    rest = map(restReading,1023,0,150,3000);
    int randomIncrement = random(25,85);
    if (random(2) == 0) randomIncrement = randomIncrement * -1;
    angle = angle + randomIncrement; 
    angle = constrain(angle,minVinkel,maxVinkel);
    servo.setSpeed(intensity);
    servo.startEaseTo(angle);
    lastCheck = millis();
  }
  
  Serial.print(" rest ");
  Serial.print(rest);
  Serial.print(" destination angle ");
  Serial.print(angle);
  Serial.print(" servo angle ");
  Serial.println(servo.getCurrentAngle());
  
  servo.continueWithInterrupts();
  delay(10);
}
