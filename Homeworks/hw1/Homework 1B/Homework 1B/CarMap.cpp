//
//  CarMap.cpp
//  Homework 1B
//
//  Created by Arsh Malik on 1/15/22.
//

#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap(){}

bool CarMap::addCar(std::string license)
{
    if (carMap.size()+1 > DEFAULT_MAX_ITEMS || carMap.contains(license))
        return false;
    carMap.insert(license, 0);
    return true;
}

double CarMap::miles(const std::string license) const
{
    double miles;
    if (carMap.get(license, miles))
        return miles;
    return -1;
}

bool CarMap::drive(std::string license, double distance)
{
    if (distance < 0 || !carMap.contains(license))
        return false;
    double d;
    carMap.get(license, d);
    d+=distance;
    carMap.update(license, d);
    return true;
}

int CarMap::fleetSize() const
{
    return carMap.size();
}

void CarMap::print() const
{
    for (int i = 0; i < carMap.size(); i++)
    {
        string k;
        double v;
        carMap.get(i, k, v);
        cout << k << " " << v << endl;
    }
}

