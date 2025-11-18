#include "wifi_manager.h"
#include <GyverOLED.h>

extern GyverOLED<SSD1306_128x64> oled;

void wifi_init() {
  oled.clear();
  oled.home();
  oled.println("Connecting to WiFi ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED) {
    oled.print(".");
    delay(500);
    if (millis() - startAttempt > 30000) {
      oled.println();
      oled.println("WiFi connection timed out");
      return;
    }
  }

  oled.println();
  oled.println("WiFi OK!");
  oled.print("IP: ");
  oled.println(WiFi.localIP().toString());
  oled.update();
}

bool wifi_isConnected() { return WiFi.status() == WL_CONNECTED; }