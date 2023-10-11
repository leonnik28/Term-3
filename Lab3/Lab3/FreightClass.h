#ifndef FREIGHTCLASS
#define FREIGHTCLASS
#include "VehicleClass.h"
class Freight : public Vehicle
{
protected:
    double straith;

public:
    double getStraight();
    void setStraight(double newStraight);
};
#endif