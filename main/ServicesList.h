
#ifndef ServicesList_H
#define ServicesList_H

#include "LedSwitch.h"
#include <vector>

class ServicesList {
  public:
  
  static std::vector<Switch*> switches;
  static void setupServices();
};

#endif
