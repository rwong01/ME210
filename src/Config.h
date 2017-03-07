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
static const uint16_t  BLACK_THRESHOLD         =    600;
static const uint16_t  DRIVE_SPEED             =    200;
static const uint16_t  LAUNCH_SPEED            =   1023;
static const uint16_t  LOADER_SPEED            =    255;
static const uint32_t  RUNTIME_TIMEOUT         = 130000;
static const uint32_t  ESCAPE_TIMEOUT          =   2000;
static const uint32_t  LAUNCH_TIMEOUT          =  10000;
static const uint32_t  BUFFER_CLEAR_TIME       =     50;

static const uint8_t   MOTOR_STEP_STEPS        =    200;
static const uint8_t   MOTOR_STEP_MODE0        =     10;
static const uint8_t   MOTOR_STEP_MODE1        =     11;
static const uint8_t   MOTOR_STEP_MODE2        =     12;

/*****************************  TEENSY PIN OUTS  ******************************/
static const uint8_t   START_PIN               =     23;
static const uint8_t   FAULT_LED               =     22;
static const uint8_t   MULTIPLEXER_CS          =     10;

static const uint8_t   BUMPER_LEFT             =      9;
static const uint8_t   BUMPER_RIGHT            =      8;

static const uint8_t   MOTOR_LEFT_FWD          =      5;
static const uint8_t   MOTOR_LEFT_REV          =      6;
static const uint8_t   MOTOR_RIGHT_FWD         =      3;
static const uint8_t   MOTOR_RIGHT_REV         =      4;
static const uint8_t   MOTOR_FIRE_FWD          =     69;
static const uint8_t   MOTOR_FIRE_REV          =     69;
static const uint8_t   MOTOR_STEP_DIR          =      8;
static const uint8_t   MOTOR_STEP_STEP         =      9;

#endif
