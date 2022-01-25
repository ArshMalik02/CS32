#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    m.erase("Ethel");
    Map result;
    reassign(m, result);
    result.dump();
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
