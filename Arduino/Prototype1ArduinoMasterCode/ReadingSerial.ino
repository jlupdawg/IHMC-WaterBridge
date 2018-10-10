void readSerial()
{
  int charsRead;                
  int i;
  char *ptr;

  if (Serial.available() > 0) {                                                               //if serial coms are available then read them
    charsRead = Serial.readBytesUntil('\n', inputString, sizeof(inputString) - 1);            //read the serial com until new line
    inputString[charsRead] = '\0';         
    i = 0;
    ptr = strtok(inputString, ",");                                                           // split com string into tokens every ','
    while (ptr) {
      inputs[i] = ptr;                                                                        //const char array = token
      inByte[i][0] = atoi(inputs[i]);                                                         //const char array to int array
      //Serial.print(pad[i]);
      //Serial.print("   ");
      i++;
      ptr = strtok(NULL, ",");                                                                //progress to next token
    }
  }
}

void printInByte()
{
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
    for( int i = 0; i <= numberOfInputs - 1; i++)
    {
      inByte[i][1] = inByte[i][0];                            //updates input values
      Serial.print("Input "); Serial.print(i + 1); Serial.print(" = "); Serial.println(inByte[i][1]);  //prints input data
    }
    Serial.println();
    updateMotors = true;                                     //update the motors ONLY when new data arrives
  }
  else
  {
    updateMotors = false;                                   
  }
}
