#include <iostream>
#include "DumpTruckClass.h"

DumpTruck::typeEngine DumpTruck::getEngine()
{
    return engine;
}

void DumpTruck::setEngine(typeEngine newEngine)
{
    engine = newEngine;
}