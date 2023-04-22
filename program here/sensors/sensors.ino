/*
Including libraries
*/
//Ble{
#include <ArduinoBLE.h>
#include <HardwareBLESerial.h>
//Ble}
//Accelerometer & angular velocity{
#include "Arduino_BMI270_BMM150.h"
//Accelerometer & angular velocity}
//Temperature and humidity{
#include <Arduino_HS300x.h>
//Temperature and humidity}
//Pressure{
  #include <Arduino_LPS22HB.h>
//Pressure}
//Uv{
  #include "Adafruit_LTR390.h"
//UV}
//Gas{
  #include <MQ135.h>
//Gas}
/*
Creating variables for sensors
*/

/*
Setting up ble instance
*/
  HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();

int timeCustom = 0;
//Uv variables{
Adafruit_LTR390 ltr = Adafruit_LTR390();
int rawUv;
//Uv variables}
//Acceleration variables{
float x, y, z;
float xv, yv, zv;
//Acceleration variables}
//Temperature and humidity variables{
float temperature;
float humidity;
//Temperature and humidity variables}
//Pressure variables{
float pressure;
//Pressure variables}
//gas variables{
#define PIN_MQ135 A2
MQ135 mq135_sensor(PIN_MQ135);
//gas variables}

void setup() {
Serial.begin(9600);
/*
Setting up sensors
*/
   if (!bleSerial.beginAndSetupBLE("Echo")) {
     Serial.println("BLUETOOTH FAILED");
  }
//Uv{
if ( ! ltr.begin() ) {
    Serial1.println("Couldn't find LTR sensor!");
    while (1) delay(10);
  }
  Serial1.println("Found LTR sensor!");

  ltr.setMode(LTR390_MODE_UVS);
  if (ltr.getMode() == LTR390_MODE_ALS) {
    Serial1.println("In ALS mode");
  } else {
    Serial1.println("In UVS mode");
  }

  ltr.setGain(LTR390_GAIN_3);
  Serial1.print("Gain : ");
  switch (ltr.getGain()) {
    case LTR390_GAIN_1: Serial1.println(1); break;
    case LTR390_GAIN_3: Serial1.println(3); break;
    case LTR390_GAIN_6: Serial1.println(6); break;
    case LTR390_GAIN_9: Serial1.println(9); break;
    case LTR390_GAIN_18: Serial1.println(18); break;
  }

  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  Serial1.print("Resolution : ");
  switch (ltr.getResolution()) {
    case LTR390_RESOLUTION_13BIT: Serial1.println(13); break;
    case LTR390_RESOLUTION_16BIT: Serial1.println(16); break;
    case LTR390_RESOLUTION_17BIT: Serial1.println(17); break;
    case LTR390_RESOLUTION_18BIT: Serial1.println(18); break;
    case LTR390_RESOLUTION_19BIT: Serial1.println(19); break;
    case LTR390_RESOLUTION_20BIT: Serial1.println(20); break;
  }

  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);
//Uv}
//Accelerometer{
  if (!IMU.begin()) {
    Serial1.println("Failed to initialize IMU!");
    int i = 0;
    Serial1.println("Trying again\n");
    while (!IMU.begin()){
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
//Accelerometer}
//Temperature and humidity{
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
//Temperature and humidity}
//Pressure{
if (!BARO.begin()) {
  Serial1.println("Failed to initialize pressure sensor!");
    int i = 0;
    Serial1.println("Trying again\n");
    while (!BARO.begin()){
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
//Pressure}
}

void loop() {
  /*
  Read sensor data into the variables
  */
//Read Uv{
  if (ltr.newDataAvailable()) {
    rawUv = ltr.readUVS();
  }
//Read Uv}
  //Read acceleration{
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }
  //Read acceleration}
  //Read velocity{
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(xv, yv, zv);
  }
  //Read velocity}
  //Read temperature and humidity{
  temperature = HS300x.readTemperature();
  humidity = HS300x.readHumidity();
  //Read temperature and humidity}
  //Read pressure{
  pressure = BARO.readPressure();
  //Read pressure}
  //The variables for the gas sensor{
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  //The variables for the gas sensor}
  
  /*
  Print the sensor data to Serial1 (hopefully implement sending this data to the lora feather, which will radio it to a distant arduino)
  */
  //time, x, y, z, abs, temperature, humidity, pressure, uv, 
  Serial1.print(timeCustom);
  //Serial1.print(", ");
  // Serial1.print(x);
  // Serial1.print(", ");
  // Serial1.print(y);
  // Serial1.print(", ");
  // Serial1.print(z);
  Serial1.print(", ");
  Serial1.print(sqrt(x*x+y*y+z*z));
  Serial1.print(", ");
  Serial1.print(temperature);
  Serial1.print(", ");
  Serial1.print(humidity);
  Serial1.print(", ");
  Serial1.print(pressure);
  Serial1.print(", ");
  Serial1.print(rawUv);
  Serial1.print(", ");
  Serial1.print(correctedPPM);  
  delay(1000);
  timeCustom++;
  if(Serial.available()>0){
    String input = Serial.readString();
    if(input.equalsIgnoreCase("Rover mode")){
      rover();
    }
  }

}
void rover() {
  char line[20];
  while (1) {
    bleSerial.poll();
    if (bleSerial.availableLines() > 0) {
      // read the line of text from the BLESerial port
      bleSerial.readLine(line, sizeof(line));
      bleSerial.poll();
      // print the line of text to the serial1 port
      int a = 0;
      String lString;
      while (line[a] != '\0') {
        lString += line[a];
        a++;
      }
      Serial1.println(lString);
    }
  }
}
