/****************************** Radio Setup ****************************************/
/* Arduino Mega
    Radio:
      Vin 3.3V
      GND GND
      EN - No Pin
      G0 D3
      SCK D52
      MISO D50
      MOSI D51
      CS D4
      RSI D2
    Motors:
      Left Motor PWM - D8
      Right Motor PWM - D9
    LCD (Left to Right):
      1:GND GND
      2:VIN 5V
      3:CONTRAST Potentiometer
      4:RS D30
      5:GND GND
      6:Enable D32
      7:No Pin
      8:No Pin
      9:No Pin
      10:No Pin
      11:D4 - D22
      12:D5 - D24
      13:D6 - D26
      14:D7 - D28
      15:BackLight - VIN w/ Resistor?
      16:GND GND

*/

const byte numChars = 32;
char *receivedChars;
char tempChars[numChars];        // temporary array for use when parsing
int arr[4]; //radio must receive 4 values
bool newData = false;
int counter = 0;

#include <SPI.h>
#include <RH_RF95.h>
#include <LiquidCrystal.h>
#include <Servo.h>




#define RFM95_CS  4    // "E"
#define RFM95_RST 2   // "D"
#define RFM95_INT 3   // "B"


// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);



/************************************************************************************************/

/************************************ Serial Communication **************************************/
char inputString[50];            // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const int numberOfInputs = 4;    // number of inputs through serial communication seperated by comma {status, leftMotor %, rightMotor %}
int inByte[numberOfInputs][2];   // decoded serial communication 2D array for comparison of previous values
char *inputs[numberOfInputs];    // raw serial communication
/************************************************************************************************/

/************************************ Manual Controller *****************************************/

int manualControllerArray[4] = {
  0, 0, 0, 0
};  //node, button, xValue, yValue
bool controllerMode = false;

/************************************************************************************************/

/***************************************** Docking **********************************************/

int dockingArray[4] = {
  0, 0, 0, 0
}; //node, inRange (high / low), leftSonar, rightSonar
int dockingStatus = 0;
bool dockingMode = false;

/************************************************************************************************/

/***************************************** LCD Write ********************************************/

LiquidCrystal lcd(30, 32, 22, 24, 26, 28);

/************************************************************************************************/

/*************************************** Motor Setup ********************************************/

byte leftMotorPin = 8;
byte rightMotorPin = 9;
bool updateMotors = true;        // if inByte changes then update the motors
int leftMotorValue = 0;
int rightMotorValue = 0;
Servo leftMotor;
Servo rightMotor;


/************************************************************************************************/

void setup() {

  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("hello, world!");

  /************************************************* This bit is initalizing the radio *****************************/
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
  
  while (!Serial) {
    delay(1);
  }
  delay(100);

  //Serial.println("Feather LoRa RX Test!");
  //Serial.flush();

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
  /***************************************************************************************************************/
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(leftMotorPin);
  rightMotor.writeMicroseconds(1500);
  rightMotor.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(1000); // delay to allow the ESC to recognize the stopped signal


}

void loop() {
<<<<<<< HEAD
  /*
    //Serial.println("Begin");
    if ((controllerMode == false) && (dockingMode == false))  //must reset the master board after putting the boat in controllerMode. This is intentional
    {
    //Serial.println("normal mode");
    incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
    if (newData == true) {
      strcpy(tempChars, receivedChars);
      parseData();
    }
    newData = false;
=======
  //Serial.println("Begin");

  if ((controllerMode == false) && (dockingMode == false))  //must reset the master board after putting the boat in controllerMode. This is intentional
  {
    //Serial.println("normal mode");
    incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
>>>>>>> parent of ee904d3... Fixed Controller Code
    readSerial();                  // check incoming serial communication
    printInByte();                 // printInbyte and decide on whether or not the motors should be updated and prints the value
    if (updateMotors)
    {
      setMotors_Serial();                 // set the motors with pwm pin values
      //writeLCD_Motors();
      //writeLCD(inByte[0][1], inByte[1][1]);
    }
    }
    else if (controllerMode == true)   //Only perform tasks necessary to manually control the boat
    {
    incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
    if (newData == true) {
      strcpy(tempChars, receivedChars);
      parseData();
    }
    newData = false;
    setMotors_Controller();
    Serial.println("Controller Mode");
    }
    else if (dockingMode == true)
    {
    incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
    if (newData == true) {
      strcpy(tempChars, receivedChars);
      parseData();
    }
    readSerial();
    dock();
    setMotors_dock();
    }
    incomingRadio();
    //setMotors_Controller();
  */
  incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
   
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
  }
<<<<<<< HEAD
  newData = false;
  setMotors_Controller();
=======

>>>>>>> parent of ee904d3... Fixed Controller Code
}





