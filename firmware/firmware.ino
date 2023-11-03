#include "motor.h"
#include "sensors.h"
String inputString = "";
bool stringComplete = false;

void setup()
{
  // softspeed();
  Serial.begin(115200);
  delay(1000);
  Serial.println("----");
  Serial.println("READY BIKE TRAILER");
  Serial.println("----");
  delay(200);
}

void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

void serialReading()
{
  if (stringComplete)
  {
    // take the 6 first characters of the string
    // and compare it with "CMDVEL"
    if (inputString.substring(0, 6) == "CMDVEL")
    {
      // take and split the next 6 characters of the string
      int vx_speed = inputString.substring(6, 9).toInt();
      int vy_speed = inputString.substring(9, 12).toInt();
      // divide by 10.0 and convert to float to get the decimal point (m/s)
      float vx_speed_f = vx_speed / 10.0;
      float vy_speed_f = vy_speed / 10.0;
      // call cmd vel function
      motor_cmd_vel(vx_speed_f, vy_speed_f);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void loop()
{
  serialReading();
}