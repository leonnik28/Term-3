#ifndef DUMPTRUCKCLASS
#define DUMPTRUCKCLASS
#include "FreightClass.h"
class DumpTruck : public Freight
{
public:
    enum typeEngine
    {
        v4 = 4,
        v6 = 6,
        v8 = 8,
        v12 = 12,
    } engine;

    enum typeEngine getEngine();
    void setEngine(typeEngine newEngine);
};

#endif