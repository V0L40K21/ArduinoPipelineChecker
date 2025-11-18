#include <Arduino.h>
#include <ArduinoJson.h>
#include <GyverHTTP.h>
#include <GyverOLED.h>
#include <Wifi.h>

#include "env.h"
#include "wifi_manager.h"

GyverOLED<SSD1306_128x64> oled;

void setup() {
  Serial.begin(115200);
  oled.init(21, 22);
  oled.clear();
  oled.home();
  wifi_init();
}

void loop() {
  if (!wifi_isConnected()) {
    oled.clear();
    oled.home();
    oled.println("WiFi lost...");
    delay(1000);
    wifi_init();
    return;
  }
}