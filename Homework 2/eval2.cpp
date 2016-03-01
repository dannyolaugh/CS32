//
//  eval2.cpp
//  cs32 homework 2
//
//  Created by Daniel O'Laughlin on 2/2/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#include <stack>
#include <iostream>
#include <string>
using namespace std;

bool isValid(const string& infix )
{
    int closedParenCount = 0;  //make sure parenthesis match up
    int openParenCount = 0;
    int lastClosedParen = 0;
    int positionOfClosedParen = 0;
    int positionOfOpenParen = 0;
    
    //    for(int j = 0; j < infix.size(); j++)
    //    {
    //        if(!isalpha(infix[j]) || infix[j] != '(' || infix[j] != ')' || infix[j] != '|' || infix[j] != '&' || infix[j] != '!' || infix[j] != ' ')
    //            return false;
    //    }
    
    
    for(int i = 0; i < infix.size(); i++)
    {
        if(infix[i] == '(')
        {
            positionOfOpenParen = i;
            openParenCount++;
            int x;
            for(x = lastClosedParen; x < infix.size(); x++) //start loop from the paren
            {
                if(infix[x] == ')')
                {
                    positionOfClosedParen = x;
                    if(positionOfClosedParen > positionOfOpenParen)
                    {
                        closedParenCount++;
                        break;
                    }
                }
            }
            lastClosedParen = x+1; //this might run out of bounds
            if(openParenCount != closedParenCount)
                return false;
            
        }
        
        if(infix[i] == '(' && i != 0)
        {
            if(i == infix.size()-1)
                return false;
            if(infix[i-1] == ')' || isalpha(infix[i-1]))
                return false;
        }
        if(infix[i] == ')')
        {
            if(i == 0)
                return false;
            if(infix[i-1] == '|' || infix[i-1] == '&' || infix[i-1] == '!' || infix[i-1] == '(')
                return false;
        }
        
        if(infix[i] == '&' || infix[i] == '|')
        {
            if(i == 0)
                return false;
            if(i == infix.size()-1)
            {
                return false;
            }
            if(infix[i-1] == '|' || infix[i-1] == '&' || infix[i-1] == '!' || infix[i-1] == '(')
                return false;
        }
        if(infix[i] == '!')
        {
            if(i == infix.size()-1)
                return false;
        }
        
        if(isdigit(infix[i]) && i != 0)
        {
            if(infix[i-1] == ')' || isdigit(infix[i-1]))
                return false;
        }
        
        
        
        
        closedParenCount = 0;   //reset these and check the numbers to make sure the parenthesis match up
        openParenCount = 0;
        for(int r = 0; r < infix.size(); r++)
        {
            if(infix[r] == '(')
                openParenCount++;
            if(infix[r] == ')')
                closedParenCount++;
        }
        if(openParenCount != closedParenCount)
            return false;
        
        
        
    }
    return true;
}

int main()
{
    string infix = "4 5";    //i can put a * and it still works //should this be true or false "(3&2)//(2&3)"
    if(isValid(infix) == 0)  //must have an operator between parenthesis
        cerr << "not valid" << endl;
    else
        cerr << "valid" << endl;
}

//check for whitespace and characters other than the numbers and ! & |

