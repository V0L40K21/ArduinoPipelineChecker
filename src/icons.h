#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

const uint8_t ICON_GIT[] PROGMEM = {
    0xc0, 0xf8, 0xff, 0xfe, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xf0, 0xfe, 0xff, 0xf8, 0xc0, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x3f,
    0x7f, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x03};

const uint8_t ICON_SUCCESS[8] PROGMEM = {0x10, 0x30, 0x60, 0x30,
                                         0x18, 0x0c, 0x06, 0x02};

const uint8_t ICON_FAILED[8] PROGMEM = {0x81, 0xc3, 0x66, 0x3c,
                                        0x18, 0x3c, 0x66, 0xc3};

const uint8_t ICON_RUNNING[8] PROGMEM = {0x18, 0x18, 0x18, 0x18,
                                         0x18, 0x7e, 0x3c, 0x18};

inline const uint8_t *getStatusIcon(const String &status) {
  String s = status;
  s.toLowerCase();

  if (s == "success" || s == "passed")
    return ICON_SUCCESS;
  if (s == "failed")
    return ICON_FAILED;
  if (s == "running")
    return ICON_RUNNING;
  if (s == "pending" || s == "waiting_for_resource")
    return ICON_RUNNING;
  if (s == "canceled")
    return ICON_FAILED;
  if (s == "skipped" || s == "manual" || s == "unknown")
    return ICON_FAILED;

  return ICON_FAILED;
}

void printLogo();
void myClear();
void printPipes(JsonArray arr);