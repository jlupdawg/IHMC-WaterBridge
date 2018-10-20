void incomingRadio() {
  if (rf95.available())
  {
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

}

