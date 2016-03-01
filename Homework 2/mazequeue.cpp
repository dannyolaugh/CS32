//
//  queue.cpp
//  cs32 homework 2
//
//  Created by Daniel O'Laughlin on 1/31/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//
#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Coord

{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr,sc));
    while(!coordQueue.empty())
    {
        Coord frontOfQueue = coordQueue.front();
        cerr << frontOfQueue.r() << " " << frontOfQueue.c() << " popped" << endl;
        coordQueue.pop();
        
        if(frontOfQueue.r() == er && frontOfQueue.c() == ec)
            return true;
        if(maze[frontOfQueue.r()-1][frontOfQueue.c()] == '.')
            coordQueue.push(Coord(frontOfQueue.r()-1,frontOfQueue.c()));
        
        if(maze[frontOfQueue.r()][frontOfQueue.c()+1] == '.')
            coordQueue.push(Coord(frontOfQueue.r(),frontOfQueue.c()+1));
        
        if(maze[frontOfQueue.r()+1][frontOfQueue.c()] == '.')
            coordQueue.push(Coord(frontOfQueue.r()+1,frontOfQueue.c()));
        
        if(maze[frontOfQueue.r()][frontOfQueue.c()-1] == '.')
            coordQueue.push(Coord(frontOfQueue.r(),frontOfQueue.c()-1));
        
        
        maze[frontOfQueue.r()][frontOfQueue.c()] = 'X';
        
        
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

