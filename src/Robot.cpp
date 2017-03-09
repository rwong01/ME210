/*
  ME210 | March 2017
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
  // stepper.setRPM(1);
  // stepper.setMicrostep(1);
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
  updateSensors();
  printState();
  checkTimer();
  checkBumper();
  center();
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
  if      (state_3 == turningRightOne_s && detectedRightOff()) state_3 = turningRightTwo_s;
  else if (state_3 == turningRightTwo_s && detectedPluss()) turnForward();
  else if ((state_3 == turningForeward_s) && detectedPluss()) state_3 = hittingBumper_s;
}

/*
 * Function: quit
 * -------------------
 * This function handles the end of game shutdown.
 */
void Robot::quit() {
  analogWrite(MOTOR_LEFT_FWD,   0);
  analogWrite(MOTOR_LEFT_REV,   0);
  analogWrite(MOTOR_RIGHT_FWD,  0);
  analogWrite(MOTOR_RIGHT_REV,  0);
  analogWrite(MOTOR_FIRE_FWD,   0);
  analogWrite(MOTOR_FIRE_REV,   0);
  Serial.print("Done...");
  Serial.print('\n');
}

/*********************************  HELPERS  **********************************/
/*
 * Function: setPinModes
 * -------------------
 * This function sets the appropriate pinmodes.
 */
void Robot::setPinModes() {
  pinMode(START_PIN,        INPUT_PULLUP);

  pinMode(US_TRIG,          OUTPUT);
  pinMode(US_ECHO,          INPUT);

  pinMode(BUMPER_LEFT,      INPUT_PULLUP);
  pinMode(BUMPER_RIGHT,     INPUT_PULLUP);

  pinMode(IR_IN_01,         INPUT);
  pinMode(IR_IN_02,         INPUT);
  pinMode(IR_IN_03,         INPUT);
  pinMode(IR_IN_04,         INPUT);
  pinMode(IR_IN_05,         INPUT);
  pinMode(IR_IN_06,         INPUT);
  pinMode(IR_IN_07,         INPUT);
  pinMode(IR_IN_08,         INPUT);
  pinMode(IR_IN_09,         INPUT);
  pinMode(IR_IN_10,         INPUT);
  pinMode(IR_IN_11,         INPUT);

  pinMode(MOTOR_LEFT_FWD,   OUTPUT);
  pinMode(MOTOR_LEFT_REV,   OUTPUT);
  pinMode(MOTOR_RIGHT_FWD,  OUTPUT);
  pinMode(MOTOR_RIGHT_REV,  OUTPUT);
  pinMode(MOTOR_FIRE_FWD,   OUTPUT);
  pinMode(MOTOR_FIRE_REV,   OUTPUT);
  pinMode(MOTOR_STEP_DIR,   OUTPUT);
  pinMode(MOTOR_STEP_STEP,  OUTPUT);
}

/*
 * Function: waitForStart
 * -------------------
 * This function pauses until the start button has been pressed.
 */
void Robot::waitForStart() {
  while(digitalRead(START_PIN) != LOW) {
    Serial.print("Ready...\n");
    updateSensors();
    printState();
    delay(BUFFER_CLEAR_TIME);
  }
  startTime = millis();
  state_1 = attackTower1_s;
  state_2 = approaching_s;
  turnForward();
}

/*
 * Function: updateSensors
 * -------------------
 * This function get all the updated values for evaluating this state.
 */
