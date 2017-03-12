/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Robot.cpp
  --------------------------
  Implementation of Robot.h.
*/

#include "Robot.h"

/**********************************  SETUP  ***********************************/
/*
 * Function: init
 * -------------------
 * This function initializes the main robot hardware.
 */
void Robot::init() {
  Serial.begin(BAUD_RATE);
  setPinModes();
  stepper.setMaxSpeed(LOADER_SPEED);
  stepper.setSpeed(LOADER_SPEED);
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
  updateSensors();
  printState();
  checkTimer();
  center();
}

/*
 * Function: sleep
 * -------------------
 * This function clears the serial buffer so that we do not get flooded.
 */
void Robot::sleep() {
  delay(LOOP_RATE);
}

/*
 * Function: exitBase
 * -------------------
 * This function handles the algorythmic complexity of exiting the base.
 */
void Robot::exitBase() {
  if      ((state_2 == orienting_s) && orientBack()) findStart();
  else if ((state_2  == finding_s)  && findStart()) leaveStart();
  else if ((state_2 == leaving_s)   && leaveStart()) {
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
  goal_plus = 2;
  if (attackTower()) {
    hammer(true);
    hammer(true);
    state_1 = attackTower2_s;
    state_2 = approaching_s;
    turnForward();
  }
}

/*
 * Function: attackTower2
 * -------------------
 * This function handles the algorythmic complexity of attacking a the second tower.
 */
void Robot::attackTower2() {
  goal_plus = 3;
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
  goal_plus = 4;
  if     ((goal_plus == plus_number) && (state_3 == turningRightOne_s) && detectedPluss()) {
    goal_plus = 4;
    turnForward();
  }
  else if ((goal_plus == plus_number) && (state_3 == turningForeward_s) && detectedPluss()) {
    state_3 =   byebye_s;
    analogWrite(MOTOR_LEFT_FWD,   255);
    analogWrite(MOTOR_LEFT_REV,   0);
    analogWrite(MOTOR_RIGHT_FWD,  255);
    analogWrite(MOTOR_RIGHT_REV,  0);
    quitTime = millis();
  }
  else if ((state_3 == byebye_s) && (millis() - quitTime) >= QUIT_TIMEOUT) state_1 = quit_s;
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
  Serial.print("I quit...");
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
    delay(BUFFER_CLEAR_TIME_NORM);
  }
  digitalWrite(MOTOR_FIRE_FWD, HIGH);
  digitalWrite(MOTOR_FIRE_REV, LOW);
  startTime = millis();
  state_1 = exitBase_s;
  state_2 = orienting_s;
  turnLeft();
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

  frontSensorIR[0]    = readSensor_IR(IR_IN_01, &raw01);
  frontSensorIR[1]    = readSensor_IR(IR_IN_02, &raw02);

  leftSensorIR[0]     = readSensor_IR(IR_IN_03, &raw03);
  leftSensorIR[1]     = readSensor_IR(IR_IN_04, &raw04);
  leftSensorIR[2]     = readSensor_IR(IR_IN_05, &raw05);

  rightSensorIR[0]    = readSensor_IR(IR_IN_06, &raw06);
  rightSensorIR[1]    = readSensor_IR(IR_IN_07, &raw07);
  rightSensorIR[2]    = readSensor_IR(IR_IN_08, &raw08);

  centerSensorIR[0]   = readSensor_IR(IR_IN_09, &raw09);
  centerSensorIR[1]   = readSensor_IR(IR_IN_10, &raw10);
  centerSensorIR[2]   = readSensor_IR(IR_IN_11, &raw11);

  avgDistOld          = (alpha * avgDist) + (1.0 - alpha) * avgDistOld;
  avgDist             = (beta * distance) + (1.0 - beta) * avgDist;

  plus_prev = plus_curr;
  plus_curr = detectedPluss();
  if((state_1 != exitBase_s) && (!plus_prev && plus_curr)){
    if( (micros()-plus_time)> plus_cooldown){
      plus_number++;
      plus_time = micros();
    }
  }
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

  Serial.print("plus_number: ");
  Serial.println(plus_number);
  Serial.print('\n');

  Serial.print(avgDist);
  Serial.print("(avg distacne)");
  Serial.print('\n');
  Serial.print(avgDistOld);
  Serial.print("(avg distacne old)");
  Serial.print('\n');
  Serial.print(avgMin);
  Serial.print("(avg min)");
  Serial.print('\n');
  Serial.print(distDescending);
  Serial.print("(dist_descending)");
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
 * Function: center
 * -------------------
 * This function self corrects to stay on line.
 */
void Robot::center() {
  if      ((state_3 != turningForeward_s) && (state_3 != ignoringPluss_s)) return;
  else if ((state_4 == inchLeft_s) && (frontSensorIR[0] || !frontSensorIR[1])) {
  // else if ((state_4 == inchLeft_s) && (frontSensorIR[0])) { TODO?????????????
    state_4 = inchRight_s;
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED_RIGHT);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
  else if ((state_4 == inchRight_s) && (!frontSensorIR[0] || frontSensorIR[1])) {
  // else if ((state_4 == inchRight_s) && (!frontSensorIR[0])) { TODO???????????
    state_3 = turningForeward_s;
    state_4 = inchLeft_s;
    analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED_LEFT);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
}

/*
 * Function: orientBack
 * -------------------
 * This function aligns to the forward direction.
 */
bool Robot::orientBack() {
  bool done = false;
  state_2 = orienting_s;
  if     (avgMin < 0){
    avgMin     = distance;
    avgDist    = distance;
    avgDistOld = distance;
  }
  else if(distDescending){
    if ((1.1 * avgDist) < avgMin) avgMin = avgDist;
    else if (avgDist < minDist){
      done = true;
      analogWrite(MOTOR_LEFT_FWD,  0);
      analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED_LEFT);
      analogWrite(MOTOR_RIGHT_FWD, 0);
      analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED_RIGHT);
      leavingTime = millis();
    }
  }
  else if(avgDistOld > (1.1*avgDist)){
    avgMin = avgDist;
    distDescending = true;
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
  state_2 = finding_s;
  if ((millis() - leavingTime) >= ESCAPE_TIMEOUT) {
    state_3 = turningForeward_s;
    analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED_LEFT);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED_RIGHT);
    analogWrite(MOTOR_RIGHT_REV, 0);
    done = true;
  }
  return done;
}

