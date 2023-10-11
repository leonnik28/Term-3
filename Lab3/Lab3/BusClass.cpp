#include <iostream>
#include "BusClass.h"

const char* Bus::isElectroBus() {
    if (electroBus)
        return "true";
    else
        return "false";
}

void Bus::setElectroBus(bool newElectroBus) {
    electroBus = newElectroBus;
}