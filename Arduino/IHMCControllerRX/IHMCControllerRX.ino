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

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

  #define RFM95_RST     2   // "A"
  #define RFM95_CS      4   // "B"
  #define RFM95_INT     3   //  next to A
/*********************************************/


// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);


void setup()
{
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
}


void loop() {
  if (rf95.available()) {

    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
Serial.println("MAdeIT");
    if (rf95.recv(buf, &len)) {
      if (!len) return;
      buf[len] = 0;
      Serial.print("Received [");
      Serial.print(len);
      Serial.print("]: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);

      const int bufferSize = 5;
      int arr[bufferSize];

      char *p = strtok((char*)buf, ",");
      byte index = 0;

      while (p != nullptr && index < bufferSize) {
        arr[index++] = atoi(p);
        p = strtok(NULL, ",");
      }

      for (int i = 0; i < index; i++)
        Serial.println(arr[i]);

    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}

