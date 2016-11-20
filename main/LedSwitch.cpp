#include "LedSwitch.h"
#include "printer.h"
#include <ESP8266WiFi.h>

void LedSwitch::setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
  set(false);
}

const char* LedSwitch::getName() {
  return "led";
}

void LedSwitch::set(bool value) {
    digitalWrite(LED_BUILTIN, value ? LOW : HIGH); 
}

