#include <Arduino.h>
#include <ArduinoJson.h>
#include <GyverHTTP.h>
#include <GyverOLED.h>
#include <Wifi.h>

#include "env.h"
#include "http.h"
#include "icons.h"
#include "wifi_manager.h"

GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;

void setup() {
  Serial.begin(115200);
  oled.init(21, 22);
  oled.clear();
  printLogo();
  wifi_init();
  http_request();
}

void loop() {
  if (!wifi_isConnected()) {
    myClear();
    oled.setCursor(0, 3);
    oled.println("WiFi lost...");
    delay(1000);
    wifi_init();
    return;
  }
}