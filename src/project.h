#include <Seeed_HM330X.h>
#include <TFT_eSPI.h>
#include <SparkFunBQ27441.h>
#include <Wire.h>
#include <rpcWiFi.h>
#include <Arduino.h>

//monitor
TFT_eSPI tft;

//sensor
HM330X sensor;

//spezifisch für unsere battery
const unsigned int BATTERY_CAPACITY = 650;
