#include <ArduinoJson.h>
#include <Wire.h>
#ifndef I2C_SDA
#define I2C_SDA SDA
#endif
#ifndef I2C_SCL
#define I2C_SCL SCL
#endif

#include "IGA.h" 
IGA input;       

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nIGA JSON Test\n");

    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    if (!input.begin()) {
        Serial.println("Failed to initialize IGA.");
        while (1) delay(10);
    } else {
        Serial.println("IGA initialized.");
    }
}

void loop() {
    JsonDocument root;

    if (input.getJSON(root)) {
        serializeJsonPretty(root, Serial);
        Serial.println();
    } else {
        Serial.println("Failed to get IGA data.");
    }

    delay(1000);
}
