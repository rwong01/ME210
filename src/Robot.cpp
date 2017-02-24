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
  //start timer
  pinMode(START_PIN,      INPUT);
  pinMode(MULTIPLEXER_CS, INPUT);

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
  //turn on flywheel
  state = exitBase_s;
}

/********************************  FUNCTIONS  *********************************/
/*
 * Function: getState
 * -------------------
 * This function returns the current state.
 */
state_t Robot::getState() {
  checkTimer();
  return state;
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
  state = returnToBase_s;
}

/*
 * Function: returnToBase
 * -------------------
 * This function handles the algorythmic complexity of returning to the base.
 */
void Robot::returnToBase() {
  moveBackward();
  moveBackward();
  moveBackward();
  state = reloadEggs_s;
}

/*
 * Function: reloadEggs
 * -------------------
 * This function handles the algorythmic complexity of getting more eggs.
 */
void Robot::reloadEggs() {
  //start timer
  state = attackTower1_s;
}

/*
 * Function: quit
 * -------------------
 * This function handles the end of game shutdown.
 */
void Robot::quit() {
  //turn off fire
  //turn off load
  //turn off motors
}

/*********************************  HELPERS  **********************************/
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
  moveForward();
  turnLeft();
  moveForward();
  launchEgg();
  moveBackward();
  turnRight();
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
 * Function: moveForward
 * -------------------
 * This function moves forward.
 */
void Robot::moveForward() {

}

/*
 * Function: moveBackward
 * -------------------
 * This function moves backward.
 */
void Robot::moveBackward() {

}

/*
 * Function: launchEgg
 * -------------------
 * This function launches eggs.
 */
void Robot::launchEgg() {
  //drop 6 balls
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
 * Function: checkTimer
 * -------------------
 * This function checks if the timer has expired.
 */
void Robot::checkTimer() {
  if(millis() >= RUNTIME_TIMEOUT) state = quit_s;
}
