
String inputString = "";
bool stringComplete = false;
int case_command = 0;
const int forward = 1;
const int backward = 2;
const int spin_right = 3;
const int spin_left = 4;
const int lateral_right = 5;
const int lateral_left = 6;
const int diagonal_front_right = 7;
const int diagonal_front_left = 8;
const int diagonal_back_right = 9;
const int diagonal_back_left = 10;

void setup()
{
  // softspeed();
  Serial.begin(9600);
  delay(1000);
  Serial.println("----");
  Serial.println("READY");
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

void serialReadCase()
{
  if (stringComplete)
  {
    //convert the string to integer
    case_command = inputString.toInt();
    switch (case_command)
    {
    case forward:
      FW();
      break;
    case backward:
      BW();
      break;
    case spin_right:
      SR();
      break;
    case spin_left:
      SL();
      break;
    default:
      STOP();
      break;
    }
    
    inputString = "";
    stringComplete = false;
  }
  case_command = 0;
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
      cmd_vel(vx_speed_f, vy_speed_f);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}



// cmd_vel function that takes two floats as arguments of mecanum wheeled robot
void cmd_vel(float vx, float vy)
{
  // Te distance between the center of the robot and the wheel D=0.1m and the radius of the wheel R=0.05m
  float D = 0.145;
  float R = 0.06;
  int w_max = 400;
  // create a v array to store the speed of each wheel
  float w[4];
  w[0] = (vx - vy) / R;
  w[1] = (vx + vy) / R;
  w[2] = (vx + vy) / R;
  w[3] = (vx - vy) / R;
  // transform v from m/s to rpm, to 0-255 pwm given that the maximun speed of the motor is 400rpm
  for (int i = 0; i < 4; i++)
  {
    w[i] = w[i] * 60 / (2 * PI * R);
    w[i] = w[i] * 255 / w_max;
    Serial.print(w[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  // call a function that takes the v array as argument and move the wheels.
  call_motors(w);
}


void loop()
{
  serialReadCase();
}