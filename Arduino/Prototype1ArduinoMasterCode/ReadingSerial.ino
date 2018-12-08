void readSerial()
{
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '/';
  char rc;

  while (Serial.available() > 0 && newSerialData == false) {
    rc = Serial.read();
    
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedSerialChars[ndx] = rc;
        ndx++;
        if (ndx >= serialChars) {
          ndx = serialChars - 1;
        }
      }
      else {
        //writeLCDCounter();
        receivedSerialChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newSerialData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void printInByte()
{
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempSerialChars, ",");     // get the first part - the string
  inByte[0][0] = atoi(strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  inByte[1][0] = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  inByte[2][0] = atoi(strtokIndx);     // convert this part to a float

  //writeLCD(inByte[1][0], inByte[2][0]);
  
  updateMotors = false;

  for ( int i = 0; i <= numberOfInputs - 1; i++)              //this for loop compares previous and new data
  {
    if (inByte[i][1] != inByte[i][0])
    {
      updateMotors = true;
    }
  }


  if (updateMotors)
  {
    for ( int i = 0; i <= numberOfInputs - 1; i++)
    {
      inByte[i][1] = inByte[i][0];                            //updates input values
      //Serial.print("INBYTE "); Serial.print(i); Serial.print(" = ");
      //Serial.println(inByte[i][1]);
      //Serial.print("Input "); Serial.print(i + 1); Serial.print(" = "); Serial.println(inByte[i][1]);  //prints input data
    }
    //Serial.println();
  }
  else
  {
    updateMotors = false;
  }
  
  if (inByte[0][0] == 1)
  {
    dockingMode = true;
  }
}
