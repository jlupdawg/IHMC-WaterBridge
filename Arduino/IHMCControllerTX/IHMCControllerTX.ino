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
#define LED           13


int xAxis = 0;
byte xPin = A0;
int yAxis = 0;
byte yPin = A1;
byte buttonNumber = 0;
byte buttonPin = 5;

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

int16_t packetnum = 0;  // packet counter, we increment per xmission


void setup()
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer

  pinMode(LED, OUTPUT);
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
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
                  };
  rf69.setEncryptionKey(key);

  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(5, INPUT);
}



void loop() {
readJoystick();
sendRadio();
}
void readJoystick()
{
  
buttonNumber = digitalRead(buttonPin);
xAxis = analogRead(xPin);
yAxis = analogRead(yPin);

}
void sendRadio()
{
  //delay(1000);  // Wait 1 second between transmits, could also 'sleep' here!
  char radiopacket[30];

  char yValue[8];
  itoa(yAxis, yValue, 10);
  char xValue[8];
  itoa(xAxis, xValue, 10);
  char button[8];
  itoa(buttonNumber, button, 10);
  const char *delimiter = ",";

  strcpy(radiopacket, button);
  strcat(radiopacket, delimiter);
  strcat(radiopacket, yValue);
  strcat(radiopacket, delimiter);
  strcat(radiopacket, xValue);

  itoa(packetnum++, radiopacket + 13, 10);
  Serial.print("Sending "); Serial.println(radiopacket);

  // Send a message!
  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();
}


