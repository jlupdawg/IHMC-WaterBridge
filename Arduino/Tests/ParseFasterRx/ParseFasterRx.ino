
// Example 5 - Receive with start- and end-markers combined with parsing

const byte numChars = 32;
char *receivedChars;
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
int messageFromPC = 0;
int integerFromPCA = 0;
int integerFromPCB = 0;
int integerFromPCC = 0;
float floatFromPC = 0.0;

boolean newData = false;

//============

#include <SPI.h>
#include <RH_RF95.h>

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
#define RFM95_CS  4    // "E"
#define RFM95_RST 2   // "D"
#define RFM95_INT 3   // "B"

#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(115200);
  Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
  Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
  Serial.println();

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  while (!Serial) {
    delay(1);
  }
  delay(100);

  Serial.println("Feather LoRa RX Test!");

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

//============

void loop() {
  recvRadio();
  //recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;
  }
}

//============

void recvRadio()
{
  if (rf95.available())
  {
    newData = true;
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      receivedChars = buf;
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index
while(strtokIndx != '!')
{
  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  messageFromPC = atoi(strtokIndx);
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  integerFromPCA = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  integerFromPCB = atof(strtokIndx);     // convert this part to a float

  strtokIndx = strtok(NULL, ",");
  integerFromPCC = atof(strtokIndx);     // convert this part to a float
}
}

//============

void showParsedData() {
  Serial.print("Message ");
  Serial.println(messageFromPC);
  Serial.print("IntegerA ");
  Serial.println(integerFromPCA);
  Serial.print("IntegerB ");
  Serial.println(integerFromPCB);
  Serial.print("IntegerC ");
  Serial.println(integerFromPCC);
  Serial.println();

}