void Robot::updateSensors() {
  leftSensorIROLD[0]  = leftSensorIR[0];
  leftSensorIROLD[1]  = leftSensorIR[1];
  leftSensorIROLD[2]  = leftSensorIR[2];

  rightSensorIROLD[0] = rightSensorIR[0];
  rightSensorIROLD[1] = rightSensorIR[1];
  rightSensorIROLD[2] = rightSensorIR[2];

  distance            = readSensor_US();

  frontSensorBump[0]  = readSensors_BUMP(BUMPER_LEFT);
  frontSensorBump[1]  = readSensors_BUMP(BUMPER_RIGHT);

  frontSensorIR[0]    = readSensor_IR(IR_IN_01);
  frontSensorIR[1]    = readSensor_IR(IR_IN_02);

  leftSensorIR[0]     = readSensor_IR(IR_IN_03);
  leftSensorIR[1]     = readSensor_IR(IR_IN_04);
  leftSensorIR[2]     = readSensor_IR(IR_IN_05);

  rightSensorIR[0]    = readSensor_IR(IR_IN_06);
  rightSensorIR[1]    = readSensor_IR(IR_IN_07);
  rightSensorIR[2]    = readSensor_IR(IR_IN_08);

  centerSensorIR[0]   = readSensor_IR(IR_IN_09);
  centerSensorIR[1]   = readSensor_IR(IR_IN_10);
  centerSensorIR[2]   = readSensor_IR(IR_IN_11);

}

/*
 * Function: printState
 * -------------------
 * This function provides usefull debugging information.
 */
