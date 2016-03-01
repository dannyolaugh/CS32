//
//  Player.h
//  Proj 1 Cs32 again
//
//  Created by Daniel O'Laughlin on 1/8/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef __Proj_1_Cs32_again__Player__
#define __Proj_1_Cs32_again__Player__


class Pit;

class Player
{
public:
    // Constructor
    Player(Pit *pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   move(int dir);
    void   setDead();
    
private:
    Pit*  m_pit;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

#endif /* defined(__Proj_1_Cs32_again__Player__) */
