#include "http.h"
#include "env.h"
#include "icons.h"
#include "wifi_manager.h"

#include <ArduinoJson.h>
#include <GyverHTTP.h>
#include <GyverOLED.h>
#include <WiFi.h>

extern GyverOLED<SSD1306_128x64> oled;

static WiFiClient wifiClient;

static ghttp::Client http(wifiClient, SERVER_HOST, SERVER_PORT);

void http_request() {
  if (!http.connect()) {
    myClear();
    oled.println("HTTP connect ERR");
    oled.update();
    return;
  }
  if (!http.request(SERVER_PATH)) {
    myClear();
    oled.println("req send FAIL");
    oled.update();
    return;
  }
  auto resp = http.getResponse();
  if (!resp) {
    myClear();
    oled.println("No response");
    oled.update();
    return;
  }
  int code = resp.code();
  if (code != 200) {
    myClear();
    oled.print("HTTP code: ");
    oled.println(code);
    oled.update();
    return;
  }
  String body = resp.body().readString();
  JsonDocument doc;
  auto err = deserializeJson(doc, body);
  if (err) {
    myClear();
    oled.println("JSON ERR");
    oled.update();
    return;
  }
  JsonArray arr = doc.as<JsonArray>();
  printPipes(arr);
}