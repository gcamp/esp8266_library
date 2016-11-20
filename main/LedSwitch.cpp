#include "LedSwitch.h"

LedSwitch::LedSwitch():Service(ServiceType::Switch) {
  pinMode(LED_BUILTIN, OUTPUT); 
  handlePayload("OFF");
}
  
String LedSwitch::getName() {
  return "led";
}

void LedSwitch::handlePayload(String payload) {
    digitalWrite(LED_BUILTIN, (payload == "ON") ? LOW : HIGH); 
}

