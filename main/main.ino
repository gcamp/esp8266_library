#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "printer.h"
#include "config.h"
#include "ServicesList.h"

void mqttCallback(const char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient mqtt(mqtt_server, 1883, mqttCallback, espClient);

void setup() {
  Serial.begin(115200);
  setupWifi();

  connectMqtt();
}

void mqttCallback(const char* topic, byte* payload, unsigned int length) {
  char stringPayload[128];
  memcpy(stringPayload, payload, length);
  stringPayload[length] = 0; //null terminate

  auto finalPayload = String(stringPayload);

  aprintf("%s : %s\n", topic, stringPayload);

  for (auto service : ServicesList::services) {
    if (service->getTopic() == topic) {
      service->handlePayload(finalPayload);
    }
  }
}

void setupWifi() {
  aprintf("Connecting to %s.", wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    aprintf(".");
  }

  auto localIP = WiFi.localIP();
  aprintf("WiFi connected\nIP address: %P\n", &localIP);
}

void connectMqtt() {
  while (!mqtt.connected()) {
    aprintf("Attempting MQTT connection...");
    
    if (mqtt.connect(mqtt_client_name, mqtt_user, mqtt_password)) {
      aprintf("connected\n");
    } 
    else {
      aprintf("failed, rc=%s trying again in 5 seconds", mqtt.state());
      delay(5000);
    }
  }

  for (auto service : ServicesList::services) {
    auto topic = service->getTopic();
    aprintf("Subscribing to %s\n", topic.c_str());
    if (!mqtt.subscribe(topic.c_str(), 1)) {
      aprintf("Something wrong happened");
    }
  }
}

void loop() {
  if (!mqtt.connected()) {
    connectMqtt();
  }
  mqtt.loop();

  for (auto service : ServicesList::services) {
    service->handleLoop();
  }
}
