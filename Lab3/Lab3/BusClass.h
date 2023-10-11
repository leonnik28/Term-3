#ifndef BUSCLASS
#define BUSCLASS
#include "PassengerClass.h"
class Bus : public Passenger {
protected:
    bool electroBus;

public:
    const char* isElectroBus();
    void setElectroBus(bool newElectroBus);
};
#endif