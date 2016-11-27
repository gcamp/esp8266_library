#include "ServicesList.h"
#include "LedSwitch.h"
#include "RFReceiver.h"
#include "RFSwitch.h"
#include "config.h"

std::vector<Service*> ServicesList::services = {                          
#ifdef SALON
new LedSwitch(),
new RFReceiver(),
new RFSwitch(1)
//new RFSwitch(2),
//new RFSwitch(3),
//new RFSwitch(4),
//new RFSwitch(5)
#else

#endif
};

