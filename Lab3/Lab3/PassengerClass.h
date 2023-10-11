#ifndef PASSENGERCLASS
#define PASSENGERCLASS
#include "VehicleClass.h"
class Passenger : public Vehicle {
protected:
    int countPeople;

public:
    int getCountPeople();
    void setCountPeople(int newCount);
};
#endif