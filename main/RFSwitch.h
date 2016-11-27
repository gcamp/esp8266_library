
#ifndef RFSwitch_H
#define RFSwitch_H

#include "Service.h"
#include <RCSwitch.h>

class RFSwitch : public Service {
  public: 
  RFSwitch(int identifier);

  String getName();
  void handlePayload(String payload);

  private:
  int identifier;
  int onValue;
  int offValue;

  RCSwitch rcSwitch;
};

#endif