/*
 * Function: leaveStart
 * -------------------
 * This function leaves the start zone.
 */
bool Robot::leaveStart() {
  bool done = false;
  state_2 = leaving_s;
  if (detectedPluss()) done = true;
  return done;
}

/*
 * Function: attackTower
 * -------------------
 * This function handles the algorythmic complexity of attacking a single tower.
 */
bool Robot::attackTower() {
  bool done = false;
  if     ((goal_plus == plus_number) && (state_3 == turningForeward_s) && detectedPluss()) state_3 = ignoringPluss_s;
  else if (state_3 == ignoringPluss_s && detectedPluss()) {
    state_3 = centeringPluss_s;
    plussTIme = millis();
  }
  else if (state_3 == centeringPluss_s  && (detectedPlussCenter() || (millis() - plussTIme >= PLUSS_TIMEOUT))) {
    hammer(true);
    state_2 = loading_s;
    state_3 = launchingEggs01_s;
  }
  else if (state_3 == launchingEggs01_s && launchEgg()) {
    state_3 = launchingEggsLoad01_s;
    loadTime = millis();
  }
  else if ((state_3 == launchingEggsLoad01_s) && ((millis() - loadTime) >= LOAD_TIMEOUT)) {
    hammer(false);
    state_2 = loading_s;
    state_3 = launchingEggs02_s;
  }
  else if (state_3 == launchingEggs02_s && launchEgg()) {
    state_3 = launchingEggsLoad02_s;
    loadTime = millis();
  }
  else if ((state_3 == launchingEggsLoad02_s) && ((millis() - loadTime) >= LOAD_TIMEOUT)) {
    hammer(false);
    state_2 = loading_s;
    state_3 = launchingEggs03_s;
  }
  else if (state_3 == launchingEggs03_s && launchEgg()) {
    state_3 = launchingEggsLoad03_s;
    loadTime = millis();
  }
  else if ((state_3 == launchingEggsLoad03_s) && ((millis() - loadTime) >= LOAD_TIMEOUT)) {
    hammer(false);
    state_2 = loading_s;
    state_3 = launchingEggs04_s;
  }
  else if (state_3 == launchingEggs04_s && launchEgg()) {
    state_3 = launchingEggsLoad04_s;
    loadTime = millis();
  }
  else if ((state_3 == launchingEggsLoad04_s) && ((millis() - loadTime) >= LOAD_TIMEOUT)) {
    hammer(false);
    state_2 = loading_s;
    state_3 = launchingEggs05_s;
  }
  else if (state_3 == launchingEggs05_s && launchEgg()) {
    state_3 = launchingEggsLoad05_s;
    loadTime = millis();
  }
  else if ((state_3 == launchingEggsLoad05_s) && ((millis() - loadTime) >= LOAD_TIMEOUT)) {
    hammer(false);
    state_2 = loading_s;
    state_3 = launchingEggs06_s;
  }
  else if (state_3 == launchingEggs06_s && launchEgg()) {
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
    LOOP_RATE = BUFFER_CLEAR_TIME_STEP;
    stepper.move(LOADER_STEP);
    state_2 = attacking_s;
  }
  stepper.runSpeedToPosition();
  if(stepper.distanceToGo() == 0) {
    LOOP_RATE = BUFFER_CLEAR_TIME_NORM;
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
  analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED_LEFT);
  analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED_RIGHT);
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
  analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED_LEFT);
  analogWrite(MOTOR_LEFT_REV,  0);
  analogWrite(MOTOR_RIGHT_FWD, 0);
  analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED_RIGHT);
}

