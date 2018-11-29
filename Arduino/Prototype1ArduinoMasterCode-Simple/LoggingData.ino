void loggingData(String title)
{
  if (split() > timerThreshold)
  {
    Serial.print(title); Serial.println(" Mode");
    Serial.print("Left Motor = "); Serial.println(leftMotorValue);
    Serial.print("Right Motor = "); Serial.println(rightMotorValue);

    if (title == "Controller Mode")
    {
      for (int i = 0; i < (sizeof(manualControllerArray) / sizeof(int)); i++)
      {
        Serial.print("Manual Controller Array "); Serial.print(i); Serial.print(" = "); Serial.println(manualControllerArray[i]);
      }
    }
    
    Serial.println();
    updateTime();
  }

}

void updateTime()
{
  currentMillis = millis();
  previousMillis = currentMillis;
}
int split()
{
  currentMillis = millis();
  return currentMillis - previousMillis;
}

