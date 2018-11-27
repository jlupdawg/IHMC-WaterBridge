
#include <SPI.h>
#include <RH_RF95.h>

/*********** Sonar Setup ************************************************************/

#define EchoPinS1 1
#define EchoPinS2 2
#define TrigPinS1 11
#define TrigPinS2 12

double S1_Duration, S2_Duration;
float sonarDist1;
float sonarDist2;
float distBetweenSensors = 1; //distance in meters between S1 and S2

/*********** Docking Calculation Setup ************************************************************/

float alpha;
float theta;
float dockDirection; //"heading" of dock (we should do this according to IMU!)
float desiredHeading;

boolean signalReceived = false;
bool boatConfirmed = true; //We absolutely do not need this for the pool
char locationVariable; //char that is sent through radio

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
  CalibrationFactorCalculation();
  
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
  while (!Serial) {
    delay(1);
    
}

void loop() {
  
  if (signalReceived && boatConfirmed){
    pingSonar();
    findChar(); //check to see if A, B, C, or D
    
    lawOfCosines(sonarDist1, sonarDist2, distBetweenSensors);
    findAlpha();
    calculateDesiredHeading();
    
    sendSignal();
    }
    
  
  S1_Duration = 0;
  if(S1_duration != 0){
      DockingMode = 1; 
    }
  
  S2_Duration = 0;
  if(S2_duration != 0){
      DockingMode = 1;
    }

}
