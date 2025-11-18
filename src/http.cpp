#include "http.h"
#include "env.h"
#include "wifi_manager.h"

#include <ArduinoJson.h>
#include <GyverHTTP.h>
#include <GyverOLED.h>
#include <WiFi.h>

extern GyverOLED<SSD1306_128x64> oled;

static WiFiClient wifiClient;

static ghttp::Client http(wifiClient, SERVER_HOST, SERVER_PORT);

void http_request() {
  if (!wifi_isConnected()) {
    oled.clear();
    oled.home();
    oled.println("WiFi lost...");
    delay(1000);
    wifi_init();
    return;
  }
  if (!http.connect()) {
    oled.clear();
    oled.home();
    oled.println("HTTP connect ERR");
    oled.update();
    return;
  }
  if (!http.request(SERVER_PATH)) {
    oled.clear();
    oled.home();
    oled.println("req send FAIL");
    oled.update();
    return;
  }
  auto resp = http.getResponse();
  oled.clear();
  oled.home();
  if (!resp) {
    oled.println("No response");
    oled.update();
    return;
  }
  int code = resp.code();
  if (code != 200) {
    oled.print("HTTP code: ");
    oled.println(code);
    oled.update();
    return;
  }
  String body = resp.body().readString();
  JsonDocument doc;
  auto err = deserializeJson(doc, body);
  oled.clear();
  oled.home();
  if (err) {
    oled.println("JSON ERR");
    oled.update();
    return;
  }
  JsonArray arr = doc.as<JsonArray>();
  for (int i = 0; i < arr.size() && i < 8; i++) {
    const char *title = arr[i]["title"];
    const char *status = arr[i]["status"];
    oled.print(title);
    oled.print(": ");
    oled.println(status);
    oled.update();
  }
}