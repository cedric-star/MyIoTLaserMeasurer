#include "project.h"

void connectToWiFi() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(10, 40);
  tft.print("Connecting to WiFi...");
  tft.setCursor(10, 60);
  tft.print(ssid);

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
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(10, 40);
    tft.print("WiFi Connected!");
    tft.setCursor(10, 60);
    tft.print("IP: ");
    tft.print(WiFi.localIP());
    delay(2000);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setCursor(10, 80);
    tft.print("WiFi Failed!");
    delay(2000);
  }
}

void sendDataToServer(const char* message) {
  if (!wifi_connected) {
    Serial.println("WiFi not connected");
    return;
  }

  WiFiClient client;

  if (client.connect(server_ip, server_port)) {
    Serial.println("Connected to server, sending data...");

    // Nachricht senden
    client.print(message);
    client.print("\n");

    // Optional: Auf Antwort warten
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 2000) {
        Serial.println("Server response timeout");
        break;
      }
      delay(10);
    }

    // Antwort lesen
    while (client.available()) {
      String response = client.readString();
      Serial.print("Server response: ");
      Serial.println(response);

      // Auf Display anzeigen
      tft.fillRect(10, 240, 300, 20, TFT_BLACK);
      tft.setTextColor(TFT_CYAN, TFT_BLACK);
      tft.setCursor(10, 240);
      tft.print("Sent: ");
      tft.print(message);
    }

    client.stop();
    Serial.println("Connection closed");
  } else {
    Serial.println("Connection to server failed");
    tft.fillRect(10, 240, 300, 20, TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setCursor(10, 240);
    tft.print("Server connection failed!");
  }
}