#include "BMI088.h"

#define ReleasePin 1 //Set the release pin

void setup() {
  // put your setup code here, to run once:
    Wire.begin();
    pinMode(ReleasePin,OUTPUT); //Set the pin as the output
    digitalWrite(ReleasePin,LOW); //Set the GPIO pin to low
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1){
  digitalWrite(ReleasePin,HIGH); //Set the GPIO pin to high to send voltage to the solenoid
  delay(50);
  digitalWrite(ReleasePin,LOW); //Set the GPIO pin to high to send voltage to the solenoid
  delay(50);
  }

}
