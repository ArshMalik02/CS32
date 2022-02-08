//
//  main.cpp
//  Homework 1A
//
//  Created by Arsh Malik on 1/12/22.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
                gpas.contains(""));
    string k;
    double v;
    assert(gpas.get(1, k, v)  &&  k == "Ethel");
    assert(gpas.get(0, k, v)  &&  k == "");
    cerr << "GG!" << endl;
}


