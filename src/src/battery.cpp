#include "../project.h"

void setupBQ27441(void) {
  if (!lipo.begin()) {
    Serial.println("Error: Unable to communicate with BQ27441.");
  }
  lipo.setCapacity(BATTERY_CAPACITY);
}