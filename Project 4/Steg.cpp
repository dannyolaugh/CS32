#include "provided.h"
#include <string>
#include <iostream>
using namespace std;


bool Steg::hide(const string& hostIn, const string& msg, string& hostOut)
{
    if(hostIn.size() == 0)
        return false;
    
    vector<unsigned short> msgNums;
    Compressor::compress(msg, msgNums);
    string linesAndDashes = BinaryConverter::encode(msgNums);
    string copy;
    int counterOfSpaces = 0;
    int startingIndex = 0;
    int counterOfChars = 0;
    int numOfLines = 0;
    
    // AA\na\n
    for(int i = 0; i < hostIn.size(); i++)    //iterate through hostIn
    {
        if(hostIn[i] == '\t' || hostIn[i] == ' ')    //if space or tab
        {
            for(int j = i; j < hostIn.size(); j++)
            {
                if(hostIn[j] == '\n')  //if newline concatinate the string
                {
                    copy += hostIn.substr(startingIndex, counterOfChars);
                    startingIndex = startingIndex + counterOfChars + counterOfSpaces;  //update starting index for next concatination
                    numOfLines++;
                    i++;
                    counterOfChars = 1;
                    break;
                }
                else if (hostIn[j] == '\r')
                {
                    if(i+1 == hostIn.size() || hostIn[i+1] != '\n')
                        return false;
                    
                    copy += hostIn.substr(startingIndex, counterOfChars);
                    startingIndex = startingIndex + counterOfChars + counterOfSpaces;  //update starting index for next concatination
                    numOfLines++;
                    i+=2;
                    counterOfChars = 2;
                    break;
                }
                else if (j == hostIn.size()-1)
                {
                    copy += hostIn.substr(startingIndex, counterOfChars);
                    numOfLines++;
                    startingIndex = startingIndex + counterOfChars + counterOfSpaces;  //update starting index for next concatination
                    i = hostIn.size();
                    counterOfChars = 0;
                }
                else if(hostIn[j] != '\t' && hostIn[j] != ' ')  //break if the thing is a character
                {
                    counterOfChars += counterOfSpaces;
                    break;
                }
                else
                {
                    counterOfSpaces++;     //if it isnt a newline then it must be a space or a tab
                }
            }
            //what if the first thing of a new line is space
            i += counterOfSpaces-1;
            counterOfSpaces = 0;
            
        }
        else if(hostIn[i] == '\n')   //if there were no tabs or spaces before the newline
        {
            copy += hostIn.substr(startingIndex, counterOfChars);
            startingIndex = startingIndex + counterOfChars + counterOfSpaces;     //should it be startingIndex+..???
            counterOfChars = 1;                               //  \n counts as a char
            numOfLines++;                                  //symbolizes end of a line so increment numOfLines
        }
        else if(hostIn[i] == '\r')
        {
            copy += hostIn.substr(startingIndex, counterOfChars);
            startingIndex = startingIndex + counterOfChars + counterOfSpaces;
            i++;
            counterOfChars = 2;
            numOfLines++;
        }
        else
        {
            counterOfChars++;
        }
        
    }
    if(counterOfChars != 0)
    {
        copy += hostIn.substr(startingIndex,counterOfChars);
    }
    
    
    //put the new tabs and spaces into the copy
    int p = 0;
    int HowManyLines = 0;
    string copyWithMessage;
    int num = 0;
    int startingPoint;
    for(int j = 0; j < copy.size(); j++)
    {
        if(copy[j] == '\n')
        {
            HowManyLines++;
            startingPoint = p;
            if(HowManyLines <= linesAndDashes.size() % numOfLines)
            {
                for(int i = 0; i <= linesAndDashes.size()/numOfLines + 1; i++)
                {
                    num = i;
                }
            }
            else
            {
                for(int i = 0; i <= linesAndDashes.size()/numOfLines; i++)
                {
                    num = i;
                }
                
            }
            copyWithMessage += linesAndDashes.substr(p,num);
            p+=num;
            // copyWithMessage += copy[j];
        }
        
        else if(copy[j] == '\r')
        {
            HowManyLines++;
            if(HowManyLines <= linesAndDashes.size() % numOfLines)
            {
                for(int i = 0; i <= linesAndDashes.size()/numOfLines + 1; i++)
                {
                    num = i;
                    
                }
            }
            else
            {
                for(int i = 0; i <= linesAndDashes.size()/numOfLines; i++)
                {
                    num = i;
                    
                }
            }
            copyWithMessage += linesAndDashes.substr(p,num);
            p+=num;
            
            copyWithMessage = copyWithMessage + copy[j] + copy[j+1];
            j++;
        }
        
        if(j == copy.size() - 1)
        {
            if(copy[j] != '\n')
                copyWithMessage += copy[j];
            HowManyLines++;
            if(HowManyLines <= linesAndDashes.size() % numOfLines)
            {
                for(int i = 0; i <= linesAndDashes.size()/numOfLines + 1; i++)
                {
                    num = i;
                }
            }
            else
            {
                for(int i = 0; i <= linesAndDashes.size()/numOfLines; i++)
                {
                    num = i;
                    
                }
            }
            copyWithMessage += linesAndDashes.substr(p,num);
            p+=num;
            
        }
        else
        {
            copyWithMessage += copy[j];
        }
    }
    //copyWithMessage	std::__1::string	"<html>        \nQ \tQQ \t  \t  \nBBB       \n   \t\t  \nGG\t \t    \nBBB     \t\t\n \t\t    \nDDD    \t  \nEEE </html      \t"
    hostOut = copyWithMessage;
    return true;
}


bool Steg::reveal(const string& hostIn, string& msg)
{
    string stringOfSpaces;
    int numOfSpaces = 0;
    int startingPosition = 0;
    for(int i = 0; i < hostIn.length(); i++)
    {
        if(hostIn[i] == '\t' || hostIn[i] == ' ')
        {
            for(int j = i; j < hostIn.length(); j++)
            {
                if(hostIn[j] == '\n')
                {
                    startingPosition = i; //if you find a newline obviously you want the starting pos of the substr to be i
                    stringOfSpaces += hostIn.substr(startingPosition, numOfSpaces);
                    break;
                }
                else if(hostIn[j] == '\r')
                {
                    startingPosition = i;
                    stringOfSpaces += hostIn.substr(startingPosition, numOfSpaces);
                    i++;
                    break;
                }
                else if(hostIn[j] == '\t' || hostIn[j] == ' ')
                {
                    numOfSpaces++;
                    if(j == hostIn.length()-1 && hostIn[j] != '\n')
                    {
                        startingPosition = i;
                        stringOfSpaces += hostIn.substr(startingPosition, numOfSpaces);
                        break;
                    }
                }
                else  //if its a character get out of here
                {
                    break;
                }
            }
            i += numOfSpaces;
            numOfSpaces = 0;
            
        }
    }
    vector<unsigned short> v;
    BinaryConverter::decode(stringOfSpaces, v);
    Compressor::decompress(v, msg);
    return true;
}