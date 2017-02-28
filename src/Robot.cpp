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
  PCB.init(MULTIPLEXER_CS);
  setPinModes();
  waitForStart();
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: getState
 * -------------------
 * This function returns the current state.
 */
state_tier_1_t Robot::getState() {
  return state_1;
}

/*
 * Function: updateState
 * -------------------
 * This function updates the values that are state indepndent.
 */
void Robot::updateState() {
  checkTimer();
  updateSensors();
  center();
  printState();
}

/*
 * Function: exitBase
 * -------------------
 * This function handles the algorythmic complexity of exiting the base.
 */
void Robot::exitBase() {
  if      (state_2 == searching_s && findLine()) orientLine();
  else if ((state_2 == orientingL_s ||  state_2 == orientingR_s) && orientLine()) findStart();
  else if (state_2 == finding_s   && findStart()) {
    state_1 = attackTower1_s;
    state_2 = approaching_s;
  }
}

/*
 * Function: attackTower1
 * -------------------
 * This function handles the algorythmic complexity of attacking a the first tower.
 */
void Robot::attackTower1() {
  if (attackTower()) {
    state_1 = attackTower2_s;
    state_2 = approaching_s;
    turnForward();
  }
}

/*
 * Function: attackTower1
 * -------------------
 * This function handles the algorythmic complexity of attacking a the second tower.
 */
void Robot::attackTower2() {
  if (attackTower()) {
    state_1 = hitBumper_s;
    turnRight();
  }
}

/*
 * Function: hitBumper
 * -------------------
 * This function handles the algorythmic complexity of hitting the pressure pad.
 */
void Robot::hitBumper() {
  if      (state_3 == turningRight_s    && detectedT()) turnForward();
  else if (state_3 == turningForeward_s &&
    (frontSensorsBump[0] || frontSensorsBump[1])) state_1 = quit_s;
}

/*
 * Function: quit
 * -------------------
 * This function handles the end of game shutdown.
 */
void Robot::quit() {
  analogWrite(MOTOR_LEFT_SPEED,  0);
  analogWrite(MOTOR_RIGHT_SPEED, 0);
  analogWrite(MOTOR_LOAD_SPEED,  0);
  analogWrite(MOTOR_FIRE_SPEED,  0);
}

/*********************************  HELPERS  **********************************/
/*
 * Function: setPinModes
 * -------------------
 * This function sets the appropriate pinmodes.
 */
void Robot::setPinModes() {
  pinMode(START_PIN,            INPUT);

  pinMode(BUMPER_LEFT,          INPUT);
  pinMode(BUMPER_RIGHT,         INPUT);

  pinMode(IR_IN_01,             INPUT);
  pinMode(IR_IN_02,             INPUT);
  pinMode(IR_IN_03,             INPUT);
  pinMode(IR_IN_04,             INPUT);
  pinMode(IR_IN_05,             INPUT);
  pinMode(IR_IN_06,             INPUT);
  pinMode(IR_IN_07,             INPUT);
  pinMode(IR_IN_08,             INPUT);
  pinMode(IR_IN_09,             INPUT);
  pinMode(IR_IN_10,             INPUT);
  pinMode(IR_IN_11,             INPUT);
  pinMode(IR_IN_12,             INPUT);

  pinMode(MOTOR_LEFT_DIR,       OUTPUT);
  pinMode(MOTOR_LEFT_SPEED,     OUTPUT);
  pinMode(MOTOR_RIGHT_DIR,      OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED,    OUTPUT);
  pinMode(MOTOR_LOAD_DIR,       OUTPUT);
  pinMode(MOTOR_LOAD_SPEED,     OUTPUT);
  pinMode(MOTOR_FIRE_DIR,       OUTPUT);
  pinMode(MOTOR_FIRE_SPEED,     OUTPUT);
  digitalWrite(MOTOR_LOAD_DIR,  FOREWARD);
  digitalWrite(MOTOR_FIRE_DIR,  FOREWARD);
}

/*
 * Function: waitForStart
 * -------------------
 * This function pauses until the start button has been pressed.
 */
void Robot::waitForStart() {
  while(digitalRead(START_PIN) != LOW) Serial.println("Ready...");
  startTime = millis();
  state_1 = exitBase_s;
  state_2 = searching_s;
  turnForward();
}

