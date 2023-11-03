#include "motor.h"
#include "sensors.h"

void motors_setup(void)
{
  pinMode(PWM_A, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  // Set the direction of the motors to forward
  digitalWrite(DIR_A, HIGH);
  digitalWrite(DIR_B, HIGH);
}


// cmd_vel function that takes two floats as arguments
void motor_cmd_vel(float vx, float vy)
{
  Serial.println("CMDVEL");
  Serial.print("vx: ");
  Serial.println(vx);
  Serial.print("vy: ");
  Serial.println(vy);
 
}

void motor_stop(void)
{
  // Set the speed of the motors to 0
  analogWrite(PWM_A, 0);
  analogWrite(PWM_B, 0);
}
