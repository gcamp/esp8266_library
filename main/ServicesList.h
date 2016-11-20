
#ifndef ServicesList_H
#define ServicesList_H

#include <vector>
#include "Service.h"

class ServicesList {
  public:
  
  static std::vector<Service*> services;
  static void setupServices();
};

#endif
