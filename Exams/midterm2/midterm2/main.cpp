#include <iostream>
#include <vector>
#include <list>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE smallbig FUNCTION

bool smallbig(vector<int> &c1, list<int> &c2)
{
    if (c1.size()!=c2.size())
        return false;
    list<int>::iterator it;
    it = c2.begin();
    for (int i = 0; i!=c1.size()&&it!=c2.end(); i++)
    {
        if ((*it)<c1[i])
        {
            int temp = c1[i];
            c1[i] = *it;
            *it = temp;
        }
        
        it++;
    }
    return true;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE smallbig FUNCTION

int main()
{
    vector<int> v;
    list<int> li;
    assert(smallbig(v, li));
    
    int x[4] = { 7, -5, 3, 6 };
    int y[4] = { 4,  1, 3, 2 };
    int expectx[4] = { 4, -5, 3, 2 };
    int expecty[4] = { 7,  1, 3, 6 };
    vector<int> small(x, x+4);
    list<int> big(y, y+4);
    assert(smallbig(small, big));
    vector<int> expectsmall(expectx, expectx+4);
    list<int> expectbig(expecty, expecty+4);
    assert(small == expectsmall  &&  big == expectbig);

    list<int> big2(y, y+3);
    assert( ! smallbig(small, big2));  // different num of elements

    cout << "All tests succeeded" << endl;
}
