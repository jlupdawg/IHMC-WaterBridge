void incomingRadio() {
  if(rf69.init())
  {
    if (rf69.available()) { // if there is a message

        uint8_t buf[RH_RF69_MAX_MESSAGE_LEN]; //create a buffer to add the message to
      uint8_t len = sizeof(buf); //create a variable that is the length of buf

        if (rf69.recv(buf, &len)) {
        if (!len) return;
        buf[len] = 0;
        /*
        Serial.print("Received [");
         Serial.print(len);
         Serial.print("]: ");
         Serial.println((char*)buf);
         Serial.print("RSSI: ");
         Serial.println(rf69.lastRssi(), DEC);
         */
        const int bufferSize = 5;  // the max number of variables you can recieve + 1
        int arr[bufferSize];       // creates a temporary interger array

        char *p = strtok((char*)buf, ",");  //create a token at every delimiter ","
        byte index = 0;                     // basically, this is "i" in a for loop of undefined size

        while (p != NULL && index < bufferSize) { // while p is not null and the index is less than or equal to the amount of variables you are recieving
          arr[index++] = atoi(p);                    // in the temporary array change your token to an integer and save it
          p = strtok(NULL, ",");                     // if p = the delimiter it is null and it is skipped
        }
        Serial.println(arr[0]);
        if (arr[0] = 1)
        {
          for (int i = 0; i < index; i++)              // move values from arr to the Manual Controller Array
          {
            manualControllerArray[i] = arr[i];
            //Serial.println(arr[i]);
          }
        }
        else if (arr[0] = 2)
        {
          for (int i = 0; i < index; i++)              // move values from arr to the Manual Controller Array
          {
            dockingArray[i] = arr[i];
            //Serial.println(arr[i]);
          }
        }
      }
      else
      {
        Serial.println("Receive failed");
      }
    }
    if (manualControllerArray[1] == 1)
    {
      controllerMode = true;
    }
  }
}

