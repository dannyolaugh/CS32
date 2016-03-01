//
//  Snake.h
//  Proj 1 Cs32 again
//
//  Created by Daniel O'Laughlin on 1/8/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef __Proj_1_Cs32_again__Snake__
#define __Proj_1_Cs32_again__Snake__


class Pit;

class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

#endif /* defined(__Proj_1_Cs32_again__Snake__) */
