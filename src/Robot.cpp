/*
  ME210 | Febuary 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Robot.cpp
  --------------------------
  Implementation of Robot.h
*/

#include "Robot.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the main robot hardware.
 */
void Robot::init() {
  Serial.begin(9600);
  setPinModes();
  waitForStart();
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: updateSensors
 * -------------------
 * This function get all the updated values for evaluating this state.
 */
void Robot::updateSensors() {
  frontSensorsBump[0] = readSensors_BUMP(BUMPER_LEFT);
  frontSensorsBump[1] = readSensors_BUMP(BUMPER_RIGHT);

  leftSensorIR[0]     = readSensor_IR(IR_IN_01);
  leftSensorIR[1]     = readSensor_IR(IR_IN_02);
  leftSensorIR[2]     = readSensor_IR(IR_IN_03);

  rightSensorIR[0]    = readSensor_IR(IR_IN_04);
  rightSensorIR[1]    = readSensor_IR(IR_IN_05);
  rightSensorIR[2]    = readSensor_IR(IR_IN_06);

  centerSensorIR[0]   = readSensor_IR(IR_IN_07);
  centerSensorIR[1]   = readSensor_IR(IR_IN_08);
  centerSensorIR[2]   = readSensor_IR(IR_IN_09);

  backSensorIR[0]     = readSensor_IR(IR_IN_10);
  backSensorIR[1]     = readSensor_IR(IR_IN_11);
  backSensorIR[2]     = readSensor_IR(IR_IN_12);
}

/*
 * Function: exitBase
 * -------------------
 * This function handles the algorythmic complexity of exiting the base.
 */
void Robot::exitBase() {
  findLine();
  findStart();
  state = attackTower1_s;
}

/*
 * Function: attackTower1
 * -------------------
 * This function handles the algorythmic complexity of attacking a the first tower.
 */
void Robot::attackTower1() {
  attackTower();
  state = attackTower2_s;
}

/*
 * Function: attackTower1
 * -------------------
 * This function handles the algorythmic complexity of attacking a the second tower.
 */
void Robot::attackTower2() {
  attackTower();
  state = hitBumper_s;
}

/*
 * Function: hitBumper
 * -------------------
 * This function handles the algorythmic complexity of hitting the pressure pad.
 */
void Robot::hitBumper() {
  state = quit_s;
}

/*
 * Function: quit
 * -------------------
 * This function handles the end of game shutdown.
 */
void Robot::quit() {
  analogWrite(MOTOR_FIRE_A,  0);
  analogWrite(MOTOR_FIRE_B,  0);
  analogWrite(MOTOR_LOAD_A,  0);
  analogWrite(MOTOR_LOAD_B,  0);
  analogWrite(MOTOR_LEFT_A,  0);
  analogWrite(MOTOR_LEFT_B,  0);
  analogWrite(MOTOR_RIGHT_A, 0);
  analogWrite(MOTOR_RIGHT_B, 0);
}

/*********************************  HELPERS  **********************************/
/*
 * Function: setPinModes
 * -------------------
 * This function sets the appropriate pinmodes.
 */
void Robot::setPinModes() {
  pinMode(START_PIN,      INPUT);
  pinMode(MULTIPLEXER_CS, INPUT);

  pinMode(BUMPER_LEFT,    INPUT);
  pinMode(BUMPER_RIGHT,   INPUT);

  pinMode(IR_IN_01,       INPUT);
  pinMode(IR_IN_02,       INPUT);
  pinMode(IR_IN_03,       INPUT);
  pinMode(IR_IN_04,       INPUT);
  pinMode(IR_IN_05,       INPUT);
  pinMode(IR_IN_06,       INPUT);
  pinMode(IR_IN_07,       INPUT);
  pinMode(IR_IN_08,       INPUT);
  pinMode(IR_IN_09,       INPUT);
  pinMode(IR_IN_10,       INPUT);
  pinMode(IR_IN_11,       INPUT);
  pinMode(IR_IN_12,       INPUT);

  pinMode(MOTOR_LOAD_A,   OUTPUT);
  pinMode(MOTOR_LOAD_B,   OUTPUT);
  pinMode(MOTOR_FIRE_A,   OUTPUT);
  pinMode(MOTOR_FIRE_B,   OUTPUT);
  pinMode(MOTOR_RIGHT_A,  OUTPUT);
  pinMode(MOTOR_RIGHT_B,  OUTPUT);
  pinMode(MOTOR_LEFT_A,   OUTPUT);
  pinMode(MOTOR_LEFT_B,   OUTPUT);
}

/*
 * Function: waitForStart
 * -------------------
 * This function pauses until the start button has been pressed.
 */
void Robot::waitForStart() {
  while(digitalRead(START_PIN) != LOW) Serial.println("Ready...");
  analogWrite(MOTOR_FIRE_A, 0);
  analogWrite(MOTOR_FIRE_B, LAUNCHER_SPEED);
  startTime = millis();
  state = exitBase_s;
}

/*
 * Function: findLine
 * -------------------
 * This function finds any line from the randomized start position.
 */
void Robot::findLine() {

}

/*
 * Function: findStart
 * -------------------
 * This function finds the desired start position.
 */
void Robot::findStart() {

}

/*
 * Function: attackTower
 * -------------------
 * This function handles the algorythmic complexity of attacking a single tower
 * given a posotion directly before the first turn off the main road.
 */
void Robot::attackTower() {
}

/*
 * Function: turnLeft
 * -------------------
 * This function turns left using the IR sensors.
 */
void Robot::turnLeft() {

}

/*
 * Function: turnRight
 * -------------------
 * This function turns Right using the IR sensors.
 */
void Robot::turnRight() {

}

/*
 * Function: turnForward
 * -------------------
 * This function moves forward.
 */
void Robot::turnForward() {

}

/*
 * Function: turnBackward
 * -------------------
 * This function moves backward.
 */
void Robot::turnBackward() {

}

/*
 * Function: launchEgg
 * -------------------
 * This function launches eggs.
 */
void Robot::launchEgg() {
  launchTime = millis();
  analogWrite(MOTOR_LOAD_A, 0);
  analogWrite(MOTOR_LOAD_B, LOADER_SPEED);
  // while((millis() - launchTime) < LAUNCH_TIMEOUT) Serial.println("Launching...");
  analogWrite(MOTOR_LOAD_A, 0);
  analogWrite(MOTOR_LOAD_B, 0);
}

/*
 * Function: detectedT
 * -------------------
 * This function returns true when reaching a junction.
 */
bool Robot::detectedT() {
  return true;
}

/*
 * Function: center
 * -------------------
 * This function self corrects to stay on line.
 */
void Robot::center() {

}

/*
 * Function: readSensor_IR
 * -------------------
 * This function handles the hardware abstraction of sensing a line
 */
bool Robot::readSensor_IR(uint8_t sensorNum) {
  //TODO
  //Comparitor BS
  return false;
}

/*
 * Function: readSensors_BUMP
 * -------------------
 * This function handles the hardware abstraction of sensing a bump
 */
bool Robot::readSensors_BUMP(uint8_t sensorNum) {
  //TODO
  //Comparitor BS
  return false;
}

/*
 * Function: checkTimer
 * -------------------
 * This function checks if the timer has expired.
 */
void Robot::checkTimer() {
  if((millis() - startTime) >= RUNTIME_TIMEOUT) state = quit_s;
}
