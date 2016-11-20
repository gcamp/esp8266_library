
#ifndef LedSwitch_H
#define LedSwitch_H

#include "Switch.h"

class LedSwitch : public Switch {
  public: 

  void setup();

  const char* getName();
  void set(bool value);
};

#endif
