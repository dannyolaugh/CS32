//
//  Game.h
//  Proj 1 Cs32 again
//
//  Created by Daniel O'Laughlin on 1/8/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef __Proj_1_Cs32_again__Game__
#define __Proj_1_Cs32_again__Game__


class Pit;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nSnakes);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

#endif /* defined(__Proj_1_Cs32_again__Game__) */

