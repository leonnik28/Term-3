#ifndef TROLLEYBUSCLASS
#define TROLLEYBUSCLASS
#include "PassengerClass.h"
class Trolleybus : public Passenger {
protected:
    bool heating;

public:
    const char* hasHeating();
    void setHeating(bool newHeating);
};
#endif