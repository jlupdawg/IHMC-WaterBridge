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


// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);



char inputString[50];            // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const int numberOfInputs = 2;    // number of inputs through serial communication seperated by comma
int inByte[numberOfInputs][2];   // decoded serial communication 2D array for comparison of previous values
char *inputs[numberOfInputs];    // raw serial communication

bool updateMotors = true;        // if inByte changes then update the motors

int manualControllerArray[3] = {0, 0, 0};
bool controllerMode = false;

byte leftMotor = 8;
byte rightMotor = 9;

void setup() {
  Serial.begin(115200);

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
    while (1);
  }
  Serial.println("RFM69 radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW
  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
                  };
  rf69.setEncryptionKey(key);
  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

void loop() {

  while (controllerMode == false)
  {
    manualController();
    readSerial();                  // check incoming serial communication
    printInByte();                 // printInbyte and decide on whether or not the motors should be updated and prints the value
    if (updateMotors)
    {
      setMotors();                   // set the motors with pwm pin values
    }
  }
  while (controllerMode == true)
  {
    manualController();
    setMotors_Controller();
  }

}



