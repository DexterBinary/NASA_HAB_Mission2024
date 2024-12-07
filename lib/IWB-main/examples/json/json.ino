#include <ArduinoJson.h>
#include <Wire.h>
#ifndef I2C_SDA
#define I2C_SDA SDA
#endif
#ifndef I2C_SCL
#define I2C_SCL SCL
#endif

#include "IWB.h"
IWB input;

void setup() {
    Serial.begin(115200);
    delay(1000);
    while(!Serial);
    Serial.printf("\nIWB JSON Test\n");

    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    if (input.begin()) {
        Serial.println("IWB initialized successfully.");
    } else {
        Serial.println("Failed to initialize IWB!");
        while(1);
    }
}

void loop() {
    JsonDocument root;

    if (input.getJSON(root)) {
        serializeJsonPretty(root, Serial);
        Serial.println();
    } else {
        Serial.println("Failed to get IWB data.");
    }

    delay(1000);
}
