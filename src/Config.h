/*
  ME210 | March 2017
  Davy Ragland | dragland@stanford.edu
  Rebecca Wong | rwong01@stanford.edu
  Sasha Maldonado | amaldona@stanford.edu
  Jake Hillard | jhillard@stanford.edu

  File: Config.h
  --------------------------
  Global constants specific to robot.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <stdint.h>

/****************************  EDITABLE CONSTANTS  ****************************/
static const uint16_t  BLACK_THRESHOLD         =                            450;
static const uint16_t  US_THRESHOLD            =                           2000;

static const uint16_t  DRIVE_SPEED_LEFT        =                            200;
static const uint16_t  DRIVE_SPEED_RIGHT       =        0.98 * DRIVE_SPEED_LEFT;

static const uint16_t  LOADER_SPEED_01         =                            280;
static const uint16_t  LOADER_SPEED_02         =                            280;
static const uint16_t  LOADER_SPEED_03         =                            280;
static const uint16_t  LOADER_SPEED_04         =                            280;
static const uint16_t  LOADER_SPEED_05         =                            280;
static const uint16_t  LOADER_SPEED_06         =                            280;
static const uint16_t  LOADER_SPEED_07         =                            280;
static const uint16_t  LOADER_SPEED_08         =                            280;
static const uint16_t  LOADER_SPEED_09         =                            280;
static const uint16_t  LOADER_SPEED_10         =                            280;
static const uint16_t  LOADER_SPEED_11         =                            280;
static const uint16_t  LOADER_SPEED_12         =                            280;

static const uint32_t  RUNTIME_TIMEOUT         =                         120000;
static const uint32_t  ESCAPE_TIMEOUT          =                           2000;
static const uint32_t  LAUNCH_TIMEOUT          =                            420;
static const uint32_t  LOAD_TIMEOUT            =                           3000;

static const uint32_t  BUFFER_CLEAR_TIME_NORM  =                             20;
static const uint32_t  BUFFER_CLEAR_TIME_STEP  =                              1;

/*****************************  TEENSY PIN OUTS  ******************************/
static const uint8_t   START_PIN               =                              1;

static const uint8_t   BUMPER_LEFT             =                              7;
static const uint8_t   BUMPER_RIGHT            =                              8;

static const uint8_t   US_TRIG                 =                              9;
static const uint8_t   US_ECHO                 =                             10;

static const uint8_t   IR_IN_01                =                            A14;
static const uint8_t   IR_IN_02                =                             A9;
static const uint8_t   IR_IN_03                =                             A8;
static const uint8_t   IR_IN_04                =                             A7;
static const uint8_t   IR_IN_05                =                             A6;
static const uint8_t   IR_IN_06                =                             A3;
static const uint8_t   IR_IN_07                =                             A4;
static const uint8_t   IR_IN_08                =                             A5;
static const uint8_t   IR_IN_09                =                             A0;
static const uint8_t   IR_IN_10                =                             A1;
static const uint8_t   IR_IN_11                =                             A2;

static const uint8_t   MOTOR_LEFT_FWD          =                             4;
static const uint8_t   MOTOR_LEFT_REV          =                             3;
static const uint8_t   MOTOR_RIGHT_FWD         =                             6;
static const uint8_t   MOTOR_RIGHT_REV         =                             5;
static const uint8_t   MOTOR_FIRE_FWD          =                             0;
static const uint8_t   MOTOR_FIRE_REV          =                            69;
static const uint8_t   MOTOR_STEP_DIR          =                            11;
static const uint8_t   MOTOR_STEP_STEP         =                            12;

#endif
