#include "project.h"
#include "env.h"


TFT_eSPI tft;
HM330X sensor;
const unsigned int BATTERY_CAPACITY = 650;

const char* ssid = WIFI_SSID;      
const char* password = WIFI_PASS;  

const char* server_ip = SERVER_URL; //nodered ip
const int server_port = SERVER_PORT;

// buffer sensordaten
u8 buf[30];

PMValues pmValues;
bool wifi_connected = false;

void setup() { 

  setupBQ27441();
  sensor.init();
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  connectToWiFi();

  delay(1000);
}

void loop() {
  if (sensor.read_sensor_value(buf, 29)) {
    delay(1000);
    return;
  }

  parse_pm_data(buf, &pmValues);
  updateDisplay(&pmValues);


  if (!wifi_connected) {
    connectToWiFi();
  }

  char message[256];
  sprintf(message, "{\"PM1.0\": %d, \"PM2.5\": %d, \"PM10\": %d, \"Battery\": %d}",
          pmValues.pm1_0_atm,
          pmValues.pm2_5_atm,
          pmValues.pm10_atm,
          lipo.soc());
  sendMQTT(message);

  delay(1000);
}