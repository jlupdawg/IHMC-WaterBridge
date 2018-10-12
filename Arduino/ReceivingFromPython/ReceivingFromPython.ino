int LED = A10;
//int number;
String number;

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){

  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop(){
  if(Serial.available())
  {
    lcd.clear();
    //number = Serial.parseInt();
    number = Serial.readStringUntil('\n');
    Serial.print(number);
    Serial.println();
    //constrain(number, 0, 255);
    //analogWrite(LED,number);
    writeLCD();
  }
  
}

void writeLCD()
{
    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(number);
}
