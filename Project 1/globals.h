//
//  utilities.h
//  Proj 1 Cs32 again
//
//  Created by Daniel O'Laughlin on 1/8/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef __Proj_1_Cs32_again__utilities__
#define __Proj_1_Cs32_again__utilities__


const int MAXROWS = 20;             // max number of rows in the pit
const int MAXCOLS = 40;             // max number of columns in the pit
const int MAXSNAKES = 180;          // max number of snakes allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;


int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();

#endif /* defined(__Proj_1_Cs32_again__utilities__) */