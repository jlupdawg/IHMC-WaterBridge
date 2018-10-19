/* Arduino Uno
 *  Radio
      Vin 3.3V
      GND GND
      EN - NO PIN
      G0 D3
      SCK D13
      MISO D12
      MOSI D11
      CS D4
      RSI D2
    Joystick
      Vin 5V
      GND GND
      VRX A0
      VRY A1
      SW D7 //Must be defined as a PULLUP
*/

#include <SPI.h>
#include <RH_RF95.h>

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

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
byte nodeNumber = 1; //defines which device is communicating with the master

/************************************************************************************************************************/


// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
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


  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission


void loop() {
  readJoystick();  //read Values from the joystick
  sendRadio();     //send values over the radio
  //printingSerial();
}
void readJoystick()
{

  buttonNumber = !digitalRead(buttonPin);  //invert the input from the joystick. It MUST have a pullup resistor. 330 Ohm works well.
  xAxis = analogRead(xPin);
  yAxis = analogRead(yPin);

  xAxis = map(xAxis, 0, 1023, 1023, 0);
  yAxis = map(yAxis, 0, 1023, 1023, 0);

  xAxis = constrain(xAxis, 0, 1023);
  yAxis = constrain(yAxis, 0, 1023);

  //Serial.println(xAxis);
  //Serial.println(yAxis);

}

void printingSerial()
{
  Serial.print("X Axis"); Serial.println(xAxis);
  Serial.print("Y Axis"); Serial.println(yAxis);
  Serial.print("Button"); Serial.println(buttonNumber);
  delay(1000);
}
void sendRadio()
{
  //delay(1000);  // Wait 1 second between transmits, could also 'sleep' here!
  char radiopacket[50];    //creates a character array to send information over the radio. This is the only allowable format

  for(int i = 0; i < 51; i++)
  {
    radiopacket[i] = 0;
  }

  char node[10];           //creates a temporary character array
  itoa(nodeNumber, node, 10); //places the value "nodeNumber" into a character array
  char xValue[10];
  itoa(xAxis, xValue, 10);
  char yValue[10];
  itoa(yAxis, yValue, 10);
  char button[10];
  itoa(buttonNumber, button, 10);
  const char *delimiter = ",";  // a delimiter is what defines the seperations in your string/array

  strcpy(radiopacket, node);    // copies the character array "node" into radiopacket
  strcat(radiopacket, delimiter); // concatenate (tacks on the end) the delimiter character
  strcat(radiopacket, button); // concatenate (tacks on the end) the character array "button"
  strcat(radiopacket, delimiter);
  strcat(radiopacket, yValue);
  strcat(radiopacket, delimiter);
  strcat(radiopacket, xValue);

  //itoa(packetnum++, radiopacket + 13, 10); // adds the number of packet being sent. I don't think we need this.
  Serial.print("Sending "); Serial.println(radiopacket); //serial prints what is being sent

  rf95.send((uint8_t *)radiopacket, strlen(radiopacket));  //sends the unsigned 8 bit integer from ram at the address "radiopacket" and the length of the radiopacket
  rf95.waitPacketSent(); //unsure what this does. I assume it creates a minimal delay for radio clarity.
}


