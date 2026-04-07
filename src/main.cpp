#include "project.h"

TFT_eSPI tft;
int i = 0;

// put function declarations here:

void setup() {
  Serial.begin(115200);
  Serial.print("hallowelt");
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // PM2.5 Sensor initialisieren
  tft.setCursor(10, 40);
  tft.print("Initializing PM2.5 Sensor...");

  // put your setup code here, to run once:
}

void loop() {
  if (i < 3) {
    tft.print("hyyyy");
    i++;
  }
  

  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}