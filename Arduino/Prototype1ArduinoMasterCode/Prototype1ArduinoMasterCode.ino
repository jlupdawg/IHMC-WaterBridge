/****************************** Radio Setup ****************************************/
/* Arduino Uno
 Vin 3.3V
 GND GND
 G0 D3
 SCK D13
 MISO D12
 MOSI D11
 CS D4
 RSI D2
 */
/* Arduino Mega
 Vin 3.3V
 GND GND
 G0 D3
 SCK D52
 MISO D50
 MOSI D51
 CS D4
 RSI D2
 */
#include <SPI.h>
#include <RH_RF95.h>
#include <LiquidCrystal.h>


// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

  #define RFM95_RST     3   // "A"
  #define RFM95_CS      4   // "B"
  #define RFM95_INT     2   //  next to A


// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

/************************************************************************************************/

/************************************ Serial Communication **************************************/
char inputString[50];            // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const int numberOfInputs = 3;    // number of inputs through serial communication seperated by comma {status, leftMotor %, rightMotor %}
int inByte[numberOfInputs][2];   // decoded serial communication 2D array for comparison of previous values
char *inputs[numberOfInputs];    // raw serial communication
/************************************************************************************************/

/************************************ Manual Controller *****************************************/

int manualControllerArray[4] = {
  0, 0, 0, 0};  //node, button, xValue, yValue
bool controllerMode = false;

/************************************************************************************************/

/***************************************** Docking **********************************************/

int dockingArray[4] = {
  0, 0, 0, 0}; //node, inRange (high / low), leftSonar, rightSonar
int dockingStatus = 0;
bool dockingMode = false;

/************************************************************************************************/

/***************************************** LCD Write ********************************************/

LiquidCrystal lcd(30, 32, 22, 24, 26, 28);

/************************************************************************************************/

/*************************************** Motor Setup ********************************************/

byte leftMotor = 8;
byte rightMotor = 9;
bool updateMotors = true;        // if inByte changes then update the motors
int leftMotorValue = 0;
int rightMotorValue = 0;


/************************************************************************************************/

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("hello, world!");

  /************************************************* This bit is initalizing the radio *****************************/
    pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  while (!Serial) {
    delay(1);
  }

  delay(100);

  Serial.println("Feather LoRa TX Test!");

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


}

void loop() {
  //Serial.println("Begin");

  if ((controllerMode == false) && (dockingMode == false))  //must reset the master board after putting the boat in controllerMode. This is intentional
  {
    //Serial.println("normal mode");
    incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
    readSerial();                  // check incoming serial communication
    printInByte();                 // printInbyte and decide on whether or not the motors should be updated and prints the value
    if (updateMotors)
    {
      setMotors_Serial();                 // set the motors with pwm pin values
      writeLCD_Motors();
      //writeLCD(inByte[0][1], inByte[1][1]);
    }
  }
  else if (controllerMode == true)   //Only perform tasks necessary to manually control the boat
  {
    incomingRadio();
    setMotors_Controller();
  }
  else if (dockingMode == true)
  {
    incomingRadio();
    readSerial();
    dock();
    setMotors_dock();
  }

}





