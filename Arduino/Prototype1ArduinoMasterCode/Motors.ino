void setMotors()
{
int leftMotorValue = map(inByte[0][1], -100 ,100, -255, 255);
int rightMotorValue = map(inByte[1][1], -100 ,100, -255, 255);

analogWrite(leftMotor, leftMotorValue);
analogWrite(rightMotor, rightMotorValue);


}
void setMotors_Controller()
{
int leftMotorValue = 0;
int rightMotorValue = 0;
int xAxis = map(manualControllerArray[2], 0 ,685, -128, 128);
int yAxis = map(manualControllerArray[3], 0 ,685, -128, 128);

if(yAxis > 10 || xAxis > 10)
{
  leftMotorValue = yAxis+xAxis;
  rightMotorValue = yAxis-xAxis;
}
else if(yAxis < -10 || xAxis < -10)
{
  leftMotorValue = yAxis-xAxis;
  rightMotorValue = yAxis+xAxis;  
}
else
{
  leftMotorValue = 0;
  rightMotorValue = 0;
}

Serial.print("Left Motor = "); Serial.println(leftMotorValue);
Serial.print("Right Motor = "); Serial.println(rightMotorValue);
delay(500);
analogWrite(leftMotor, leftMotorValue);
analogWrite(rightMotor, rightMotorValue);

}
