
void writeLCD_Motors()
{

  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("RMotor = "); 
  lcd.print(rightMotorValue);


  lcd.setCursor(0, 1);
  lcd.print("LMotor = "); 
  lcd.print(leftMotorValue);

}

void writeLCD(int a, int b)
{
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DataA = "); 
  lcd.print(a);

  lcd.setCursor(0, 1);
  lcd.print("DataB = "); 
  lcd.print(b);
}


void writeLCDCounter()
{
  //delay(500);
  counter++;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Counter = "); 
  lcd.print(counter);

}



