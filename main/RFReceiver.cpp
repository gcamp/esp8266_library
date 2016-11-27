#include "RFReceiver.h"

#include "printer.h"

RFReceiver::RFReceiver():Service(ServiceType::Sensor) {
  rcSwitch.enableReceive(D6);
}
  
String RFReceiver::getName() {
  return "rf_receiver";
}

void RFReceiver::handleLoop() {
  if (rcSwitch.available()) {  
    unsigned int value = rcSwitch.getReceivedValue();
    
    if (value == 0) {
      aprintf("Unknown encoding");
    } else {
      aprintf("Received %u / %u bit. Protocol %u / lenght %u\n", value, rcSwitch.getReceivedBitlength(), rcSwitch.getReceivedProtocol(), rcSwitch.getReceivedDelay());
    }

    rcSwitch.resetAvailable();
  }
}

