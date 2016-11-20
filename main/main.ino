#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "printer.h"
#include "config_salon.h"
#include "ServicesList.h"

void mqttCallback(const char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient mqtt(mqtt_server, 1883, mqttCallback, espClient);


void setup() {
  Serial.begin(115200);
  setupWifi();
  ServicesList::setupServices();

  connectMqtt();
}

void mqttCallback(const char* topic, byte* payload, unsigned int length) {
  char stringPayload[128];
  memcpy(stringPayload, payload, length);
  stringPayload[length] = 0; //null terminate

  aprintf("%s : %s\n", topic, stringPayload);

  for (auto aSwitch : ServicesList::switches) {
    auto switchTopic = (std::string(mqtt_client_name) + "/switch/" + aSwitch->getName()).c_str();
    if (strcmp(switchTopic, topic) == 0) {
      aSwitch->set(strcmp(stringPayload, "ON") == 0); 
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

  for (auto aSwitch : ServicesList::switches) {
    aSwitch->setup();

    auto topic = (std::string(mqtt_client_name) + "/switch/" + aSwitch->getName()).c_str();
    aprintf("Subscribing to %s\n", topic);
    if (!mqtt.subscribe(topic)) {
      aprintf("Something wrong happened");
    }
  }
}

void loop() {
  if (!mqtt.connected()) {
    connectMqtt();
  }
  mqtt.loop();
}
