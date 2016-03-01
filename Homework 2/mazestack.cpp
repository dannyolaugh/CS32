//
//  main.cpp
//  cs32 homework 2
//
//  Created by Daniel O'Laughlin on 1/30/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
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
    
    stack<Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    
    while(!coordStack.empty())
    {
        Coord TopOfStack = coordStack.top();
        cerr << TopOfStack.r() << " " << TopOfStack.c() << " popped" << endl;
        coordStack.pop();
        if(TopOfStack.r() == er && TopOfStack.c() == ec)
            return true;
        if(maze[TopOfStack.r()-1][TopOfStack.c()] == '.')     //what if out of bounds
            coordStack.push(Coord(TopOfStack.r()-1,TopOfStack.c()));
        
        if(maze[TopOfStack.r()][TopOfStack.c()+1] == '.')
            coordStack.push(Coord(TopOfStack.r(),TopOfStack.c()+1));
        
        if(maze[TopOfStack.r()+1][TopOfStack.c()] == '.')
            coordStack.push(Coord(TopOfStack.r()+1,TopOfStack.c()));
        
        if(maze[TopOfStack.r()][TopOfStack.c()-1] == '.')
            coordStack.push(Coord(TopOfStack.r(),TopOfStack.c()-1));
        
        
        maze[TopOfStack.r()][TopOfStack.c()] = 'X';
        
        
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

//check for if you dont encounter an open parethesis


