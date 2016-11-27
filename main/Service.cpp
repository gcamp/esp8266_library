#include "config.h"
#include "Service.h"
#include <ESP8266WiFi.h>

Service::Service(ServiceType type):type(type) {}

String Service::getTopic() {
  auto typeString = "";
  switch(type) {
    case ServiceType::Switch: 
      typeString = "switch";
    break;
    case ServiceType::Sensor: 
      typeString = "sensor";
    break;
  }
  return String("/") + mqtt_client_name + "/" + typeString + "/" + getName();
}

