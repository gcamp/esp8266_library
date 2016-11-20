#include "ServicesList.h"
#include "LedSwitch.h"
#include "config.h"

std::vector<Service*> ServicesList::services;

void ServicesList::setupServices() {
#ifdef SALON
  services.push_back(new LedSwitch());
#else

#endif
}

