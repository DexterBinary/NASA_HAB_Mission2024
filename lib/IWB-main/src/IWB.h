#ifndef IWB_H
#define IWB_H

#include <ArduinoJson.h>
#include <Wire.h>

class IWB {
   public:
    IWB();
    bool begin();
    bool getData(double &var1, double &var2);
    bool getJSON(JsonDocument &doc);

   private:
};
#endif  // IWB_H