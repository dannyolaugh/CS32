//
//  History.cpp
//  Proj 1 Cs32 again
//
//  Created by Daniel O'Laughlin on 1/8/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#include "History.h"
#include "Pit.h"
#include <cctype>   //keep this anyway bc i use isalpha
#include "globals.h"
#include <iostream>


using namespace std;

History::History(int nRows, int nCols)
:m_nRows(nRows), m_nCols(nCols)
{
    for(int i=0; i< nRows; i++)
    {
        for(int j = 0; j < nCols; j++)
            m_pit[i][j] = 0;
    }
    
}

bool History:: record(int r, int c)
{
    if(r > m_nRows || c > m_nCols || r < 1 || c <1)
    {
        return false;
    }
    
    int num = 1;
    
    m_pit[r-1][c-1] = num;
    num++;
    return true;
    
    
    
    
    /* if(!isalpha(m_pit[r-1][c-1]))
     {
     m_pit[r-1][c-1] = 'A';
     }
     else if(m_pit[r-1][c-1] == 'Z')
     {
     }
     
     else
     {
     char letter = m_pit[r-1][c-1];
     letter++;
     m_pit[r-1][c-1] = letter;
     
     }
     
     
     return true;*/
}

void History:: display() const
{
    clearScreen();
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    string matty = ".ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Fill the grid with dots
    for (r = 0; r < m_nRows; r++)
        for (c = 0; c < m_nCols; c++)
            grid[r][c] = '.';
    
    for (r = 0; r < m_nRows; r++)
        for (c = 0; c < m_nCols; c++)
            //if(isalpha(m_pit[r][c]))
            grid[r][c] = matty[m_pit[r][c]];
    
    for (r = 0; r < m_nRows; r++)
    {
        for (c = 0; c < m_nCols; c++)
        {
            cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
    
}