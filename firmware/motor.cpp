#include "motor.h"
#include "sensors.h"

int vx_pwm = 0;
int vy_pwm = 0;
float vx_abs = 0.0;
float vy_abs = 0.0;
float max_speed = MAX_SPEED;
float min_speed = MIN_SPEED;
bool dir_a = HIGH;
bool dir_b = HIGH;
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
  dir_a = (vx >= 0) ? HIGH : LOW;
  dir_b = (vy >= 0) ? HIGH : LOW;
  // take absolute value of vx and vy
  vx_abs = abs(vx);
  vy_abs = abs(vy);
  //check if the speed is out of range
  if (vx_abs > max_speed)
  {
    vx_abs = max_speed;
  }
  if (vy_abs > max_speed)
  {
    vy_abs = max_speed;
  }
  //map the speed to the pwm range
  if (vx_abs >= min_speed && vx_abs <= max_speed)
  {
    vx_pwm = (int)(MAX_SPEED_PWM-MIN_SPEED_PWM)/(max_speed-min_speed)*(vx_abs-min_speed)+MIN_SPEED_PWM;
  }
  if (vy_abs >= min_speed && vy_abs <= max_speed)
  {
    vy_pwm = (int)(MAX_SPEED_PWM-MIN_SPEED_PWM)/(max_speed-min_speed)*(vy_abs-min_speed)+MIN_SPEED_PWM;
  }
  
  // move the motors
  digitalWrite(DIR_A, dir_a);
  digitalWrite(DIR_B, dir_b);
  // Set the speed of the motors using a ramp function from the minimum speed to the value of pwm calculated above
  for (int i = MIN_SPEED_PWM; i <= vx_pwm; i=i*1.1)
  {
    analogWrite(PWM_A, i);
    delay(10);
  }
  for (int i = MIN_SPEED_PWM; i <= vy_pwm; i=i*1.1)
  {
    analogWrite(PWM_B, i);
    delay(10);
  }
  
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
