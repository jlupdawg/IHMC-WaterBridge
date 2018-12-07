void loggingData(String title)
{
  if (split() > timerThreshold)
  {
    Serial.print(title); Serial.println(" Mode");
    Serial.print("Left Motor = "); Serial.println(leftMotorValue);
    Serial.print("Right Motor = "); Serial.println(rightMotorValue);
    /*
      Serial.print("f1:");
      Serial.print(" - ");
      Serial.print(f1);
      Serial.print(" - ");
      Serial.print("b1");
      Serial.print(" - ");
      Serial.println(b1);
    */

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
      Serial.print("f1: "); Serial.print(f1);  Serial.print(" - "); Serial.print("b1: "); Serial.print(b1);
      Serial.print("s1: "); Serial.print(s1);  Serial.print(" - "); Serial.print("s2: "); Serial.print(s2);
      Serial.print("Forward: ");  Serial.print(forward);  Serial.print(" - Backwards: ");  Serial.print(backwards);  Serial.print(" - notMoving: ");  Serial.print(notMoving);
    }
    if (title == "Normal")
    {
      Serial.print("f1: "); Serial.print(f1);  Serial.print(" - "); Serial.print("b1: "); Serial.print(b1); Serial.print(" - ");
      Serial.print("NForward: ");  Serial.print(forward);  Serial.print(" - NBackwards: ");  Serial.print(backwards);  Serial.print(" - NnotMoving: ");  Serial.print(notMoving);
    }

    Serial.println();
    updateTime();
  }
  else{
    delay(100);
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
