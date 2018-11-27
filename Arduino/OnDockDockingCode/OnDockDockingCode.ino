
#include <SPI.h>
#include <RH_RF95.h>

/*********** Sonar Setup ************************************************************/

#define EchoPinS1 1
#define EchoPinS2 2
#define TrigPinS1 11
#define TrigPinS2 12

double S1_Duration, S2_Duration;
float distanceS1;
float distanceS2;
float distBetweenSensors = 1; //distance in meters between S1 and S2
float detectDist = 1500; //Minimum distance from each sonar to consider an object "detected"
float AmbientTemp;
float CalibrationFactor;
float duration;
int sonarVar = 0; //switches between 0 and 1 to alternate between left and right sensors

/*********** Docking Calculation Setup ************************************************************/

float alpha;
float theta;
float dockDirection; //"heading" of dock (we should do this according to IMU!)
float desiredHeading;

bool signalReceived = false;
bool boatConfirmed = true; //We absolutely do not need this for the pool
bool dockingMode;
int regionVariable; //zone number that is sent through radio

/************ Radio Setup **********************************************************/


#define RF95_FREQ 915.0 //Talking to boat, freq matches Rx on boat

// Singleton instance of the radio driver
#define RFM95_CS  4    // "E"
#define RFM95_RST 2   // "D"
#define RFM95_INT 3   // "B"
/****************************************************** Output Variables *************************************************/
int xAxis = 0; //Joystick x axis value
byte xPin = A0; // Joystick x axis input pin
int yAxis = 0;
byte yPin = A1;
byte buttonNumber = 0;
byte buttonPin = 7;
byte nodeNumber = 3; //defines which device is communicating with the master, 3 IS THE DOCK!!!!! 

/************************************************************************************************************************/


// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);


void setup() {
  //calibrationFactorCalculation();
/*************SONAR SETUP*****************************************************************************************************/
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
  while (!Serial){
    delay(1);
  }
/*************RADIO SETUP*****************************************************************************************************/

// Change to 434.0 or other frequency, must match RX's freq!

// Singleton instance of the radio driver
  #define RFM95_CS  4    // "E"
  #define RFM95_RST 2   // "D"
  #define RFM95_INT 3   // "B"
  
  
  #define RF95_FREQ 915.0
  
  // Singleton instance of the radio driver
  RH_RF95 rf95(RFM95_CS, RFM95_INT);
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

    
}

void loop() {
  
  if (signalReceived && boatConfirmed){
    switch (sonarVar) {
      case 0:
          Sonar_S1();
          break;
      case 1:
          Sonar_S2();
          break;
      default:
          //error
          break;
    }
    findRegion(); //check to see if A, B, C, or D
    
    lawOfCosines(distanceS1, distanceS2, distBetweenSensors);
    findAlpha();
    calculateDesiredHeading();
    
    sendRadio();
    }
    
  else if(signalReceived == true && boatConfirmed == false){
    //try to confirm boat
    }

  else{
    receiveRadio(); //Keep trying to receive radio until the boat sends signal that it is within docking distance, then turn on sonar
    }
  
  /*S1_Duration = 0;
  if(S1_Duration != 0){
      dockingMode = 1; 
    }
  
  S2_Duration = 0;
  if(S2_Duration != 0){
      dockingMode = 1;
    }*/
}
