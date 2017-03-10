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
  // if      (state_2 == searching_s   && findBack()) orientBack();
  if      ((state_2 == orienting_s) && orientBack()) findStart();
  else if (state_2 == finding_s     && findStart()) leaveStart();
  else if ((state_2 == leaving_s)   && leaveStart()) {
    LOOP_RATE = BUFFER_CLEAR_TIME_STEP;
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
  // if (detectedPluss()) state_1 = quit_s;
  goal_plus = 1;
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
  goal_plus = 2;
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
    delay(BUFFER_CLEAR_TIME_START);
  }
  analogWrite(MOTOR_FIRE_FWD, DRIVE_SPEED);
  analogWrite(MOTOR_FIRE_REV, 0);
  startTime = millis();
  state_1 = exitBase_s;
  // state_2 = searching_s;
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

  ave_dist = (ave_dist+ distance)/2;

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
  Serial.print(" inches (raw)");
  Serial.print('\n');
  Serial.print(distanceShortest);
  Serial.print(" inches (short)");
  Serial.print('\n');
  Serial.print(distanceShortestNew);
  Serial.print(" inches (new)");
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
  Serial.print(ave_dist);
  Serial.print("(avg distacne)");
  Serial.print('\n');
  Serial.print(ave_min);
  Serial.print("(avg min)");
  Serial.print('\n');
  Serial.print(dist_descending);
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
  //else if ((state_4 == inchLeft_s) && (frontSensorIR[0] || frontSensorIR[1])) {
  else if ((state_4 == inchLeft_s) && (frontSensorIR[0])) {
    state_4 = inchRight_s;
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
  //else if ((state_4 == inchRight_s) && (!frontSensorIR[0] || !frontSensorIR[1])) {
  else if ((state_4 == inchRight_s) && (!frontSensorIR[0])) {
    state_3 = turningForeward_s;
    state_4 = inchLeft_s;
    analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, 0);
  }
}

/*
 * Function: findBack
 * -------------------
 * This function finds the back based on the shorted US distance.
 */
bool Robot::findBack() {
  if (distance <= distanceShortest) distanceShortest = distance;
  if ((millis() - startTime) >= ESCAPE_TIMEOUT) return true;
  return false;
}

/*
 * Function: orientBack
 * -------------------
 * This function aligns to the forward direction.
 */
bool Robot::orientBack() {
  // state_2 = orienting_s;
  // if (distance <= distanceShortestNew) distanceShortestNew = distance;
  // if (distance <= (1.25 * distanceShortest)) {
  //   analogWrite(MOTOR_LEFT_FWD,  0);
  //   analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED);
  //   analogWrite(MOTOR_RIGHT_FWD, 0);
  //   analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED);
  //   leavingTime = millis();
  //   return true;
  // }
  // return false;


  bool done = false;
  state_2 = orienting_s;
  if(ave_min < 0){
    Serial.println("here");
    ave_min = distance;
    ave_dist = distance;
    return false; //Dont set done here, return to set initial pattern.
  }
  if( dist_descending){ //We are getting closer. Continue until we pass the min
  if( ave_min > 1.1*ave_dist){
    ave_min = ave_dist;
    }
    else { //We were close, now we're further. Stop doing it.
      done = true;
    }
  }
  else {
  //We are currently moving away.
  if( ave_min > 1.1*ave_dist){ //We're now closer. Set new min and start the descent.
             ave_min = ave_dist;
       dist_descending = true;        }
   }

  if(done){
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  DRIVE_SPEED);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, DRIVE_SPEED);
    leavingTime = millis();
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
    analogWrite(MOTOR_LEFT_FWD,  DRIVE_SPEED);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, DRIVE_SPEED);
    analogWrite(MOTOR_RIGHT_REV, 0);
    return true;
  }
  return false;
  if (detectedPluss()) done = true;
  return done;
}

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
  if     ( (goal_plus == plus_number) && (state_3 == turningForeward_s) && detectedPluss()) state_3 = ignoringPluss_s;
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
  }
  if((millis() - launchTime) >= LAUNCH_TIMEOUT) {
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
 * More accurate than detectedPluss
 */
bool Robot::detectedPlussStrict() {
  if (
    ((leftSensorIR[0] && rightSensorIR[0]) || (leftSensorIR[1] && rightSensorIR[1])
     || (leftSensorIR[2] && rightSensorIR[2]))) return true;
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


/*

    (
                                                                                           rightSensorIR[0] ||
                                                                                           rightSensorIR[1] ||
                                                                                           rightSensorIR[2]
    ) && (
     leftSensorIR[0] ||
     leftSensorIR[1] ||
     leftSensorIR[2])
  ) return true;
*/
  return false;
}

/*
 * Function: detectedPluss
 * -------------------
 * This function returns true when reaching a pluss sign junction.
 */
bool Robot::detectedPluss() {
  if (
    // ((leftSensorIR[0] && rightSensorIR[0]) || (leftSensorIR[1] && rightSensorIR[1])
    // || (leftSensorIR[2] && rightSensorIR[2]))

    (
                                                                                           rightSensorIR[0] ||
                                                                                           rightSensorIR[1] ||
                                                                                           rightSensorIR[2]
    ) && (
     leftSensorIR[0] ||
     leftSensorIR[1] ||
     leftSensorIR[2])
  ){
    //Within this if you are on a plus. Now check if its the one you want to
    //stop on.
    return true;
    //if( state_1 == attackTower1 ) &&  ()

  }
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
      detectedPlussStrict() ){
    done = true;
    analogWrite(MOTOR_LEFT_FWD,  0);
    analogWrite(MOTOR_LEFT_REV,  0);
    analogWrite(MOTOR_RIGHT_FWD, 0);
    analogWrite(MOTOR_RIGHT_REV, 0);
    return done;
  }
  if (state_4 == inchLeft_s) {
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
  float distance = pulseIn(US_ECHO, HIGH, 10000);
  if ((distance / 148.0) <= 1) return US_THRESHOLD;
  else return distance  / 148.0;
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
