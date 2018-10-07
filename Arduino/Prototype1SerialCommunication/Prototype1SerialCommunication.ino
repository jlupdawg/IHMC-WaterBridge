
char inputString[50];            // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const int numberOfInputs = 3;    // number of inputs through serial communication seperated by comma
int inByte[numberOfInputs][2];   // decoded serial communication 2D array for comparison of previous values
char *inputs[numberOfInputs];    // raw serial communication 

bool updateMotors = true;        // if inByte changes then update the motors

void setup() {
  Serial.begin(9600);            //begin serial communication
}

void loop() {
  readSerial();                  // check incoming serial communication
  printInByte();                 // printInbyte and decide on whether or not the motors should be updated and prints the value
  setMotors();                   // set the motors with pwm pin values

}

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
    for ( int i = 0; i <= numberOfInputs - 1; i++)
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
void setMotors()
{
  
}

