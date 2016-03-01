//
//  eval.cpp
//  cs32 homework 2
//
//  Created by Daniel O'Laughlin on 1/31/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;



bool valid(const string& infix )
{
    int closedParenCount = 0;  //make sure parenthesis match up
    int openParenCount = 0;
    int lastClosedParen = 0;
    int positionOfClosedParen = 0;
    int positionOfOpenParen = 0;
    
    
    
    
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
            if(infix[i-1] != '(' && infix[i-1] != '&' && infix[i-1] != '|' && infix[i-1] != '!')
                return false;
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


int evaluate(string infix, const bool values[], string& postfix, bool& result)
// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)
{
    if(infix == "")
        return 1;
    
    for (int i = 0; i < infix.length(); i++) {
        if(infix[i] == ' ')
        {
            infix.erase(i, 1);
            i--;
        }
    }
    if(valid(infix) == 0)
        return 1;
    //Initialize postfix to empty
    postfix = "";
    //Initialize the operator stack to empty
    stack<char> OperatorBruh;
    
    //For each character ch in the infix string
    for(int i = 0; i < infix.size(); i++)
    {
        switch (infix[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // append ch to end of postfix
                postfix += infix[i];
                break;
            case '(':
                //push ch onto the operator stack
                OperatorBruh.push(infix[i]);
                break;
            case ')':
                while(!OperatorBruh.empty())
                {
                    if(OperatorBruh.top() == '(')
                    {
                        OperatorBruh.pop();
                        break;
                    }
                    else
                    {
                        postfix += OperatorBruh.top();
                        OperatorBruh.pop();
                    }
                }
                //            if(!OperatorBruh.empty() && OperatorBruh.top() == '!')
                //            {
                //                postfix += OperatorBruh.top();
                //                OperatorBruh.pop();
                //            }
                break;
                
            case '&':
            case '|':
            case '!':
                while(!OperatorBruh.empty() && OperatorBruh.top() != '(')
                {
                    char top = OperatorBruh.top();
                    if(top == '&' || top == '|' || top == '!')
                    {
                        if(top >= infix[i])
                            break;
                    }
                    postfix += top;
                    OperatorBruh.pop();
                    
                }
                
                OperatorBruh.push(infix[i]);
                
                break;
            default:
                return 1;
                
        }
    }
    
    while(!OperatorBruh.empty())
    {
        postfix += OperatorBruh.top();
        OperatorBruh.pop();
    }
    
    stack<bool> OperandBae;
    
    //	For each character ch in the postfix string
    //    if ch is an operand
    //        push the value that ch represents onto the operand stack
    //	    else // ch is a binary operator
    //	        set operand2 to the top of the operand stack
    //            pop the stack
    //	        set operand1 to the top of the operand stack
    //            pop the stack
    //            apply the operation that ch represents to operand1 and
    //            operand2, and push the result onto the stack
    //            When the loop is finished, the operand stack will contain one item,
    //            the result of evaluating the expression
    
    for(int x = 0; x < postfix.size(); x++)
    {
        
        if(isdigit(postfix[x]))
        {
            OperandBae.push(values[postfix[x]-48]);
        }
        else if(postfix[x] != '!')
        {
            bool operand2 = OperandBae.top();
            OperandBae.pop();
            bool operand1 = OperandBae.top();
            OperandBae.pop();
            
            
            if(postfix[x] == '|')
                OperandBae.push(operand1 || operand2);//push operand 2 && operand 1
            else if(postfix[x] == '&')
                OperandBae.push(operand1 && operand2);
            
            
        }
        else
        {
            bool operand1 = OperandBae.top();
            OperandBae.pop();
            OperandBae.push(!operand1);
        }
        
    }
    result = OperandBae.top();
    return 0;
}

int main()
{
    
    // checks the valid function
    assert(valid("2| 3") == true);
    // assert(valid("") == false);
    assert(valid("45") == false);
    assert(valid("01") == false);
    assert(valid("()") == false);
    assert(valid("2(9|8)") == false);
    assert(valid("2(&8)") == false);
    assert(valid("(6&(7|7)") == false);
    assert(valid("4|!3&(0&3)") == true);
    // assert(valid("") == false);
    assert(valid("9 ") == true);
    assert(valid("((9))") == true);
    assert(valid("2|3") == true);
    assert(valid("2") == true);
    assert(valid("(3)") == true);
    assert(valid("2&(3)") == true);
    assert(valid("0&!9") == true);
    assert(valid("!(7|8)") == true);
    assert(valid("!7|8") == true);
    assert(valid("6|4&5") == true);
    assert(valid("1&!(9|1&1|9) | !!!(9&1&9)") == true);
    assert(valid("!!!!!!3") == true);
    assert(valid(("(())")) == false);
    
    cout << "Passed all tests" << endl;
    
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate(")()(", ba, pf, answer) == 1);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("2", ba, pf, answer) == 0 && answer);
    assert(evaluate("(3)", ba, pf, answer) == 0 && !answer);
    assert(evaluate("2&(3)", ba, pf, answer) == 0 && !answer);
    assert(evaluate("0 & !9", ba, pf, answer) == 0 && answer);
    assert(evaluate("!(7|8)", ba, pf, answer) == 0 && !answer);
    assert(evaluate("!7|8", ba, pf, answer) == 0 && answer);
    assert(evaluate("6|4&5", ba, pf, answer) == 0 && answer);
    assert(evaluate("1&!(9|1&1|9) | !!!(9&1&9)", ba, pf, answer) == 0 && answer);
    assert(evaluate("!!!!!!3&2", ba, pf, answer) == 0 && !answer); // problem when the infix starts with multiple !
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0 &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("(())", ba, pf, answer) == 1);
    assert(evaluate(") ( )(", ba, pf, answer) == 1);
    assert(evaluate("!4", ba, pf, answer) == 0  &&  pf == "4!"  &&  answer);
    assert(evaluate("! ! 4", ba, pf, answer) == 0  &&  pf == "4!!"  &&  !answer);
    assert(evaluate("!!!!!!!4", ba, pf, answer) == 0  &&  pf == "4!!!!!!!"  &&  answer);
    assert(evaluate("!!!!!!!4 | !!!!9", ba, pf, answer) == 0 && pf == "4!!!!!!!9!!!!|" && answer);
    assert(evaluate("(!!!)(!!2)", ba, pf, answer) == 1);
    assert(evaluate("!(!!!1&(6|3))", ba, pf, answer) == 0 && pf== "1!!!63|&!" && answer);
    assert(evaluate("6&3|!1", ba, pf, answer) == 0  && pf == "63&1!|" && !answer);
    assert(evaluate("6&3|1", ba, pf, answer) == 0  && answer);
    assert(evaluate("(   3) !", ba, pf, answer) == 1);
    assert(evaluate("(!8)&(!4)", ba, pf, answer) == 0 && pf== "8!4!&" && !answer);
    assert(evaluate("(1!&)", ba, pf, answer) == 1);
    assert(evaluate("(||!&!!)", ba, pf, answer) == 1);
    assert(evaluate("18!4", ba, pf, answer) == 1);
    assert(evaluate("(!!!6&(4|!8&6))", ba, pf, answer) == 0 && !answer);
    assert(evaluate("(!!!6&(4|8&6))", ba, pf, answer) == 0 && !answer );
    assert(evaluate("(!7&!6|!!!9)", ba, pf, answer) == 0  && answer);
    assert(evaluate("(6&4)!8)", ba, pf, answer) == 1);
    
    
    
    
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}






