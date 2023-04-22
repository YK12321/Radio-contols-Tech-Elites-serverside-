//BLE lib{
#include <ArduinoBLE.h>
#include <HardwareBLESerial.h>
//BLE lib}
//Temperature and humidity{
#include <Arduino_HS300x.h>
//Temperature and humidity}
//Temperature and humidity variables{
float temperature[6];
float humidity[6];
char iChar;
//Temperature and humidity variables}
bool freeYet = false;
bool done = false;
  HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();
void setup() {
  // put your setup code here, to run once:
/*  blePeripheral.setLocalName("Transmitter");
  blePeripheral.setDeviceName("Transmitter");
  blePeripheral.setAppearance(0x0080);
  blePeripheral.begin();
  bleSerial.setLocalName("Transmitter Serial");
  bleSerial.begin();
  blePeripheral.addAttribute(bleSerial);*/
  Serial1.begin(9600);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
   if (!bleSerial.beginAndSetupBLE("Echo")) {
    Serial.begin(9600);
    while (true) {
      Serial.println("failed to initialize HardwareBLESerial!");
      delay(1000);
    }
  }
  if (!HS300x.begin()) {
  Serial1.println("Failed to initialize humidity temperature sensor!");
  int i = 0;
    Serial1.println("Trying again\n");
    while (!HS300x.begin()){
      if(i>0){
        Serial1.print(" Failed\n");
      }
      Serial1.print("Try number ");
      Serial1.print(i);
      i++;
      delay(1000);
    }
    Serial1.print("Passed\nOn attempt number ");
    Serial1.print(i);
    Serial1.print("\n");
}

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!done){
    int i =0;
  if(!freeYet){
    moveForward(10000);
    freeYet=true;
  }
  stop();
  
  i = readSensors(i);
  bleSerial.poll();
  if(bleSerial.availableLines()>0){
  bleSerial.print(temperature[i]);
  bleSerial.print(",");
  bleSerial.print(humidity[i]);
  bleSerial.print(",");
  iChar = String(i)[0];
  bleSerial.print(iChar);
  }
  moveForward(3000);
  i = readSensors(i);
  bleSerial.poll();
  if(bleSerial.availableLines()>0){
  bleSerial.println(temperature[i]);
  bleSerial.print(",");
  bleSerial.print(humidity[i]);
  bleSerial.print(",");
  iChar = String(i)[0];
  bleSerial.print(iChar);
  }
  turnRight();
  moveForward(3000);
  bleSerial.poll();
  if(bleSerial.availableLines()>0){
  i = readSensors(i);
  bleSerial.println(temperature[i]);
  bleSerial.print(",");
  bleSerial.print(humidity[i]);
  bleSerial.print(",");
  iChar = String(i)[0];
  bleSerial.print(iChar);}
  turnLeft();
  moveForward(3000);
  bleSerial.poll();
  if(bleSerial.availableLines()>0){
  i = readSensors(i);  
  bleSerial.println(temperature[i]);
  bleSerial.print(",");
  bleSerial.print(humidity[i]);
  bleSerial.print(",");
  iChar = String(i)[0];
  bleSerial.print(iChar);}
  turnLeft();
  moveForward(3000);
   bleSerial.poll();
  if(bleSerial.availableLines()>0){
  i = readSensors(i);
  bleSerial.println(temperature[i]);
  bleSerial.print(",");
  bleSerial.print(humidity[i]);
  bleSerial.print(",");
  iChar = String(i)[0];
  bleSerial.print(iChar);}
  turnLeft();
  moveForward(3000);
   bleSerial.poll();
  if(bleSerial.availableLines()>0){
  i = readSensors(i);
  bleSerial.println(temperature[i]);
  bleSerial.print(",");
  bleSerial.print(humidity[i]);
  bleSerial.print(",");
  iChar = String(i)[0];
  bleSerial.print(iChar);}
  turnLeft();
  // Serial1.print("C"); Deprecated due to the camera being broken
  //delay(8*60*1000); Removed in camera hotfix, as no longer needed
  turnRight();
  turnRight();
  moveForward(5000);
  done=true;
  
  // Read data from sensors or other sources

  // Send data to receiver
  delay(1000);
  }
}
int readSensors(int i) {
  temperature[i] = roundf(HS300x.readTemperature() * 1000) / 1000.0f;
  humidity[i] = roundf(HS300x.readHumidity() * 1000) / 1000.0f;
  i++;
}
void LFRS(){
  digitalWrite(D3, LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D2, HIGH);
}
void LSRF(){
  digitalWrite(D2, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4,HIGH);
}
void LFRF(){
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D4, HIGH);  
  digitalWrite(D2, HIGH);
}
void moveForward(){
LFRF();
}
void moveForward(int Delay){
  LFRF();
  delay(Delay);
  stop();
}

void stop(){
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
}
void moveBack(){
//deprecated
}
void moveBack(int delay){
//deprecated
}
void turnRight(){
  LFRS();
  delay(500);
  stop();
}
void turnLeft(){
  LSRF();
  delay(500);
  stop();
}