void Robot::printState() {
  Serial.print("STATE 1 : ");
  Serial.print(states_teir_1_names[state_1]);
  Serial.print(" STATE 2 : ");
  Serial.print(states_teir_2_names[state_2]);
  Serial.print(" STATE 3 : ");
  Serial.print(states_teir_3_names[state_3]);
  Serial.print(" STATE 4 : ");
  Serial.print(states_teir_4_names[state_4]);

  Serial.print('\n');
  Serial.print(distance);
  Serial.print(" inches");
  Serial.print('\n');
  Serial.print(frontSensorBump[0]);
  Serial.print("   ");
  Serial.print(frontSensorBump[1]);
  Serial.print('\n');
  Serial.print(" ");
  Serial.print(frontSensorIR[0]);
  Serial.print(" ");
  Serial.print(frontSensorIR[1]);
  Serial.print('\n');
  Serial.print(leftSensorIR[0]);
  Serial.print("   ");
  Serial.print(rightSensorIR[0]);
  Serial.print('\n');
  Serial.print(leftSensorIR[1]);
  Serial.print(centerSensorIR[0]);
  Serial.print(centerSensorIR[1]);
  Serial.print(centerSensorIR[2]);
  Serial.print(rightSensorIR[1]);
  Serial.print('\n');
  Serial.print(leftSensorIR[2]);
  Serial.print("   ");
  Serial.print(rightSensorIR[2]);
  Serial.print('\n');
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
 * Function: checkBumper
 * -------------------
 * This function checks if the bumpers have triggered.
 */
void Robot::checkBumper() {
  if ((frontSensorBump[0] || frontSensorBump[1])) state_1 = quit_s;
}

/*
 * Function: center
 * -------------------
 * This function self corrects to stay on line.
 */
void Robot::center() {
  if      ((state_3 != turningForeward_s) && (state_3 != ignoringPluss_s)) return;
  else if ((state_4 == inchLeft_s) && frontSensorIR[1]) {
    state_4 = inchRight_s;
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
  else if ((state_4 == inchRight_s) && !frontSensorIR[1]) {
    state_3 = turningForeward_s;
    state_4 = inchLeft_s;
    analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
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
  else if (frontSensorBump[0] || frontSensorBump[1]) {
    escapeTime = millis();
    turnBackward();
  }
  else if (state_3 == turningBackward_s && (millis() - escapeTime) >= ESCAPE_TIMEOUT) {
    escapeTime = millis();
    turnRight();
  }
  else if (state_3 == turningRightOne_s && (millis() - escapeTime) >= ESCAPE_TIMEOUT) turnForward();
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
  else if ((state_3 == turningLeftOne_s || state_3 == turningRightOne_s) && detectedI()) {
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
  else if (frontSensorBump[0] || frontSensorBump[1]) {
    escapeTime = millis();
    turnBackward();
  }
  else if (state_3 == turningBackward_s && (millis() - escapeTime) >= ESCAPE_TIMEOUT) turnRight();
  else if (state_3 == turningRightOne_s && detectedRightOff()) state_3 = turningRightTwo_s;
  else if (state_3 == turningRightTwo_s && detectedI()) turnForward();

  else if (state_3 == turningForeward_s && detectedLeft()) turnLeft();
  else if (state_3 == turningLeftOne_s  && detectedLeftOff()) state_3 = turningLeftTwo_s;
  else if (state_3 == turningLeftTwo_s && detectedLeft()) turnForward();

  else if (state_3 == turningForeward_s && detectedRight()) turnRight();
  else if (state_3 == turningRightOne_s && detectedRightOff()) state_3 = turningRightTwo_s;
  else if (state_3 == turningRightTwo_s && detectedRight()) turnForward();
  return done;
}

/*
 * Function: attackTower
 * -------------------
 * This function handles the algorythmic complexity of attacking a single tower.
 */
bool Robot::attackTower() {
  bool done = false;
  if      (state_3 == turningForeward_s && detectedPluss()) state_3 = ignoringPluss_s;
  else if (state_3 == ignoringPluss_s && detectedPluss()) state_3 = centeringPluss_s;
  else if (state_3 == centeringPluss_s  && detectedPlussCenter()) {
    state_2 = loading_s;
    state_3 = launchingEggs_s;
  }
  else if (state_3 == launchingEggs_s && launchEgg()) done = true;
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
    analogWrite(MOTOR_FIRE_FWD, LAUNCH_SPEED);
    analogWrite(MOTOR_FIRE_REV, 0);
    // stepper.rotate(120);
  }
  if((millis() - launchTime) >= LAUNCH_TIMEOUT) {
    analogWrite(MOTOR_FIRE_FWD, 0);
    analogWrite(MOTOR_FIRE_REV, 0);
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
  state_3 = turningLeftOne_s;
  analogWrite(MOTOR_LEFT_FWD,  0);
  analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_REV, 0);
}

/*
 * Function: turnRight
 * -------------------
 * This function turns Right using the IR sensors.
 */
void Robot::turnRight() {
  state_3 = turningRightOne_s;
  state_4 = inchLeft_s;
  analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
  analogWrite(MOTOR_LEFT_REV,  0);
  analogWrite(MOTOR_RIGHT_FWD, 0);
  analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED);
}

/*
 * Function: turnForward
 * -------------------
 * This function moves forward.
 */
void Robot::turnForward() {
  state_3 = turningForeward_s;
  state_4 = inchLeft_s;
  analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
  analogWrite(MOTOR_LEFT_REV,  0);
  analogWrite(MOTOR_RIGHT_FWD, 0);
  analogWrite(MOTOR_RIGHT_REV, 0);
}

/*
 * Function: turnBackward
 * -------------------
 * This function moves backward.
 */
void Robot::turnBackward() {
  state_3 = turningBackward_s;
  state_4 = noLine_s;
  analogWrite(MOTOR_LEFT_FWD,  0);
  analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED);
  analogWrite(MOTOR_RIGHT_FWD, 0);
  analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED);
}

/*
 * Function: detectedI
 * -------------------
 * This function returns true when centered on a line.
 */
