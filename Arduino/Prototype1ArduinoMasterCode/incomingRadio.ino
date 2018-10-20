void incomingRadio() {
    if (rf95.available())
  {
<<<<<<< HEAD
    newData = true;
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if(rf95.recv(buf, &len))
    {
      receivedChars = buf;
      //Serial.println((char*)buf);
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}
void parseData() {
  char * strtokIndx; // this is used by strtok() as an index
  //Serial.println(tempChars);
  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  arr[0] = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  arr[1] = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  arr[2] = atoi(strtokIndx);     

  strtokIndx = strtok(NULL, ",");
  arr[3] = atoi(strtokIndx);     

  strtokIndx = strtok(NULL, ",");
  arr[4] = atoi(strtokIndx);   


  if (arr[0] == 1)
  {
    for (int i = 0; i < 4; i++)              // move values from arr to the Manual Controller Array
    {
      manualControllerArray[i] = arr[i];
      //Serial.println(arr[i]);
    }
  }

  else if (arr[0] == 2)
  {
    for (int i = 0; i < 4; i++)              // move values from arr to the Manual Controller Array
    {
      dockingArray[i] = arr[i];
      //Serial.println(arr[i]);
    }
  }

  if (manualControllerArray[1] == 1)
  {
    controllerMode = true;
  }

=======
          //Serial.println("Radio Buffer");
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; //create a buffer to add the message to
      uint8_t len = sizeof(buf); //create a variable that is the length of buf

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
        const int bufferSize = 5;  // the max number of variables you can recieve + 1
        int arr[bufferSize];       // creates a temporary interger array

        char *p = strtok((char*)buf, ",");  //create a token at every delimiter ","
        byte index = 0;                     // basically, this is "i" in a for loop of undefined size

        while (p != NULL && index < bufferSize) { // while p is not null and the index is less than or equal to the amount of variables you are recieving
          arr[index++] = atoi(p);                    // in the temporary array change your token to an integer and save it
          p = strtok(NULL, ",");                     // if p = the delimiter it is null and it is skipped
        }
        //Serial.println(arr[0]);
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
>>>>>>> parent of ee904d3... Fixed Controller Code
}

