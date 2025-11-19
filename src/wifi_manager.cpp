#include "wifi_manager.h"
#include "icons.h"
#include <GyverOLED.h>

extern GyverOLED<SSD1306_128x64> oled;

void wifi_init() {
  myClear();
  oled.println("Connecting to WiFi");
  oled.update();
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long startAttempt = millis();
  oled.setCursor(0, 4);
  oled.autoPrintln(true);
  while (WiFi.status() != WL_CONNECTED) {
    oled.print("*");
    oled.update();
    delay(100);
    if (millis() - startAttempt > 30000) {
      myClear();
      oled.println("WiFi connection timed out");
      oled.update();
      return;
    }
  }
  oled.autoPrintln(false);

  myClear();
  oled.println("WiFi OK!");
  oled.print("IP: ");
  oled.println(WiFi.localIP().toString());
  oled.update();
  delay(1000);
}

bool wifi_isConnected() { return WiFi.status() == WL_CONNECTED; }