bool Robot::detectedI() {
  if (
                        !frontSensorIR[0]  &&                       !frontSensorIR[1]  &&
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
    !leftSensorIR[1] && !centerSensorIR[0] &&  centerSensorIR[1] && !centerSensorIR[2] && !rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedLeft
 * -------------------
 * This function returns true when reaching a left junction.
 */
bool Robot::detectedLeft() {
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
  if (

    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
    !leftSensorIR[1] && !centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedLeftOff
 * -------------------
 * This function returns true when at the midpoint of a left turn.
 */
bool Robot::detectedLeftOff() {
  if (

     leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
    !leftSensorIR[1] &&                        centerSensorIR[1] &&                       !rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                    rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedRightOff
 * -------------------
 * This function returns true when at the midpoint of a right turn.
 */
bool Robot::detectedRightOff() {
  if (

    !leftSensorIR[0] &&                                                                    rightSensorIR[0] &&
    !leftSensorIR[1] &&                        centerSensorIR[1] &&                       !rightSensorIR[1] &&
     leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedS
 * -------------------
 * This function returns true when reaching the start.
 */
bool Robot::detectedS() {
  if (
                        !frontSensorIR[0]  &&                      !frontSensorIR[1]   &&
    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
     leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
    !leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  ) return true;
  return false;
}

/*
 * Function: detectedPluss
 * -------------------
 * This function returns true when reaching a pluss sign junction.
 */
bool Robot::detectedPluss() {
  if ((
                                                                                           rightSensorIR[0] ||
                                                                                           rightSensorIR[1] ||
                                                                                           rightSensorIR[2]
    ) && (
     leftSensorIR[0] ||
     leftSensorIR[1] ||
     leftSensorIR[2])
  ) return true;
  return false;
}

bool Robot::detectedPlussCenter() {
  bool done = false;
  // if      (
  //    !leftSensorIR[0] &&                                                                   !rightSensorIR[0] &&
  //     leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
  //    !leftSensorIR[2] &&                                                                   !rightSensorIR[2]
  // ) {
  //   done = true;
  //   analogWrite(MOTOR_LEFT_FWD,  0);
  //   analogWrite(MOTOR_LEFT_REV,  0);
  //   analogWrite(MOTOR_RIGHT_FWD, 0);
  //   analogWrite(MOTOR_RIGHT_REV, 0);
  // }
  if      (
      leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1]
  ) {
    done = true;
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
  else if (state_4 == inchLeft_s) {
    if ((rightSensorIR[0] != rightSensorIROLD[0]) || (rightSensorIR[2] != rightSensorIROLD[2])) state_4 = inchRight_s;
    else if (rightSensorIR[0]) {
      analogWrite(MOTOR_LEFT_FWD,  0);
      analogWrite(MOTOR_LEFT_REV,  0);
      analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED);
      analogWrite(MOTOR_RIGHT_REV, 0);
    }
    else if (rightSensorIR[2]) {
      analogWrite(MOTOR_LEFT_FWD,  0);
      analogWrite(MOTOR_LEFT_REV,  0);
      analogWrite(MOTOR_RIGHT_FWD, 0);
      analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED);
    }
  }
  else if (state_4 == inchRight_s) {
    if ((leftSensorIR[0] != leftSensorIROLD[0]) || (leftSensorIR[2] != leftSensorIROLD[2])) state_4 = inchLeft_s;
        else if (leftSensorIR[0]) {
        analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
        analogWrite(MOTOR_LEFT_REV,  0);
        analogWrite(MOTOR_RIGHT_FWD, 0);
        analogWrite(MOTOR_RIGHT_REV, 0);
        }
    else if (leftSensorIR[2]) {
      analogWrite(MOTOR_LEFT_FWD,  0);
      analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED);
      analogWrite(MOTOR_RIGHT_FWD, 0);
      analogWrite(MOTOR_RIGHT_REV, 0);
    }
  }
  return done;
}

/*
 * Function: readSensor_US
 * -------------------
 * This function handles the hardware abstraction of sensing distacne.
 */
float Robot::readSensor_US() {
  digitalWrite(US_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG, LOW);
  return float(pulseIn(US_ECHO, HIGH, 10000))  / 148.0;
}

/*
 * Function: readSensor_IR
 * -------------------
 * This function handles the hardware abstraction of sensing a line.
 */
bool Robot::readSensor_IR(uint8_t pinNum) {
  uint16_t value = analogRead(pinNum);
  Serial.println(value);
  return value <= BLACK_THRESHOLD;
}

/*
 * Function: readSensors_BUMP
 * -------------------
 * This function handles the hardware abstraction of sensing a bump.
 */
bool Robot::readSensors_BUMP(uint8_t pinNum) {
  uint16_t value = digitalRead(pinNum);
  return (!value);
}