/*
 * Function: checkTimer
 * -------------------
 * This function checks if the timer has expired.
 */
void Robot::checkTimer() {
  if((millis() - startTime) >= RUNTIME_TIMEOUT) state_1 = quit_s;
}

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
 * Function: printState
 * -------------------
 * This function provides usefull debugging information.
 */
void Robot::printState() {
  Serial.print("STATE 1 : ");
  Serial.print(state_1);
  Serial.print("STATE 2 : ");
  Serial.print(state_2);
  Serial.print("STATE 3 : ");
  Serial.print(state_3);
  Serial.print('\n');
}

/*
 * Function: findLine
 * -------------------
 * This function finds any line from the randomized start position.
 */
bool Robot::findLine() {
  bool done = false;
  if      (leftSensorIR[0]) {
    state_2 = orientingL_s;
    done = true;
  }
  else if (rightSensorIR[0]) {
    state_2 = orientingR_s;
    done = true;
  }
  else if (frontSensorsBump[0] || frontSensorsBump[1]) {
    escapeTime = millis();
    turnBackward();
  }
  else if (state_3 == turningBackward_s && (millis() - escapeTime) >= ESCAPE_TIMEOUT) {
    escapeTime = millis();
    turnRight();
  }
  else if (state_3 == turningRight_s && (millis() - escapeTime) >= ESCAPE_TIMEOUT) turnForward();
  return done;
}

/*
 * Function: orientLine
 * -------------------
 * This function centers the robot onto the start line.
 */
bool Robot::orientLine() {
  bool done = false;
  if      (state_2 == orientingL_s && state_3 == turningForeward_s && centerSensorIR[1]) turnRight();
  else if (state_2 == orientingR_s && state_3 == turningForeward_s && centerSensorIR[1]) turnLeft();
  else if ((state_3 == turningLeft_s || state_3 == turningRight_s) && detectedI()) {
    state_2 = finding_s;
    turnForward();
    done = true;
  }
  return done;
}

/*
 * Function: findStart
 * -------------------
 * This function finds the desired start position.
 */
bool Robot::findStart() {
  bool done = false;
  if      (detectedS()) done = true;
  else if (frontSensorsBump[0] || frontSensorsBump[1]) {
    escapeTime = millis();
    turnBackward();
  }
  else if (state_3 == turningBackward_s && (millis() - escapeTime) >= ESCAPE_TIMEOUT) turnRight();
  else if (state_3 == turningRight_s && detectedI()) turnForward();
  else if (state_3 == turningForeward_s && detectedLeft()) turnLeft();
  else if (state_3 == turningForeward_s && detectedRight()) turnRight();
  else if (state_3 == turningLeft_s && detectedLeft()) turnForward();
  else if (state_3 == turningRight_s && detectedRight()) turnForward();
  return done;
}

/*
 * Function: attackTower
 * -------------------
 * This function handles the algorythmic complexity of attacking a single tower
 * given a posotion directly before the first turn off the main road.
 */
bool Robot::attackTower() {
  bool done = false;
  if      (state_3 == turningForeward_s && state_2 == approaching_s && detectedT()) turnLeft();
  else if (state_3 == turningLeft_s     && detectedT()) {
    state_2 = loading_s;
    turnForward();
  }
  else if (state_3 == turningForeward_s && state_2 == loading_s   && detectedT()) launchEgg();
  else if (state_3 == launchingEggs_s   && launchEgg()) turnBackward();
  else if (state_3 == turningBackward_s && detectedT()) {
    turnRight();
    done = true;
  }
  return done;
}

/*
 * Function: launchEgg
 * -------------------
 * This function launches eggs.
 */
bool Robot::launchEgg() {
  bool done = false;
  if (state_2 == loading_s) {
    launchTime = millis();
    state_3 = launchingEggs_s;
    state_2 = attacking_s;
    analogWrite(MOTOR_LEFT_SPEED,  0);
    analogWrite(MOTOR_RIGHT_SPEED, 0);
    analogWrite(MOTOR_LOAD_SPEED, LOADER_SPEED);
    analogWrite(MOTOR_FIRE_SPEED, LAUNCH_SPEED);
  }
  if((millis() - launchTime) >= LAUNCH_TIMEOUT) {
    analogWrite(MOTOR_LOAD_SPEED, 0);
    analogWrite(MOTOR_FIRE_SPEED, 0);
    done = true;
  }
  return done;
}

