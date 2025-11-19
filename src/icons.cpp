#include "icons.h"
#include <ArduinoJson.h>
#include <GyverOLED.h>

extern GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
void printLogo() {
  oled.drawBitmap(0, 0, ICON_GIT, 16, 16);
  oled.setCursor(32, 0);
  oled.setScale(2);
  oled.print("GitLab");
  oled.setScale(1);
  myClear();
  oled.update();
}

void myClear() {
  oled.clear(0, 17, 128, 64);
  oled.setCursor(0, 3);
  oled.update();
}

void printPipes(JsonArray arr) {
  myClear();
  for (int i = 0; i < arr.size(); i++) {
    const char *title = arr[i]["title"];
    const char *status = arr[i]["status"];
    uint8_t textRow = 3 + i;
    uint8_t iconY = textRow * 8;
    oled.drawBitmap(116, iconY, getStatusIcon(status), 8, 8);
    oled.setCursor(0, textRow);
    oled.print(i + 1);
    oled.print(".");
    oled.print(title);
  }
  oled.update();
}