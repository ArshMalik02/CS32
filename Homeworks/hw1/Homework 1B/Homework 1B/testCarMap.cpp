//
//  main.cpp
//  Homework 1B
//
//  Created by Arsh Malik on 1/15/22.
//
#include "CarMap.h"
#include <cassert>

int main()
{
    CarMap cars;
    cars.addCar("hr234");
    cars.addCar("hr123");
    cars.addCar("hr345");
    assert(cars.miles("hr123") == 0 && cars.miles("hr234") == 0 && cars.miles("hr345") == 0 && cars.miles("kj") == -1);
    cars.drive("hr234", 5);
    assert(cars.fleetSize() == 3);
    cars.print();
}
