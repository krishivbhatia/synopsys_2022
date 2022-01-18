#include <MeccaBrain.h>
#include <stdio.h>

// defines pins number for solenoid electromagnet
#define SOLENOID 3     
// defines pins number for robot arm
#define CHAIN_SVL 8

MeccaBrain mecaChainSVL(CHAIN_SVL);

void setup() {

  pinMode(CHAIN_SVL, OUTPUT);
  pinMode(SOLENOID, OUTPUT);
  
  Serial.begin(9600);
  mecaChainSVL.communicate();

  //Servo1 is green
  mecaChainSVL.setServoColor(0, 0xF2);
  mecaChainSVL.communicate();
  
  //Servo2 is red
  mecaChainSVL.setServoColor(1, 0xF1);
  mecaChainSVL.communicate();
  delay(500);
  
  mecaChainSVL.setServoPosition(0, 120);
  mecaChainSVL.communicate();
  delay(500);
  
  mecaChainSVL.setServoPosition(1, 10);
  mecaChainSVL.communicate();
  delay(500);
  
  while(!Serial.available()) {}
}

void loop() {
  char buffer[16];
  if (Serial.available() > 0) {
    int size = Serial.readBytesUntil('\n', buffer, 12);
    // move arm to left
    if (buffer[0] == 'F') {
      mecaChainSVL.setServoPosition(0, 200);
    }
    else if (buffer[0] == 'S') {
      mecaChainSVL.setServoPosition(0, 180);
    }
    else if (buffer[0] == 'K') {
      mecaChainSVL.setServoPosition(0, 160);
    }
    mecaChainSVL.communicate();
    delay(2000);
      
    // move arm down to pick
    mecaChainSVL.setServoPosition(1, 230);
    mecaChainSVL.communicate();
    delay(2000);

    digitalWrite(SOLENOID, HIGH);
    // delay(4000);
      
    // move arm up after pick
    mecaChainSVL.setServoPosition(1, 40);
    mecaChainSVL.communicate();
    delay(3000);
      
    // move arm to right
    mecaChainSVL.setServoPosition(0, 50);
    mecaChainSVL.communicate();
    delay(4000);

    // move arm down to drop
    mecaChainSVL.setServoPosition(1, 200);
    mecaChainSVL.communicate();
    delay(2000);

    digitalWrite(SOLENOID, LOW);
    delay(2000);
    
    mecaChainSVL.setServoPosition(1, 10);
    mecaChainSVL.communicate();
    delay(500);
    
    mecaChainSVL.setServoPosition(0, 90);
    mecaChainSVL.communicate();
    delay(500);
  }
}
