/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: test.cpp
  --------------------------
  Unit test suite.
*/
#include "Config.h"
#include <AccelStepper.h>

/***********************************  BOOT  ***********************************/
AccelStepper stepper(1, MOTOR_STEP_STEP, MOTOR_STEP_DIR);
int main() {
  Serial.begin(9600);
  pinMode(MOTOR_STEP_DIR,   OUTPUT);
  pinMode(MOTOR_STEP_STEP,  OUTPUT);
  pinMode(US_TRIG,          OUTPUT);
  pinMode(US_ECHO,          INPUT);
  stepper.setMaxSpeed(LAUNCH_SPEED);
  stepper.setSpeed(LAUNCH_SPEED);
  uint32_t start = millis();
/***********************************  MAIN  ***********************************/
  while(true) {
    digitalWrite(US_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(US_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_TRIG, LOW);
    float distance = pulseIn(US_ECHO, HIGH, 10000);
    if (distance == 0) return US_THRESHOLD;
    float inches =  distance  / 148.0;
    Serial.println(inches);
    if ((millis() - start) >= 5000) stepper.runSpeed();
    delay(BUFFER_CLEAR_TIME);
  }
}
