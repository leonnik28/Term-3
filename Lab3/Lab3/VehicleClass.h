#ifndef VEHICLECLASS
#define VEHICLECLASS
class Vehicle
{
protected:
    char name[50];

public:
    Vehicle();
    ~Vehicle();
    const char* getName();
    void setName(const char* newName);
};
#endif