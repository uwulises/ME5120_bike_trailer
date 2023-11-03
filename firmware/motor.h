#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define PWM_A 3
#define DIR_A 4

#define PWM_B 5
#define DIR_B 6

#define MIN_SPEED 60
#define MAX_SPEED 140


void motors_setup(void);

void motor_cmd_vel(float vx, float vy);

void motor_stop(void);

#endif