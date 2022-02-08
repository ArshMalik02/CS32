//
//  History.cpp
//  Project1
//
//  Created by Arsh Malik on 1/7/22.
//

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_cl = nCols;
    m_rw = nRows;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
        {
            m_track[i][j] = 0;
        }
}

bool History::record(int r, int c)
{
    if (r <= 0 || c <= 0 || r > m_rw || c > m_cl)
        return false;
                          
    m_track[r-1][c-1]++;
    return true;
}

void History::display() const
{
    clearScreen();
    for (int i = 0; i < m_rw; i++)
    {
        for (int j = 0; j < m_cl; j++)
        {
            if (m_track[i][j] == 0)
                cout << '.';
            else if (m_track[i][j] >= 26)
            {
                cout << 'Z';
            }
            else
            {
                cout << char(64 + m_track[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}







