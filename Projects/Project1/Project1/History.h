//
//  History.hpp
//  Project1
//
//  Created by Arsh Malik on 1/7/22.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_track[MAXROWS][MAXCOLS];
    int m_rw;
    int m_cl;
};

#endif /* History_hpp */
