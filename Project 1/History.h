//
//  History.h
//  Proj 1 Cs32 again
//
//  Created by Daniel O'Laughlin on 1/8/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef __Proj_1_Cs32_again__History__
#define __Proj_1_Cs32_again__History__

#include "globals.h"

class Pit;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_nRows;
    int m_nCols;
    char m_pit[MAXROWS][MAXCOLS];  //make a two dimensial array resembling pit
    
};

#endif /* defined(__Proj_1_Cs32_again__History__) */
