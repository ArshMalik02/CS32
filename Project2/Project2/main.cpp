#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;
    m.insert("a", 1);
    ValueType v;
    assert(m.get("a", v) == true && v == 1);
//    assert(m.get(1, k, v) && k == "c" && v == 123);
//    assert(m.insert("b", 5) && m.size() == 5);
//    assert(m.get(1, k, v) && k == "b" && v == 5);
//    assert(m.get(4, k, v) && k == "x" && v == 1000);
//    assert(m.insert("h", 1) && m.size()==6);
//    assert(m.get(4, k, v) && k == "h" && v == 1);
//    assert(m.insert("z", 999) && m.size()==7);
//    assert(m.get(6, k, v) && k == "z" && v == 999);
//    m.dump();

    
//    assert(m.contains("Fred") && m.size()==1);
//    assert(m.insert("Ethel", 456));
//    assert(m.contains("Fred") && m.contains("Ethel"));
//    assert(m.insert("Fred", 0) == false);
//    assert(m.empty()==false);
//    m = m;
//    assert(m.contains("Fred"));
//    assert(m.contains("Ethel"));
//    assert(m.size() == 2);
    
//    Map m1;
//    m1.insert("John", 789);
//    m1.insert("Akira", 890);
//    m1.insert("Tim", 234);
//    m1 = m;
//    assert(!m1.contains("John") && !m1.contains("Akira") && !m1.contains("Tim"));
//    assert(m1.contains("Fred") && m1.contains("Ethel") && m1.size()==2);
//    Map m1;
//    Map m2 = m1;
//    assert(!m2.contains("Ethel") && m2.size()==0);
    
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
