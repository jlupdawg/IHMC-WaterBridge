
void setMotors_Serial()                                                    //sets the motors straight from the incoming serial data
{
  leftMotorValue = map(inByte[numberOfInputs - 2][1], -100 , 100, minSpeed, maxSpeed);    //maps a value given in percent to an analog value
  rightMotorValue = map(inByte[numberOfInputs - 1][1], -100 , 100, minSpeed, maxSpeed);   //maps a value given in percent to an analog value


  leftMotorValue = constrain(leftMotorValue, minSpeed, maxSpeed);
  rightMotorValue = constrain(rightMotorValue, minSpeed, maxSpeed);

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
    leftMotorValue = map(leftMotorValue, -255, 0, minSpeed, stopSpeed);
  }
  else if (leftMotorValue > 0)
  {
    leftMotorValue = map(leftMotorValue, 0, 255, stopSpeed, maxSpeed);
  }
  else
  {
    leftMotorValue = stopSpeed;
  }

  if (rightMotorValue < 0)
  {
    rightMotorValue = map(rightMotorValue, -255, 0, minSpeed, stopSpeed);
  }
  else if (rightMotorValue > 0)
  {
    rightMotorValue = map(rightMotorValue, 0, 255, stopSpeed, maxSpeed);
  }
  else
  {
    rightMotorValue = stopSpeed;
  }


  leftMotorValue = constrain(leftMotorValue, minSpeed, maxSpeed);
  rightMotorValue = constrain(rightMotorValue, minSpeed, maxSpeed);


  int adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
  int adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
  leftMotor.writeMicroseconds(adjustedLeftMotorValue);
  rightMotor.writeMicroseconds(adjustedRightMotorValue);
  //Serial.print("Left Motor = "); Serial.println(leftMotorValue);
  //Serial.print("Right Motor = "); Serial.println(rightMotorValue);
  //delay(100);

}


void setMotors_dock(int leftMotorDockVal, int rightMotorDockVal) {
  leftMotorValue = map(leftMotorDockVal, -100 , 100, minSpeed, maxSpeed);    //maps a value given in percent to an analog value
  rightMotorValue = map(rightMotorDockVal, -100 , 100, minSpeed, maxSpeed);   //maps a value given in percent to an analog value


  leftMotorValue = constrain(leftMotorValue, minSpeed, maxSpeed);
  rightMotorValue = constrain(rightMotorValue, minSpeed, maxSpeed);


  int adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
  int adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
  leftMotor.writeMicroseconds(adjustedLeftMotorValue);
  rightMotor.writeMicroseconds(adjustedRightMotorValue);

}
/*
void setMotors_Sonar() {
  incomingRadio();
  if (Direction == 1 || Direction == 2) { //Turn Right

    leftMotorValue = maxSpeed;
    rightMotorValue = minSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    delay(300);

    Serial.println("Right");
    
    leftMotorValue = maxSpeed;
    rightMotorValue = maxSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    delay(100);

    Serial.println("Forward");
    
    leftMotorValue = minSpeed;
    rightMotorValue = minSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    delay(2); //adjust if the boat is drifting forward too much, or backwards too much

    Serial.println("Back");

    leftMotorValue = stopSpeed;
    rightMotorValue = stopSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);

    Serial.println("Stop");
    return;
  }

  //**************************************************************************************************************************8

  else if (Direction == 0) //Turn Left
  {
    leftMotorValue = minSpeed;
    rightMotorValue = maxSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    delay(300);

    Serial.println("Left");

    leftMotorValue = maxSpeed;
    rightMotorValue = maxSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    delay(100);

    Serial.println("Forward");

    leftMotorValue = minSpeed;
    rightMotorValue = minSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    delay(2); //adjust  boat is drifting forward too muchif the

    Serial.println("Back");

    leftMotorValue = stopSpeed;
    rightMotorValue = stopSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);

    Serial.println("Stop");
    return;
  }
}
*/

void setMotors_Sonar() {
  incomingRadio();

  int adjustedLeftMotorValue = 1500;
  int adjustedRightMotorValue = 1500;

  if (Direction == 1 || Direction == 2) { //Turn Right

    leftMotorValue = maxSpeed;
    rightMotorValue = minSpeed;
    adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    leftMotor.writeMicroseconds(adjustedLeftMotorValue);
    rightMotor.writeMicroseconds(adjustedRightMotorValue);
    delay(300);

    leftMotorValue = maxSpeed;
    rightMotorValue = maxSpeed;
    adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    leftMotor.writeMicroseconds(adjustedLeftMotorValue);
    rightMotor.writeMicroseconds(adjustedRightMotorValue);
    delay(100);

    leftMotorValue = minSpeed;
    rightMotorValue = minSpeed;
    adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    leftMotor.writeMicroseconds(adjustedLeftMotorValue);
    rightMotor.writeMicroseconds(adjustedRightMotorValue);
    delay(2); //adjust if the boat is drifting forward too much, or backwards too much

    leftMotorValue = stopSpeed;
    rightMotorValue = stopSpeed;

    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    return;
  }

  //**************************************************************************************************************************8

  else if (Direction == 0) //Turn Left
  {
    leftMotorValue = minSpeed;
    rightMotorValue = maxSpeed;
    adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    leftMotor.writeMicroseconds(adjustedLeftMotorValue);
    rightMotor.writeMicroseconds(adjustedRightMotorValue);
    delay(300);

    leftMotorValue = maxSpeed;
    rightMotorValue = maxSpeed;
    adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    leftMotor.writeMicroseconds(adjustedLeftMotorValue);
    rightMotor.writeMicroseconds(adjustedRightMotorValue);
    delay(100);

    leftMotorValue = minSpeed;
    rightMotorValue = minSpeed;
    adjustedLeftMotorValue = map(leftMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    adjustedRightMotorValue = map(rightMotorValue, minSpeed, maxSpeed, maxSpeed, minSpeed);
    leftMotor.writeMicroseconds(adjustedLeftMotorValue);
    rightMotor.writeMicroseconds(adjustedRightMotorValue);
    delay(2); //adjust if the boat is drifting forward too much

    leftMotorValue = stopSpeed;
    rightMotorValue = stopSpeed;
    leftMotor.writeMicroseconds(leftMotorValue);
    rightMotor.writeMicroseconds(rightMotorValue);
    return;
  }
}