/*
 * Function: turnLeft
 * -------------------
 * This function turns left using the IR sensors.
 */
void Robot::turnLeft() {
  state_3 = turningLeft_s;
  digitalWrite(MOTOR_LEFT_DIR,   BACKWARD);
  digitalWrite(MOTOR_RIGHT_DIR,  FOREWARD);
  analogWrite(MOTOR_LEFT_SPEED,  DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_SPEED, DRIVE_SPEED);
}

/*
 * Function: turnRight
 * -------------------
 * This function turns Right using the IR sensors.
 */
void Robot::turnRight() {
  state_3 = turningRight_s;
  digitalWrite(MOTOR_LEFT_DIR,   FOREWARD);
  digitalWrite(MOTOR_RIGHT_DIR,  BACKWARD);
  analogWrite(MOTOR_LEFT_SPEED,  DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_SPEED, DRIVE_SPEED);
}

/*
 * Function: turnForward
 * -------------------
 * This function moves forward.
 */
void Robot::turnForward() {
  state_3 = turningForeward_s;
  digitalWrite(MOTOR_LEFT_DIR,   FOREWARD);
  digitalWrite(MOTOR_RIGHT_DIR,  FOREWARD);
  analogWrite(MOTOR_LEFT_SPEED,  DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_SPEED, DRIVE_SPEED);
}

/*
 * Function: turnBackward
 * -------------------
 * This function moves backward.
 */
void Robot::turnBackward() {
  state_3 = turningBackward_s;
  digitalWrite(MOTOR_LEFT_DIR,   BACKWARD);
  digitalWrite(MOTOR_RIGHT_DIR,  BACKWARD);
  analogWrite(MOTOR_LEFT_SPEED,  DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_SPEED, DRIVE_SPEED);
}

/*
 * Function: center
 * -------------------
 * This function self corrects to stay on line.
 */
void Robot::center() {
  if(state_3 == turningForeward_s) {
    //TODO Robustness BS
  }
  if(state_3 == turningBackward_s) {
    //TODO Robustness BS
  }
}

/*
 * Function: detectedI
 * -------------------
 * This function returns true when reaching the start.
 */
bool Robot::detectedI() {
  //TODO Robustness BS
  if (
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
    !leftSensorIR[1] && !centerSensorIR[0] &&  centerSensorIR[1] && !centerSensorIR[2] && !rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2] &&
                        !backSensorIR[0]   &&  backSensorIR[1]   && !backSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedLeft
 * -------------------
 * This function returns true when reaching a left junction.
 */
bool Robot::detectedLeft() {
  //TODO Robustness BS
  if (
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
     leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] && !centerSensorIR[2] && !rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedRight
 * -------------------
 * This function returns true when reaching a right junction.
 */
bool Robot::detectedRight() {
  //TODO Robustness BS
  if (
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
    !leftSensorIR[1] && !centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedS
 * -------------------
 * This function returns true when reaching the start.
 */
bool Robot::detectedS() {
  //TODO Robustness BS
  if (
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
     leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2] &&
                        !backSensorIR[0]   && !backSensorIR[1]   && !backSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedT
 * -------------------
 * This function returns true when reaching a junction.
 */
bool Robot::detectedT() {
  //TODO Robustness BS
  if (
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
     leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2] &&
                        !backSensorIR[0]   &&  backSensorIR[1]   && !backSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: readSensor_IR
 * -------------------
 * This function handles the hardware abstraction of sensing a line.
 */
bool Robot::readSensor_IR(uint8_t pinNum) {
  uint16_t value = PCB.readValue(pinNum);
  //TODO Comparitor BS
  return value >= BLACK_THRESHOLD;
}

/*
 * Function: readSensors_BUMP
 * -------------------
 * This function handles the hardware abstraction of sensing a bump.
 */
bool Robot::readSensors_BUMP(uint8_t pinNum) {
  //TODO Comparitor BS
  return digitalRead(pinNum);
}
