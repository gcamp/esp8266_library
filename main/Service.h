
#ifndef Service_H
#define Service_H

#include <ESP8266WiFi.h>

enum class ServiceType {
  Switch
};

class Service {
  public:
  Service(ServiceType type);

  String getTopic();

  virtual String getName() = 0;
  virtual void handlePayload(String payload) = 0;

  private:
  ServiceType type;
};

#endif
