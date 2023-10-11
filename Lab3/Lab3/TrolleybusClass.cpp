#include <iostream>
#include "TrolleybusClass.h"

const char* Trolleybus::hasHeating() {
    if (heating)
        return "true";
    else
        return "false";
}

void Trolleybus::setHeating(bool newHeating) {
    heating = newHeating;
}