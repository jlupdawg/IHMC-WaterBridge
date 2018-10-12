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

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 434

#define RFM69_INT     3  // 
#define RFM69_CS      4  //
#define RFM69_RST     2  // "A"

/****************************************************** Output Variables *************************************************/
int xAxis = 0; //Joystick x axis value
byte xPin = A0; // Joystick x axis input pin
int yAxis = 0;
byte yPin = A1;
byte buttonNumber = 0;
byte buttonPin = 7;
byte nodeNumber = 1; //defines which device is communicating with the master

/************************************************************************************************************************/
// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

int16_t packetnum = 0;  // packet counter, we increment per xmission


void setup()
{
  Serial.begin(115200);
  /************************************************* This bit is initalizing the radio *****************************/
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather RFM69 TX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  //rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
                  };
  rf69.setEncryptionKey(key);
  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
  /***************************************************************************************************************/

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT);
}



void loop() {
  readJoystick();  //read Values from the joystick
  sendRadio();     //send values over the radio
}
void readJoystick()
{

  buttonNumber = !digitalRead(buttonPin);  //invert the input from the joystick. It MUST have a pullup resistor. 330 Ohm works well.
  xAxis = analogRead(xPin);
  yAxis = analogRead(yPin);

}
void sendRadio()
{
  //delay(1000);  // Wait 1 second between transmits, could also 'sleep' here!
  char radiopacket[30];    //creates a character array to send information over the radio. This is the only allowable format

  char node[8];           //creates a temporary character array
  itoa(nodeNumber, node, 10); //places the value "nodeNumber" into a character array
  char xValue[8];
  itoa(xAxis, xValue, 10);
  char yValue[8];
  itoa(yAxis, yValue, 10);
  char button[8];
  itoa(buttonNumber, button, 10);
  const char *delimiter = ",";  // a delimiter is what defines the seperations in your string/array

  strcpy(radiopacket, node);    // copies the character array "node" into radiopacket
  strcat(radiopacket, delimiter); // concatenate (tacks on the end) the delimiter character
  strcat(radiopacket, button); // concatenate (tacks on the end) the character array "button"
  strcat(radiopacket, delimiter);
  strcat(radiopacket, yValue);
  strcat(radiopacket, delimiter);
  strcat(radiopacket, xValue);

  itoa(packetnum++, radiopacket + 13, 10); // adds the number of packet being sent. I don't think we need this.
  Serial.print("Sending "); Serial.println(radiopacket); //serial prints what is being sent

  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));  //sends the unsigned 8 bit integer from ram at the address "radiopacket" and the length of the radiopacket
  rf69.waitPacketSent(); //unsure what this does. I assume it creates a minimal delay for radio clarity.
}


