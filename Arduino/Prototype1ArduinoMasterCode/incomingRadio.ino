void incomingRadio() {

  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; //create a buffer to add the message to
  uint8_t len = sizeof(buf); //create a variable that is the length of buf
  if (rf95.available()) {
    //Serial.println("Radio Buffer");
    if (rf95.recv(buf, &len)) {
      if (!len) return;
      buf[len] = 0;
      /*
        Serial.print("Received [");
        Serial.print(len);
        Serial.print("]: ");
        Serial.println((char*)buf);
        Serial.print("RSSI: ");
        Serial.println(rf95.lastRssi(), DEC);
      */
      const int bufferSize = 4;  // the max number of variables you can recieve + 1
      int arr[bufferSize];       // creates a temporary interger array
      //Serial.println("Made It");
      char *p = strtok((char*)buf, ",");  //create a token at every delimiter ","
      byte index = 0;                     // basically, this is "i" in a for loop of undefined size

      while (p != NULL && index < bufferSize) { // while p is not null and the index is less than or equal to the amount of variables you are recieving
        arr[index++] = atoi(p);                    // in the temporary array change your token to an integer and save it
        p = strtok(NULL, ",");                     // if p = the delimiter it is null and it is skipped
        //Serial.println(arr[0]);
      }

      if (arr[0] == 1)
      {
        for (int i = 0; i < index; i++)              // move values from arr to the Manual Controller Array
        {
          manualControllerArray[i] = arr[i];
          //Serial.println(arr[i]);
        }
      }
      else if (arr[0] == 3)
      {
        for (int i = 0; i < index; i++)              // move values from arr to the Docking Array
        {
          dockingArray[i] = arr[i];
          Serial.println(arr[i]);
          dockingRegion = dockingArray[1];
          desiredHeading = dockingArray[2];

          printDockingStuff();
        }
      }
    }
    /*
      else
      {
      Serial.println("Receive failed");
      }
    */
    if (manualControllerArray[1] == 1)
    {
      controllerMode = true;
    }
    if (manualControllerArray[1] == 1 && manualControllerArray[2] > 1000)
    {
      controllerModeHard = true;
    }
    if (manualControllerArray[1] == 1 && manualControllerArray[2] < 200)
    {
      manualControllerArray[2] = 514;
      manualControllerArray[3] = 514;
      controllerMode = false;

    }

  }
}

void printDockingStuff(){
  Serial.print("dockingRegion: "); Serial.println(dockingRegion);
  Serial.print("desiredHeading "); Serial.println(desiredHeading);
  }
