#include "project.h"

const char *ID = "mynode";
const char *server = "192.168.178.27"; 
WiFiClient wifiClient;
PubSubClient client(wifiClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void reconnect() {
  if (!client.connected())
  {
    if (client.connect(ID)) {
      Serial.println("connected");
    }
    else {
      Serial.print("failed: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
    }
  }
}


void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    tft.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifi_connected = true;
    delay(1000);
  } else {
    delay(1000);
  }
  client.setServer(server, 1883);
}


void sendMQTT(char* msg) {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  client.publish("/sensors/laser", msg);
  
}
