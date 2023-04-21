/* The program for the feather1 to take information from nano 33 ble sense rev2 and radio it to  where the feather2 
** will communicate to the ground station's program todisplay the data in a user friendly manner, and will display results
*/
#include <RH_RF95.h>

// LoRa settings
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define RFM95_FREQ 915.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(100);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  if (!rf95.init()) {
    Serial1.println("LoRa init failed. Check your connections.");
    while (1) ;
  }
  rf95.setFrequency(RFM95_FREQ);
  rf95.setTxPower(23, false);
  Serial.println("LoRa Transmitter Ready!");
}

void loop() {
  static uint16_t messageCount = 0;
  String input;
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    input += c;
  }
  
  if (input.length() > 0) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    input.getBytes(buf, input.length() + 1);
    rf95.send(buf, input.length() + 1);
    rf95.waitPacketSent();
    Serial1.println("Sent message #" + String(messageCount) + ": " + input);
    messageCount++;
  }
    digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
