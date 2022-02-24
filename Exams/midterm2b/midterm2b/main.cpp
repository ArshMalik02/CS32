#include <iostream>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE product FUNCTION

int productHelper(int a, int b, int countb, int total)
{
    if (countb==0)
        return total;
    return productHelper(a, b, countb-1, total+a);
}
int product(int a, int b)
{
    if (a==0 || b==0)
        return 0;
    return productHelper(a, b, b, 0);
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE product FUNCTION

int main()
{
    assert(product(7, 5) == 35);
    assert(product(-4, 8) == -32);
    assert(product(2, 6) == 12);
    cout << "All tests succeeded" << endl;
}
