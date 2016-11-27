#include "RFSwitch.h"
#include "printer.h"

RFSwitch::RFSwitch(int identifier):Service(ServiceType::Switch),identifier(identifier) {
  switch (identifier) {
    case 1:
    onValue = 4461875;
    offValue = 4461884;
    break;
    case 2:
    onValue = 4462019;
    offValue = 4462028;
    break;
    case 3:
    onValue = 4462339;
    offValue = 4462348;
    break;
    case 4:
    onValue = 4463875;
    offValue = 4463884;
    break;
    case 5:
    onValue = 4470019;
    offValue = 4470028;
    break;
  }

  rcSwitch.setPulseLength(187);
  rcSwitch.enableTransmit(D5);
  rcSwitch.setRepeatTransmit(3);
}
  
String RFSwitch::getName() {
  return "rf_switch_" + String(identifier);
}

void RFSwitch::handlePayload(String payload) {
  int value = (payload == "ON") ? onValue : offValue;

  aprintf("Sending value : %i\n", value);

  rcSwitch.send(value, 24);
  delay(1000); 
}

