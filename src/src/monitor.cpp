#include "../project.h"

void updateDisplay(PMValues *pmValues) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);




  // PM1.0
  tft.setCursor(10, 10);
  tft.print("PM1.0:");
  tft.setCursor(100, 10);
  tft.print(pmValues->pm1_0_atm);
  tft.setCursor(160, 10);
  tft.print("ug/m3");

  // PM2.5
  tft.setCursor(10, 40);
  tft.print("PM2.5:");
  tft.setCursor(100, 40);
  tft.print(pmValues->pm2_5_atm);
  tft.setCursor(160, 40);
  tft.print("ug/m3");

  // PM10
  tft.setCursor(10, 70);
  tft.print("PM10:");
  tft.setCursor(100, 70);
  tft.print(pmValues->pm10_atm);
  tft.setCursor(160, 70);
  tft.print("ug/m3");

  // Luftqualität
  tft.setCursor(10, 100);
  if (pmValues->pm2_5_atm <= 12) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.print("Air Quality: GOOD");
  } else if (pmValues->pm2_5_atm <= 35) {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.print("Air Quality: MODERATE");
  } else if (pmValues->pm2_5_atm <= 55) {
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.print("Air Quality: UNHEALTHY (Sensitive)");
  } else if (pmValues->pm2_5_atm <= 150) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("Air Quality: UNHEALTHY");
  } else {
    tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
    tft.print("Air Quality: HAZARDOUS!");
  }

  // Batterie und WiFi Status
  unsigned int charge = lipo.soc();
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(10, 225);
  tft.setTextSize(1);
  tft.print("Battery: ");
  tft.print(charge);
  tft.print("% WiFi: ");
  tft.print(wifi_connected ? "OK" : "NO");

  // WHO Guideline
  tft.print("WHO Guideline: <5 ug/m3");
}