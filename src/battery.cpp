#include "project.h"

void setupBQ27441(void) {
  if (!lipo.begin()) {
    Serial.println("Error: Unable to communicate with BQ27441.");
    tft.setTextColor(TFT_RED);
    tft.setCursor((320 - tft.textWidth("Battery Not Initialised!")) / 2, 120);
    tft.print("Battery Not Initialised!");
    while (1);
  }
  lipo.setCapacity(BATTERY_CAPACITY);
}