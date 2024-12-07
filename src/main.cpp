/*
  Code by Declan Saul, Joshua Jackson-Smith and Connor Crighton of Parklands College Secondary for the 2024 NASA High Altitude Balloon Launch.
*/
#include <Arduino.h>
#include <Wire.h>
#include <IWB.h>
#include <IGA.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "kxtj3-1057.h"

#define I2C_SDA 26
#define I2C_SCL 27

#define KXTJ3_DEBUG Serial
#define LOW_POWER

#define SPI_MISO 12
#define SPI_MOSI 13
#define SPI_SCK 14
#define SD_CS 5

double localPressure = 1017.0; // Local pressure in hPa (Cape Town South Africa)
float   sampleRate = 6.25;  // HZ - Samples per second - 0.781, 1.563, 3.125, 6.25, 12.5, 25, 50, 100, 200, 400, 800, 1600Hz
uint8_t accelRange = 8;     // Accelerometer range = 2, 4, 8, 16g
SPIClass spi = SPIClass(HSPI);

IGA airQualitySensor;
IWB pressureSensor;

KXTJ3 myIMU(0x0F); //IMU Address
uint16_t carbonDioxide, volatileOrganicCompounds;
double temperatureC, pressure;
String header = "Time,Pressure,Temperature,Acell X,Acell Y,Acell Z,CO2 equivelent,TVOC";

String dataPath = "/data0.csv";
String defaultDataFileName = "data";

void write(String path, String data) {
  File file = SD.open(path, FILE_APPEND);
  if(!file) { 
    return; 
  }
  if(file.println(data)) { } else { }
  file.close();
}

void takeReadings(){

  myIMU.standby(false);
  airQualitySensor.getData(carbonDioxide, volatileOrganicCompounds);
  pressureSensor.getData(pressure, temperatureC);

  String data = "";
  data += 
    String(millis()) + "," +
    String(temperatureC) + "," +
    String(pressure) + "," +
    String(myIMU.axisAccel(X)) + "," +
    String(myIMU.axisAccel(Y)) + "," +
    String(myIMU.axisAccel(Z)) + "," +
    String(carbonDioxide) + "," +
    String(volatileOrganicCompounds);
  write(dataPath, data);
  
  myIMU.standby(true);
}
//append to file


//write to file (deletes original contents)
void writeHeader(String path, String header) {
  File file = SD.open(path, FILE_WRITE);
  if(!file) { return; }
  if(file.println(header)) { } else { }
  file.close();
}
void setup() {
    Serial.begin(115200);
    delay(1000);
  spi.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_CS); 
  if (!SD.begin(SD_CS, spi)) { 
    Serial.println("SD Card initialization failed");
    return;
  } else { 
    Serial.println("SD Card initialized");
    write("/log.txt", "SD Card initialized");
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD Card present");
    return; 
  } else { 
    if (SD.exists(dataPath)) {  //Check if the data file already exists and create a new one if it does
    int i = 1;
    while (SD.exists("/" + defaultDataFileName + String(i) + ".csv")) {
      i++;
    }
    dataPath = "/" + defaultDataFileName + String(i) + ".csv";
    Serial.println(i);
  }
    Serial.println("SD Card loaded");
    write("/log.txt", "SD Card loaded");
  }
    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();
      // Write the header to the CSV file
  writeHeader(dataPath, header);
  Serial.println("Wrote header to file");
  write("/log.txt", "Wrote header to file");

  //Start Sensors
  //IMU Start
  if( myIMU.begin(sampleRate, accelRange) != 0 )
  {
    Serial.print("Failed to initialize IMU.\n");
  }
  else
  {
    Serial.print("IMU initialized.\n");
  }
  myIMU.intConf(123, 1, 10, HIGH);
  //IMU End
  if (pressureSensor.begin()) {
    Serial.println("IWB initialized successfully.");
  } else {
    Serial.println("Failed to initialize IWB!");
  }

    if (airQualitySensor.begin()) {
        Serial.println("IGA initialized successfully.");
    } else {
        Serial.println("Failed to initialize IGA");

    }
}

void loop() {
    takeReadings();
    if (pressureSensor.getData(pressure, temperatureC)) {
        Serial.println(temperatureC);
        Serial.println(pressure);
    } else {
        Serial.println("Failed to get IWB data.");
    }
    delay(1000);
}