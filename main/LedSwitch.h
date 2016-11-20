
#ifndef LedSwitch_H
#define LedSwitch_H

#include "Service.h"

class LedSwitch : public Service {
  public: 
  LedSwitch();

  String getName();
  void handlePayload(String payload);
};

#endif
