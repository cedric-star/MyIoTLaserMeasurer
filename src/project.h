#ifndef PROJECT_H
#define PROJECT_H

#include "Seeed_HM330X.h"
#include <TFT_eSPI.h>
#include <SparkFunBQ27441.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "rpcWiFi.h"

//monitor
extern TFT_eSPI tft;

//lasersensor
extern HM330X sensor;
//extern SFE_BQ27441 lipo;

#define FF17 &FreeSans9pt7b
extern const unsigned int BATTERY_CAPACITY;

//wifi
extern const char* ssid;
extern const char* password;
extern const char* server;
extern const int server_port;

//sensor daten butter
extern u8 buf[30];

struct PMValues {
  u16 pm1_0_cf; //cfh werte unter standardisierten bedingungen
  u16 pm2_5_cf; //in industrieanlagen und os verwendet 
  u16 pm10_cf;
  u16 pm1_0_atm; //atm werte unter gegebenen bedingungen
  u16 pm2_5_atm; //halt für draußen und drinnen
  u16 pm10_atm;
};

extern bool wifi_connected;
extern unsigned long last_send_time;
extern const unsigned long send_interval;

void setupBQ27441(void);
void connectToWiFi();
void sendDataToServer(const char* message);
HM330XErrorCode parse_pm_data(u8* data, PMValues *pmValues);
void updateDisplay(PMValues *pmValues);
void sendMQTT(char* msg);

#endif