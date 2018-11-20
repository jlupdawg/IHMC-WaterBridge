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
#include <RH_RF69.h>
#include <LiquidCrystal.h>


// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 434
#define RFM69_INT     3  // 
#define RFM69_CS      4  //
#define RFM69_RST     2  // "A"
#define LED           13


// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

/************************************************************************************************/

/************************************ Serial Communication **************************************/
char inputString[50];            // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const int numberOfInputs = 2;    // number of inputs through serial communication seperated by comma {status, leftMotor %, rightMotor %}
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

/*************************************** Sonar Setup ********************************************/
//Pins for Corner Sonar sensors
#define trigPin_1 13
#define echoPin_1 4
#define trigPin_2 10
#define echoPin_2 9
#define trigPin_3 7
#define echoPin_3 8
#define trigPin_4 12
#define echoPin_4 11

//Pins for Front and Back sonar sensors
//#define (Pin-On-Sensor)_(Sensor-Number) (Pin-On-Arduino)
#define Pin2_1 3
#define Pin2_2 5
#define Pin4_2 2 //trigger pin for both Front and Back Sensors

double duration, distance_corner, distance_front_back, s1, s2, s3, s4, f1, b1;
double CalibrationFactor;

/************************************************************************************************/

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("hello, world!");

  /************************************* Radio Setup ********************************************/
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);
  Serial.println("Feather RFM69 RX Test!");
  Serial.println();
  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    //while (1);
  }
  Serial.println("RFM69 radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  //rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW
  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
  };
  rf69.setEncryptionKey(key);
  Serial.print("RFM69 radio @");  
  Serial.print((int)RF69_FREQ);  
  Serial.println(" MHz");


  /********************************************************************************************************/


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
    dock();
    setMotors_dock();
  }
  
/***********************************************************************************SONAR LOOP CODE************************************************************************************************/
  
  Override(f1, b1);

}
