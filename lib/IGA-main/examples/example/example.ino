#include <Wire.h>
#ifndef I2C_SDA
#define I2C_SDA SDA
#endif
#ifndef I2C_SCL
#define I2C_SCL SCL
#endif

// Specifics
#include <IGA.h>
IGA input;
uint16_t var1, var2;
char s[] = "CO2 concentration: %d ppm, TVOC concentration: %d ppb\n";

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nIGA Example Test\n");

    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    if (input.begin()) {
        Serial.println("IGA initialized successfully.");
    } else {
        Serial.println("Failed to initialize IGA");
        exit(0);
    }
}

void loop() {
    if (input.getData(var1, var2)) {
        Serial.printf(s, var1, var2);
    } else {
        Serial.println("Failed to get IGA data.");
    }

    delay(1000);
}
