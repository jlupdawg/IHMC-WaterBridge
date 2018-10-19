void setMotors_Serial()                                                    //sets the motors straight from the incoming serial data
{
  leftMotorValue = map(inByte[numberOfInputs - 2][1], -100 , 100, -255, 255);    //maps a value given in percent to an analog value
  rightMotorValue = map(inByte[numberOfInputs - 1][1], -100 , 100, -255, 255);   //maps a value given in percent to an analog value

  if (leftMotorValue < 0)
  {
    leftMotorValue = map(leftMotorValue, -255, 0, 1100, 1500);
  }
  else if (leftMotorValue > 0)
  {
    leftMotorValue = map(leftMotorValue, 0, 255, 1500, 1900);
  }
  else
  {
    leftMotorValue = 1500;
  }

  if (rightMotorValue < 0)
  {
    rightMotorValue = map(rightMotorValue, -255, 0, 1100, 1500);
  }
  else if (rightMotorValue > 0)
  {
    rightMotorValue = map(rightMotorValue, 0, 255, 1500, 1900);
  }
  else
  {
    rightMotorValue = 1500;
  }

  
  leftMotorValue = constrain(leftMotorValue, 1100, 1900);
  rightMotorValue = constrain(rightMotorValue, 1100, 1900);

  leftMotor.writeMicroseconds(leftMotorValue);
  rightMotor.writeMicroseconds(rightMotorValue);
}


void setMotors_Controller()
{
  int threshold = 20;                                              //limit value for minimum controls to make sure that 0 = 0 without interference
  int xAxis = map(manualControllerArray[2], 0 , 1028, -255, 255);    //maps incoming  analog data from controller to a value between -128 and 128. The ICs may need to be changed based on power supply and consumption
  int yAxis = map(manualControllerArray[3], 0 , 1028, -255, 255);

  if (yAxis > threshold || xAxis > threshold)                       //if the value is not in the threshold and is positive
  {
    leftMotorValue = yAxis + xAxis;
    rightMotorValue = yAxis - xAxis;
  }
  else if (yAxis < -threshold || xAxis < -threshold)                //if the value is not in the threshold and is negative
  {
    leftMotorValue = yAxis + xAxis;
    rightMotorValue = yAxis - xAxis;
  }
  else
  {
    leftMotorValue = 0;
    rightMotorValue = 0;
  }



  if (leftMotorValue < 0)
  {
    leftMotorValue = map(leftMotorValue, -255, 0, 1100, 1500);
  }
  else if (leftMotorValue > 0)
  {
    leftMotorValue = map(leftMotorValue, 0, 255, 1500, 1900);
  }
  else
  {
    leftMotorValue = 1500;
  }

  if (rightMotorValue < 0)
  {
    rightMotorValue = map(rightMotorValue, -255, 0, 1100, 1500);
  }
  else if (rightMotorValue > 0)
  {
    rightMotorValue = map(rightMotorValue, 0, 255, 1500, 1900);
  }
  else
  {
    rightMotorValue = 1500;
  }
  leftMotorValue = constrain(leftMotorValue, 1100, 1900);
  rightMotorValue = constrain(rightMotorValue, 1100, 1900);

  leftMotor.writeMicroseconds(leftMotorValue);
  rightMotor.writeMicroseconds(rightMotorValue);

  //Serial.print("Left Motor = "); Serial.println(leftMotorValue);
  //Serial.print("Right Motor = "); Serial.println(rightMotorValue);
  //delay(100);

}


void setMotors_dock()
{

}

