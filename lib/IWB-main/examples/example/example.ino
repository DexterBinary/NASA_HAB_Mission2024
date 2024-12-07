#include <ArduinoJson.h>
#include <Wire.h>
#ifndef I2C_SDA
#define I2C_SDA SDA
#endif
#ifndef I2C_SCL
#define I2C_SCL SCL
#endif

// Specifics
#include <IWB.h>
IWB input;
double var1, var2;
char s[] = "Pressure: %.2f hPa, Temperature: %.2f ºC\n";


void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nIWB Example Test\n");

    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    if (input.begin()) {
        Serial.println("IWB initialized successfully.");
    } else {
        Serial.println("Failed to initialize IWB!");
        exit(0);
    }
}

void loop() {
    if (input.getData(var1, var2)) {
        Serial.printf(s, var1, var2);
    } else {
        Serial.println("Failed to get IWB data.");
    }

    delay(1000);
}