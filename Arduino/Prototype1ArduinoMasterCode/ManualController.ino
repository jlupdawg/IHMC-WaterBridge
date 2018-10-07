void manualController() {
  if (rf69.available()) {

    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf69.recv(buf, &len)) {
      if (!len) return;
      buf[len] = 0;
      Serial.print("Received [");
      Serial.print(len);
      Serial.print("]: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf69.lastRssi(), DEC);

      const int bufferSize = 5;
      int arr[bufferSize];

      char *p = strtok((char*)buf, ",");
      byte index = 1;

      while (p != nullptr && index < bufferSize) {
        arr[index++] = atoi(p);
        p = strtok(NULL, ",");
      }

      for (int i = 0; i < index; i++)
      {
        manualControllerArray[i] = arr[i];
        //Serial.println(arr[i]);
      }
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  if(manualControllerArray == 1)
  {
    controllerMode = true;
  }
}
