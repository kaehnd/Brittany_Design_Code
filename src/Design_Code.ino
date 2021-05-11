
#include "BMI088.h"

#define TRIGGER_ACCELERATION 70.0 //Set the release acceleration
#define TRIGGER_GyroscopeHigh 90.00 //Set the high end release for the gyroscope
#define TRIGGER_GyroscopeLow -90.00 //Set the low end release for the gyroscope
#define ReleasePin 1 //Set the release pin
#define ButtonPin 9//Set the reset button pin

static float ax = 0, ay = 0, az = 0; //initialize the accelerometer variables
static float gx = 0, gy = 0, gz = 0; //initialize the gyroscope variables
//int16_t temp = 0; //initialize the temperature variable

void setup(void) {
    Wire.begin();
    pinMode(ReleasePin,OUTPUT); //Set the pin as the output
    digitalWrite(ReleasePin,LOW); //Set the GPIO pin to low
    digitalWrite(ButtonPin,HIGH); //Set the Release Button Pin to High

    while (1) {
        if (bmi088.isConnection()) { //Determine if the BMI088 is connected or not and print out that information
            bmi088.initialize();
            break;
        } else {
          
        }

        delay(2000);
        
    }
    
}

void loop(void) {
    bmi088.getAcceleration(&ax, &ay, &az); //Get the accelerometer values
    bmi088.getGyroscope(&gx, &gy, &gz); //Get the gyroscope values
    //temp = bmi088.getTemperature(); //Get the temperature value

    run_tests();


    if (ay >= TRIGGER_ACCELERATION || gx >= TRIGGER_GyroscopeHigh || gx <= TRIGGER_GyroscopeLow){ //Determine if any of the conditions are exceeded
      while(1){
        if(ButtonPin == 1){
          digitalWrite(ReleasePin,HIGH); //Set the GPIO pin to high to send voltage to the solenoid
        }
        else{
          break;
        }
      }
    } 

    delay(50);
}

void acceleration_test(){
  ay = 100; // set the acceleration to be above the release level
  if(ReleasePin == 1){
    Serial.print("The pin is released"); //Confirm the pin is released
    digitalWrite(ButtonPin,LOW); //Simulate button press
    if(ReleasePin == 0){
      Serial.print("The code is reset"); //Confirm the code is reset
    }
  }
}

void low_gyro_test(){
  gy = -100; //Set the gyroscope angle above the minimum allowable angle
  if(ReleasePin ==1){
    Serial.print("The pin is released"); //Confirm the pin is released
    digitalWrite(ButtonPin,LOW); //simulate the button press
    if(ReleasePin == 0){
      Serial.print("The code is reset"); //Confirm the code is reset
    }
  }
}

void high_gyro_test(){
  gy = 100; //Set the gyroscope angle above the maximum allowable angle
  if(ReleasePin ==1){
    Serial.print("The pin is released"); //Confirm the pin is released
    digitalWrite(ButtonPin,LOW); //simulate the button press
    if(ReleasePin == 0){
      Serial.print("The code is reset"); //Confirm the code is reset
    }
  }
}

void run_tests(){
  acceleration_test();
  low_gyro_test();
  high_gyro_test();
}
