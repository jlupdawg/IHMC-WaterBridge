void setMotors_Serial()                                                    //sets the motors straight from the incoming serial data
{
  leftMotorValue = map(inByte[numberOfInputs-2][1], -100 , 100, -255, 255);      //maps a value given in percent to an analog value
  rightMotorValue = map(inByte[numberOfInputs-1][1], -100 , 100, -255, 255);     //maps a value given in percent to an analog value

  leftMotorValue = constrain(leftMotorValue, -255, 255);
  rightMotorValue = constrain(rightMotorValue, -255, 255);

  analogWrite(leftMotor, leftMotorValue);                            //provides a pwm value to the motors
  analogWrite(rightMotor, rightMotorValue);
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

  Serial.print("Left Motor = "); Serial.println(leftMotorValue);
  Serial.print("Right Motor = "); Serial.println(rightMotorValue);
  delay(100);

  analogWrite(leftMotor, leftMotorValue);
  analogWrite(rightMotor, rightMotorValue);

}

void setMotors_dock()                                                    
{

}

