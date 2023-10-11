#include <iostream>
#include "VehicleClass.h"
#include "FreightClass.h"
#include "DumpTruckClass.h"
#include "PassengerClass.h"
#include "BusClass.h"
#include "TrolleybusClass.h"

int main()
{
    Vehicle vehicle;
    Freight freight;
    DumpTruck dumpTruck;
    Passenger passenger;
    Bus bus;
    Trolleybus trolleybus;

    vehicle.setName("Vehicle");
    freight.setName("Freight");
    dumpTruck.setName("Dump Truck");
    passenger.setName("Passenger");
    bus.setName("Bus");
    trolleybus.setName("Trolleybus");
    freight.setStraight(50.5);
    dumpTruck.setStraight(40.2);
    dumpTruck.setEngine(DumpTruck::v4);
    bus.setCountPeople(44);
    bus.setElectroBus(true);
    trolleybus.setHeating(false);

    std::cout << "Vehicle name: " << vehicle.getName() << std::endl;
    std::cout << "Freight name: " << freight.getName() << ", straight: " << freight.getStraight() << std::endl;
    std::cout << "Dump Truck name: " << dumpTruck.getName() << ", straight: " << dumpTruck.getStraight() << ", engine: " << dumpTruck.getEngine() << std::endl;
    std::cout << "Bus name: " << bus.getName() << ", people: " << bus.getCountPeople() << ", electro: " << bus.isElectroBus() << std::endl;
    std::cout << "Trolleybus name: " << trolleybus.getName() << ", heating: " << trolleybus.hasHeating() << std::endl;

    return 0;
}
