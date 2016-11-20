#include "ServicesList.h"
#include "LedSwitch.h"

std::vector<Switch*> ServicesList::switches;

void ServicesList::setupServices() {
  switches.push_back(new LedSwitch());
}

