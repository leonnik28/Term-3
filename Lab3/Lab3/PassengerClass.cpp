#include <iostream>
#include "PassengerClass.h"

int Passenger::getCountPeople() {
    return countPeople;
}

void Passenger::setCountPeople(int newCount) {
    countPeople = newCount;
}