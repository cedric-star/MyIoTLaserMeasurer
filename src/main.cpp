#include "project.h"
#include "env.h"


// Definitionen der globalen Variablen
TFT_eSPI tft;
HM330X sensor;
const unsigned int BATTERY_CAPACITY = 650;

// WiFi Credentials
const char* ssid = WIFI_SSID;       // Ändern Sie dies
const char* password = WIFI_PASS;  // Ändern Sie dies

// Server information
const char* server_ip = "192.168.178.130";  // IP-Adresse Ihres Servers
const int server_port = 9050;

// Buffer für Sensor-Daten (29 Bytes)
u8 buf[30];

PMValues pmValues;
bool wifi_connected = false;
unsigned long last_send_time = 0;
const unsigned long send_interval = 5000;  // Alle 5 Sekunden senden

void setup() {
  Serial.begin(115200);
  Serial.print("hallowelt");
  setupBQ27441();
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // PM2.5 Sensor initialisieren
  tft.setCursor(10, 40);
  tft.print("Initializing PM2.5 Sensor...");

  if (sensor.init()) {
    Serial.println("HM330X init failed!!!");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setCursor(10, 50);
    tft.print("ERROR!");
    tft.setCursor(10, 80);
    tft.print("Sensor not found!");
    while (1)
      ;
  }

  Serial.println("HM330X init success");

  // WiFi verbinden
  connectToWiFi();
  delay(1000);
}

void loop() {
  if (sensor.read_sensor_value(buf, 29)) {
    Serial.println("HM330X read failed!");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setCursor(10, 50);
    tft.setTextSize(2);
    tft.print("Sensor Error!");
    tft.setCursor(10, 80);
    tft.print("Read failed");
    delay(1000);
    return;
  }

  parse_pm_data(buf);
  updateDisplay();

  // Daten für Server vorbereiten
  char message[256];
  sprintf(message, "PM1.0: %d, PM2.5: %d, PM10: %d, Battery: %d%%",
          pmValues.pm1_0_atm,
          pmValues.pm2_5_atm,
          pmValues.pm10_atm,
          lipo.soc());

  // Nur senden, wenn WiFi verbunden ist und Intervall erreicht
  unsigned long current_time = millis();
  if (wifi_connected) {
    
    last_send_time = current_time;
  } else if (!wifi_connected) {
    // Versuche alle 30 Sekunden erneut zu verbinden
    static unsigned long last_reconnect = 0;
    if (current_time - last_reconnect >= 30000) {
      connectToWiFi();
      last_reconnect = current_time;
    }
  }
  sendMQTT();

  delay(5000);
}