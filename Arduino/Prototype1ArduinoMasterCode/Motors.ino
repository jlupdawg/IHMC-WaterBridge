void setMotors_Serial()                                                    //sets the motors straight from the incoming serial data
{
  int leftMotorValue = map(inByte[1][1], -100 , 100, -255, 255);      //maps a value given in percent to an analog value
  int rightMotorValue = map(inByte[2][1], -100 , 100, -255, 255);     //maps a value given in percent to an analog value

  analogWrite(leftMotor, leftMotorValue);                            //provides a pwm value to the motors
  analogWrite(rightMotor, rightMotorValue);
}


void setMotors_Controller()
{
  int leftMotorValue = 0;
  int rightMotorValue = 0;
  int threshold = 10;                                              //limit value for minimum controls to make sure that 0 = 0 without interference
  int xAxis = map(manualControllerArray[2], 0 , 685, -128, 128);    //maps incoming  analog data from controller to a value between -128 and 128. The ICs may need to be changed based on power supply and consumption
  int yAxis = map(manualControllerArray[3], 0 , 685, -128, 128);

  if (yAxis > threshold || xAxis > threshold)                       //if the value is not in the threshold and is positive
  {
    leftMotorValue = yAxis + xAxis;
    rightMotorValue = yAxis - xAxis;
  }
  else if (yAxis < -threshold || xAxis < -threshold)                //if the value is not in the threshold and is negative
  {
    leftMotorValue = yAxis - xAxis;
    rightMotorValue = yAxis + xAxis;
  }
  else
  {
    leftMotorValue = 0;
    rightMotorValue = 0;
  }

  //Serial.print("Left Motor = "); Serial.println(leftMotorValue);
  //Serial.print("Right Motor = "); Serial.println(rightMotorValue);
  //delay(500);
  
  analogWrite(leftMotor, leftMotorValue);
  analogWrite(rightMotor, rightMotorValue);

}

void setMotors_dock()                                                    
{

}
