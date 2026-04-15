#ifndef PROJECT_H
#define PROJECT_H

#include "Seeed_HM330X.h"
#include <TFT_eSPI.h>
#include <SparkFunBQ27441.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "rpcWiFi.h"

// Globale Objekte
extern TFT_eSPI tft;
extern HM330X sensor;
//extern SFE_BQ27441 lipo;

// Konstanten
#define FF17 &FreeSans9pt7b
extern const unsigned int BATTERY_CAPACITY;

// WiFi Credentials
extern const char* ssid;
extern const char* password;

// Server information
extern const char* server_ip;
extern const int server_port;

// Buffer für Sensor-Daten
extern u8 buf[30];

// Strukturen
struct PMValues {
  u16 pm1_0_cf;
  u16 pm2_5_cf;
  u16 pm10_cf;
  u16 pm1_0_atm;
  u16 pm2_5_atm;
  u16 pm10_atm;
};

extern bool wifi_connected;
extern unsigned long last_send_time;
extern const unsigned long send_interval;

// Funktionsdeklarationen
void setupBQ27441(void);
void connectToWiFi();
void sendDataToServer(const char* message);
HM330XErrorCode parse_pm_data(u8* data, PMValues *pmValues);
void updateDisplay(PMValues *pmValues);
void sendMQTT();

#endif