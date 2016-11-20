#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "printer.h"
#include "config.h"

WiFiClient espClient;
PubSubClient mqtt(espClient);

void setup() {
  setupSerial();
//  setup_wifi();
//  mqtt.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  aprintf("Connecting to %s\n", wifi_ssid);

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
    
    if (mqtt.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      aprintf("connected\n");
    } 
    else {
      aprintf("failed, rc=%s trying again in 5 seconds", mqtt.state());
      delay(5000);
    }
  }
}

void loop() {
//  if (!mqtt.connected()) {
//    connectMqtt();
//  }
//  mqtt.loop();

  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);
}