/*
 * Function: turnForward
 * -------------------
 * This function moves forward.
 */
void Robot::turnForward() {
  state_3 = turningForeward_s;
  state_4 = inchLeft_s;
  analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED_LEFT);
  analogWrite(MOTOR_LEFT_REV,  0);
  analogWrite(MOTOR_RIGHT_FWD, 0);
  analogWrite(MOTOR_RIGHT_REV, 0);
}


/*
 * Function: detectedPluss
 * -------------------
 * This function returns true when reaching a pluss sign junction.
 */
bool Robot::detectedPluss() {
  if (
    (
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
  if      (
      !frontSensorIR[0] &&                                                                  !frontSensorIR[1] &&
      leftSensorIR[1] &&  centerSensorIR[0] &&  centerSensorIR[1] &&  centerSensorIR[2] &&  rightSensorIR[1] &&
      !leftSensorIR[2] &&                                                                  !rightSensorIR[2]
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
      analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED_RIGHT * 0.9);
      analogWrite(MOTOR_RIGHT_REV, 0);
    }
    else if (rightSensorIR[2]) {
      analogWrite(MOTOR_LEFT_FWD,  0);
      analogWrite(MOTOR_LEFT_REV,  0);
      analogWrite(MOTOR_RIGHT_FWD, 0);
      analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED_RIGHT * 0.9);
    }
  }
  else if (state_4 == inchRight_s) {
    if ((leftSensorIR[0] != leftSensorIROLD[0]) || (leftSensorIR[2] != leftSensorIROLD[2])) state_4 = inchLeft_s;
        else if (leftSensorIR[0]) {
        analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED_LEFT * 0.9);
        analogWrite(MOTOR_LEFT_REV,  0);
        analogWrite(MOTOR_RIGHT_FWD, 0);
        analogWrite(MOTOR_RIGHT_REV, 0);
        }
    else if (leftSensorIR[2]) {
      analogWrite(MOTOR_LEFT_FWD,  0);
      analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED_LEFT * 0.9);
      analogWrite(MOTOR_RIGHT_FWD, 0);
      analogWrite(MOTOR_RIGHT_REV, 0);
    }
  }
  return done;
}

/*
 * Function: hammer
 * -------------------
 * This function is because we suck.
 */
void Robot::hammer(bool left) {
  if (left) {
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  255);
    analogWrite(MOTOR_RIGHT_FWD, 255);
    analogWrite(MOTOR_RIGHT_REV, 0);
    delay(SWEEP_TIMEOUT);
  }
  else {
    analogWrite(MOTOR_LEFT_FWD,  255);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, 255);
    delay(SWEEP_TIMEOUT);
  }
  analogWrite(MOTOR_LEFT_FWD,  0);
  analogWrite(MOTOR_LEFT_REV,  0);
  analogWrite(MOTOR_RIGHT_FWD, 0);
  analogWrite(MOTOR_RIGHT_REV, 0);
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
  float distance = pulseIn(US_ECHO, HIGH, 10000);
  if ((distance / 148.0) <= 1) return US_THRESHOLD;
  else return distance  / 148.0;
}

/*
 * Function: readSensor_IR
 * -------------------
 * This function handles the hardware abstraction of sensing a line.
 */
bool Robot::readSensor_IR(uint8_t pinNum, float* val) {
  uint16_t value = analogRead(pinNum);
  Serial.println(value);
  float temp = *val;
  temp = (beta * value) + (1.0 - beta) * temp;
  *val = temp;
  return temp <= BLACK_THRESHOLD;
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
