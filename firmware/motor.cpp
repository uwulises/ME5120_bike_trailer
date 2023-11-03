#include "motor.h"
#include "sensors.h"

int vx_pwm = 0;
int vy_pwm = 0;
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
  // take the direction of the motors from the sign of vx and vy
  int dir_a = (vx >= 0) ? HIGH : LOW;
  int dir_b = (vy >= 0) ? HIGH : LOW;
  // take absolute value of vx and vy
  vx = abs(vx);
  vy = abs(vy);
  Serial.print("vx abs: ");
  Serial.println(vx);
  Serial.print("vy abs: ");
  Serial.println(vy);
  // if vx and vy are smaller than the minimum speed, set them to 0
  if (vx < MIN_SPEED)
  {
    vx = 0;
    vx_pwm = 0;
  }
  if (vy < MIN_SPEED)
  {
    vy = 0;
    vy_pwm = 0;
  }
  // if vx and vy are bigger than the maximum speed, set them to the maximum speed
  if (vx > MAX_SPEED)
  {
    vx = MAX_SPEED;
  }
  if (vy > MAX_SPEED)
  {
    vy = MAX_SPEED;
  }
  // call map only if vx and vy are not 0
  if (vx > 0)
  {
    // map the vx and vy values to the PWM values
    vx_pwm = map(vx, MIN_SPEED, MAX_SPEED, MIN_SPEED_PWM, MAX_SPEED_PWM);
  }
  if (vy > 0)
  {
    vy_pwm = map(vy, MIN_SPEED, MAX_SPEED, MIN_SPEED_PWM, MAX_SPEED_PWM);
  }

  // move the motors
  digitalWrite(DIR_A, dir_a);
  digitalWrite(DIR_B, dir_b);
  analogWrite(PWM_A, vx_pwm);
  analogWrite(PWM_B, vy_pwm);
  Serial.print("vx_pwm: ");
  Serial.println(vx_pwm);
  Serial.print("vy_pwm: ");
  Serial.println(vy_pwm);
}

void motor_stop(void)
{
  // Set the speed of the motors to 0
  analogWrite(PWM_A, 0);
  analogWrite(PWM_B, 0);
}
