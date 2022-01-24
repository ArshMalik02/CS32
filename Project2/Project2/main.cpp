#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m1;
    assert(m1.insert("Fred", 123));
//    assert(m1.insert("Ethel", 456));
    assert(m1.insert("Lucy", 789));
    Map m2;
    assert(m2.insert("Lucy", 789));
    assert(m2.insert("Ricky", 321));
    Map result;
    m1.dump();
    cerr << endl;
    reassign(m1, result);
    result.dump();
//    assert(m.size() == 2);
//    ValueType v = 42;
//    assert(!m.get("Lucy", v)  &&  v == 42);
//    assert(m.get("Fred", v)  &&  v == 123);
//    v = 42;
//    KeyType x = "Lucy";
//    assert(m.get(0, x, v)  &&
//           ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
//    KeyType x2 = "Ricky";
//    assert(m.get(1, x2, v)  &&
//           ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
//           x != x2);
//    m.dump();
//    Map m1 = m;
//    m1.dump();
//    assert(m1.size()==2);
    
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
