/* The program for the Nano 33 Ble sense to take information from sensors and forward it to the feather where the feather 
** will take that information and beam it over its builtin lora radio to feather2 (lets just call that feather2 to make this easier)
** feather2 will communicate to the ground station's program todisplay the data in a user friendly manner, and will display results
*/

#include <RH_RF95.h>

// LoRa settings
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define RFM95_FREQ 915.0
#define BUTTON 11

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available 
  /* The infinite while loop above not needed if you're not using rx/tx for sending 
  ** the recieved radio data to your program or are using some other method to 
  */
  pinMode(BUTTON, INPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(100);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  if (!rf95.init()) {
    Serial.println("LoRa init failed. Check your connections.");
    while (1) ;
  }
  rf95.setFrequency(RFM95_FREQ);
  rf95.setTxPower(23, false);
 // Serial.println("LoRa Receiver Ready!");
}

void loop() {
  if(digitalRead(BUTTON)){
    
    Serial.println("Rover mode");
    Serial.println("Enabling rover mode. Non-Camera hotfix 2023-04-22 (2:19).")
  }
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
     // Serial.print("Received: ");
      Serial.println((char*)buf);
    } else {
      Serial.println("LoRa receive failed");
    }
  }
}

