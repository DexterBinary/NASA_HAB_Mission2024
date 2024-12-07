#include "IGA.h"

// SGP30 I2C Address
#define SGP30_I2C_ADDRESS 0x58

// SGP30 Commands
#define SGP30_INIT_CMD 0x2003
#define SGP30_MEASURE_CMD 0x2008

IGA::IGA() {
}

bool IGA::begin() {
    // Wire.begin();
    if (!wireping(SGP30_I2C_ADDRESS)) return false;
    // Initialize the SGP30 sensor
    writeCommand(SGP30_INIT_CMD);
    delay(100);
    return true;  // Return true for successful initialization (add error handling if needed)
}

void IGA::writeCommand(uint16_t command) {
    Wire.beginTransmission(SGP30_I2C_ADDRESS);
    Wire.write(command >> 8);
    Wire.write(command & 0xFF);
    Wire.endTransmission();
}

bool IGA::wireping(uint8_t address) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    if (error == 0) return true;
    return false;
}

bool IGA::readData(uint16_t data[], uint8_t numWords) {
    Wire.requestFrom(SGP30_I2C_ADDRESS, numWords * 3);  // SGP30 returns 3 bytes for each 16-bit word

    for (uint8_t i = 0; i < numWords; ++i) {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
        Wire.read();  // Checksum byte, not used

        data[i] = ((uint16_t)msb << 8) | lsb;
    }

    return true;  // Return true for successful read (add error handling if needed)
}

bool IGA::getData(uint16_t &co2, uint16_t &tvoc) {
    writeCommand(SGP30_MEASURE_CMD);
    delay(12);  // Measurement delay for SGP30

    uint16_t data[2];
    if (!readData(data, 2))
        return false;

    co2 = data[0];
    tvoc = data[1];
    return true;  // Return true for successful read (add error handling if needed)
}

bool IGA::getJSON(JsonDocument &doc) {
    if (!wireping(SGP30_I2C_ADDRESS)) {
        uninitialized = true;
        return false;
    }
    if (uninitialized) {
        uninitialized = false;
        begin();
    }

    writeCommand(SGP30_MEASURE_CMD);
    delay(12);  // Measurement delay for SGP30

    uint16_t data[2];
    if (!readData(data, 2))
        return false;

    JsonArray dataArray = doc["IGA"].to<JsonArray>();

    JsonObject dataSet = dataArray.add<JsonObject>();  // First data se
    dataSet["name"] = "TVOC";
    dataSet["value"] = data[1];
    dataSet["unit"] = "ppb";

    dataSet = dataArray.add<JsonObject>();  // Subsequent data sets
    dataSet["name"] = "CO2";
    dataSet["value"] = data[0];
    dataSet["unit"] = "ppm";

    return true;
}
