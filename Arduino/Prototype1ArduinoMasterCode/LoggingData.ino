void loggingData(String title)
{
  if (split() > timerThreshold)
  {
    Serial.print(title); Serial.println(" Mode");
    Serial.print("Left Motor = "); Serial.println(leftMotorValue);
    Serial.print("Right Motor = "); Serial.println(rightMotorValue);

      Serial.print("f1:");
      Serial.print(" - ");
      Serial.print(f1);
      Serial.print(" - ");
      Serial.print("b1");
      Serial.print(" - ");
      Serial.println(b1);
    
    if (title == "Controller Mode")
    {
      for (int i = 0; i < (sizeof(manualControllerArray) / sizeof(int)); i++)
      {
        Serial.print("Manual Controller Array "); Serial.print(i); Serial.print(" = "); Serial.println(manualControllerArray[i]);
      }
    }

    if (title == "Docking Mode")
    {
      for (int i = 0; i < (sizeof(dockingArray) / sizeof(int)); i++)
      {
        Serial.print("Docking Array "); Serial.print(i); Serial.print(" = "); Serial.println(dockingArray[i]);
      }
    }
    if (title == "Sonar")
    {
      Serial.print("f1:");
      Serial.print(" - ");
      Serial.print(f1);
      Serial.print(" - ");
      Serial.print("b1");
      Serial.print(b1);
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
