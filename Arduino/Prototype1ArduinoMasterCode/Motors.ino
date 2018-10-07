void setMotors()
{
int leftMotorValue = map(inByte[0][1], -100 ,100, -255, 255);
int rightMotorValue = map(inByte[1][1], -100 ,100, -255, 255);

analogWrite(leftMotor, leftMotorValue);
analogWrite(rightMotor, rightMotorValue);


}
void setMotors_Controller()
{
int leftMotorValue = map(manualController[1], -100 ,100, -255, 255);
int rightMotorValue = map(manualController[2], -100 ,100, -255, 255);

analogWrite(leftMotor, leftMotorValue);
analogWrite(rightMotor, rightMotorValue);

}
