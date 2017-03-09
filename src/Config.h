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
static const uint16_t  BLACK_THRESHOLD         =               400;
static const uint16_t  US_THRESHOLD            =              2000;
static const uint16_t  DRIVE_SPEED             =               200;
static const uint16_t  LAUNCH_SPEED            =               750;
static const uint16_t  LOADER_SPEED            =               255;
static const uint32_t  RUNTIME_TIMEOUT         =            130000;
static const uint32_t  ESCAPE_TIMEOUT          =              4000;
static const uint32_t  LAUNCH_TIMEOUT          =              4000;
static const uint32_t  BUFFER_CLEAR_TIME       =                15;

static const uint8_t   MOTOR_STEP_STEPS        =               200;
static const uint8_t   MOTOR_STEP_MODE0        =                10;
static const uint8_t   MOTOR_STEP_MODE1        =                11;
static const uint8_t   MOTOR_STEP_MODE2        =                12;

/*****************************  TEENSY PIN OUTS  ******************************/
static const uint8_t   START_PIN               =                 1;

static const uint8_t   BUMPER_LEFT             =                 7;
static const uint8_t   BUMPER_RIGHT            =                 8;
static const uint8_t   US_TRIG                 =                 9;
static const uint8_t   US_ECHO                 =                10;

static const uint8_t   IR_IN_01                =               A14;
static const uint8_t   IR_IN_02                =                A9;
static const uint8_t   IR_IN_03                =                A8;
static const uint8_t   IR_IN_04                =                A7;
static const uint8_t   IR_IN_05                =                A6;
static const uint8_t   IR_IN_06                =                A3;
static const uint8_t   IR_IN_07                =                A4;
static const uint8_t   IR_IN_08                =                A5;
static const uint8_t   IR_IN_09                =                A0;
static const uint8_t   IR_IN_10                =                A1;
static const uint8_t   IR_IN_11                =                A2;

static const uint8_t   MOTOR_LEFT_FWD          =                4;
static const uint8_t   MOTOR_LEFT_REV          =                3;
static const uint8_t   MOTOR_RIGHT_FWD         =                6;
static const uint8_t   MOTOR_RIGHT_REV         =                5;
static const uint8_t   MOTOR_FIRE_FWD          =               69;
static const uint8_t   MOTOR_FIRE_REV          =               69;
static const uint8_t   MOTOR_STEP_DIR          =               11;
static const uint8_t   MOTOR_STEP_STEP         =               12;

#endif
