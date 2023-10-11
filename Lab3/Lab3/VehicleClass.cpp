#include <iostream>
#include "VehicleClass.h"

const char* Vehicle::getName()
{
    return name;
}

void Vehicle::setName(const char* newName)
{
    strncpy_s(name, newName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}