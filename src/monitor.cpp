#include "project.h"

void updateDisplay() {
  tft.fillScreen(TFT_BLACK);

  // Überschrift
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(10, 5);
  tft.setTextSize(1);
  tft.print("PM2.5 Sensor Monitor");
  tft.drawLine(10, 20, 310, 20, TFT_WHITE);

  // PM1.0
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(10, 35);
  tft.print("PM1.0 (ATM):");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 52);
  tft.setTextSize(2);
  tft.print(pmValues.pm1_0_atm);
  tft.setCursor(90, 52);
  tft.setTextSize(1);
  tft.print("ug/m3");

  // PM2.5
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(10, 80);
  tft.print("PM2.5 (ATM):");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 97);
  tft.setTextSize(2);
  tft.print(pmValues.pm2_5_atm);
  tft.setCursor(90, 97);
  tft.setTextSize(1);
  tft.print("ug/m3");

  // PM10
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(10, 125);
  tft.print("PM10 (ATM):");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 142);
  tft.setTextSize(2);
  tft.print(pmValues.pm10_atm);
  tft.setCursor(90, 142);
  tft.setTextSize(1);
  tft.print("ug/m3");

  // Luftqualität
  tft.setCursor(10, 175);
  tft.setTextSize(1);
  if (pmValues.pm2_5_atm <= 12) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.print("Air Quality: GOOD");
  } else if (pmValues.pm2_5_atm <= 35) {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.print("Air Quality: MODERATE");
  } else if (pmValues.pm2_5_atm <= 55) {
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.print("Air Quality: UNHEALTHY (Sensitive)");
  } else if (pmValues.pm2_5_atm <= 150) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("Air Quality: UNHEALTHY");
  } else {
    tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
    tft.print("Air Quality: HAZARDOUS!");
  }

  // Batterie und WiFi Status
  unsigned int charge = lipo.soc();
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(10, 215);
  tft.setTextSize(1);
  tft.print("Battery: ");
  tft.print(charge);
  tft.print("% | WiFi: ");
  tft.print(wifi_connected ? "OK" : "NO");

  // WHO Guideline
  tft.setCursor(10, 235);
  tft.print("WHO Guideline: <5 ug/m3");
}