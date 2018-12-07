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

#include <LiquidCrystal.h>
#include <Servo.h>




#include <SPI.h>
#include <RH_RF95.h>

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!

// Singleton instance of the radio driver
#define RFM95_CS  4    // "E"
#define RFM95_RST 2   // "D"
#define RFM95_INT 3   // "B"


#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);
/************************************************************************************************/

/************************************ Serial Communication **************************************/
char inputString[50];            // ------------------------------------------------------------------a string to hold incoming data
boolean stringComplete = false;  // ------------------------------------------------------------------whether the string is complete
const int numberOfInputs = 4;    // ------------------------------------------------------------------number of inputs through serial communication seperated by comma {status, leftMotor %, rightMotor %}
int inByte[numberOfInputs][2];   // ------------------------------------------------------------------decoded serial communication 2D array for comparison of previous values
char *inputs[numberOfInputs];    // ------------------------------------------------------------------raw serial communication
/************************************************************************************************/

/************************************ Manual Controller *****************************************/

int manualControllerArray[4] = {
  0, 0, 0, 0
};  //node, button, xValue, yValue
bool controllerMode = false;
bool controllerModeHard = false;

/************************************************************************************************/

/*************************************** Sonar Setup ********************************************/

//Pins for Corner Sonar sensors
#define trigPin_1 39
#define echoPin_1 41
#define trigPin_2 21
#define echoPin_2 23
#define trigPin_3 25
#define echoPin_3 27
#define trigPin_4 37
#define echoPin_4 35
/*Pins for Front and Back sonar sensors*/
#define pinF_2 5      //Front sonar echo pin
#define pinB_2 6      //Back sonar echo pin
#define pinB_4 11     //F_B sonar trigger pin

double duration_corner, duration_front_back; //------------------------------------------------------------------variable for microsecond values recorded from sonar values
double distance_corner, distance_front_back = 3000, s1, s2, s3, s4;//--------------------------------------------distance storage variables
double f1 = 3000, b1 = 3000; //----------------------------------------------------------------------------------out of range values, sonar will never read this high
double watchCircleRadius = 106.5; //-----------------------------------------------------------------------------radius of circle "around" the boat, used for minimum allowable distance of objects to the center of the boat
double CalibrationFactor = 58.3; //------------------------------------------------------------------------------units: microsec/cm, initialize as 58.3(STP factor) when thermisor not set up
int objectIndicated = 0, forward = 0, backwards = 0, notMoving = 3; //-----------------------------------------------------------state indicator variables
int Direction = 3; //--------------------------------------------------------------------------------------------Left(1), Right(0), Center(2): relative to the front sonar sensor(front of boat), 3 is never a valid direction indicator

int ThermistorPin = 0;
double AmbientTemp; //-------------------------------------------------------------------------------------------Celcius

/************************************************************************************************/

/***************************************** Docking **********************************************/

int dockingArray[4] = {
  0, 0, 0, 0
}; //node, inRange (high / low), leftSonar, rightSonar
int dockingStatus = 0;

/************************************************************************************************/
/***************************************** Logging **********************************************/

unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
int timerThreshold = 100;

/************************************************************************************************/

/***************************************** LCD Write ********************************************/

LiquidCrystal lcd(30, 32, 22, 24, 26, 28);

/************************************************************************************************/

/*************************************** Motor Setup ********************************************/

byte leftMotorPin = 9;
byte rightMotorPin = 10;
bool updateMotors = true;        // if inByte changes then update the motors
int leftMotorValue = 0;
int rightMotorValue = 0;
Servo leftMotor;
Servo rightMotor;

int percentage = 15;

//int minSpeed = 1100;
int stopSpeed = 1500; //--------------------------------------------------------------------------Mapped to 0% motor speed
//int maxSpeed = 1900;
int minSpeed = stopSpeed - (400 * percentage / 100);
int maxSpeed = (400 * percentage / 100) + stopSpeed;


bool dockingMode = false;

/************************************************************************************************/


/************************************************************************************************/

void setup() {

  lcd.begin(16, 2);
  lcd.clear();
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(115200);
  /************************************************* This bit is initalizing the radio *****************************/
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(100);
  Serial.println("Arduino LoRa RX Test!");

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

  /***************************************************************************************************************/
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);
  leftMotorValue = stopSpeed;
  rightMotorValue = stopSpeed;
  //leftMotorValue = 1600;
  //rightMotorValue = 1600;
  leftMotor.writeMicroseconds(leftMotorValue);
  rightMotor.writeMicroseconds(rightMotorValue); // send "stop" signal to ESC.
  delay(1000); // delay to allow the ESC to recognize the stopped signal


  /*************************************Sonar Pin Modes******************************************************/
  //----------------------------------------------------------------------------------------------------------echo pins are set to input because they recieve a sound pulse in from a transmit, triger are set to output because arduino triggers a pulse using HIGH -> LOW
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);
  pinMode(trigPin_4, OUTPUT);
  pinMode(echoPin_4, INPUT);
  pinMode(pinF_2, INPUT);
  pinMode(pinB_2, INPUT);
  pinMode(pinB_4, OUTPUT); //--------------------------------------------------------------------------------uses pin 2 for triggeringboth front and back sonar sensor.
}

void loop() {

  //Serial.println("loop");

  if ((controllerMode == false) && (dockingMode == false) && (objectIndicated == 0)) { //-------------must reset the master board after putting the boat in controllerMode. This is intentional
    //Serial.println("PRINT 1");
    
    incomingRadio();            // ------------------------------------------------------------------reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
    readSerial();               // ------------------------------------------------------------------check incoming serial communication
    printInByte();              // ------------------------------------------------------------------printInbyte and decide on whether or not the motors should be updated and prints the value
    Object_Location();
    //Serial.println("PRINT 7");
    
    /*if (updateMotors) {
      setMotors_Serial();       // ------------------------------------------------------------------set the motors with pwm pin values
      //writeLCD_Motors();
      //writeLCD(inByte[0][1], inByte[1][1]);
    }*/
    

    loggingData("Normal");
  }
  else if (controllerModeHard == true)
  {
    incomingRadio();
    setMotors_Controller();
    loggingData("Controller Mode Hard");
  }
  else if (objectIndicated == 1 && dockingMode == false) {
    //Serial.println("PRINT 2");
    incomingRadio();
    Object_Location();
    setMotors_Sonar();
    cornerSonarCheck();
    setMotors_Sonar();

    loggingData("Sonar");
  }
  else if (controllerMode == true)   //------------------------------------------------------------------Only perform tasks necessary to manually control the boat
  {
    incomingRadio();            // ----------------------------------------------------------------------reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
    setMotors_Controller();
    Object_Location();
    //Serial.println("Controller Mode");
    loggingData("Controller");
  }

  else if (dockingMode == true)
  {
    /*incomingRadio();            // reads incoming radio and sends it to the motors. This may need to be changed to "Incoming Radio" for future use
      readSerial();
      dock();
      setMotors_dock();
      loggingData("Docking Mode");*/
    DockingMechanism();

  }

}
