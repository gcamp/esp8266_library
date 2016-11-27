
#ifndef RFReceiver_H
#define RFReceiver_H

#include "Service.h"
#include <RCSwitch.h>

class RFReceiver : public Service {
  public: 
  RFReceiver();

  String getName();
  void handleLoop();

  private:
  RCSwitch rcSwitch;
};

#endif
