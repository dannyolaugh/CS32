#include "provided.h"
#include "HashTable.h"
#include <string>
#include <vector>
using namespace std;

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
    numbers.clear();
    unsigned short C = 0;
    //max load factor of .5
    //C is the smaller of N/2 + 512
    if(s.size()/2 + 512 < 16384)
    {
        C = s.size()/2 + 512;
    }
    else
    {
        C = 16384;
    }
    
    HashTable<string, unsigned short> H(C/2, C);   //create hashtable
    
    
    for(int i = 0; i < 256; i++)
    {
        string s1(1, static_cast<char>(i));
        H.set(s1, i, true);
    }
    
    //delclaration of variables
    int nextFreeID = 256;
    string runSoFar;
    unsigned short x = 0;
    
    for(int j = 0; j < s.size(); j++)
    {
        string c = s.substr(j,1);
        string expandedRun = runSoFar + c;
        
        unsigned short k = 0;
        if(H.get(expandedRun, k))  //if get return true (already there)
        {
            runSoFar = expandedRun;
            continue;
        }
        //otherwise do below
        H.get(runSoFar, x);
        numbers.push_back(x);
        H.touch(runSoFar);     //make it most recent
        runSoFar = "";  //runSoFar is reset
        unsigned short cv = 0;
        H.get(c, cv);
        numbers.push_back(cv);
        
        if(!H.isFull())
        {
            H.set(expandedRun, nextFreeID);   //if H has room add to the table insert expandedRun
            nextFreeID++;    //increment
        }
        else     //if it is full
        {
            string key;
            unsigned short value = 0;
            H.discard(key, value);        //remove least recent value
            H.set(expandedRun, value);   //insert expandedRun
        }
        
        
        
        
    }
    if(!runSoFar.empty())
    {
        H.get(runSoFar, x);
        numbers.push_back(x);
    }
    numbers.push_back(C);
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
    if(numbers.size() == 0)  //if empty
        return false;
    unsigned short C = numbers.back();
    HashTable<unsigned short, string> H(C/2, C);  //load factor
    
    for(int i = 0; i < 256; i++)
    {
        string s1(1, static_cast<char>(i));  //making zero a letter, then a string, making 1 a letter then a string, etc
        H.set(i, s1, true);   //theres 256 nodes that have one character
    }
    
    int nextFreeID = 256;
    string runSoFar;
    string output;
    
    for(int k = 0; k < numbers.size()-1; k++)
    {
        unsigned short us = numbers[k];
        
        if(us < 256)    //this means that the string its mapped to is a single character
        {
            string mappedString;
            H.get(us, mappedString);   //makes mappedstring the string that us is mapped to
            output += mappedString;    //what you are go
            
            if(runSoFar == "")     //if runSoFar is empty
            {
                runSoFar += mappedString;  //concatenate
                continue;
            }
            
            string expandedString;
            expandedString = runSoFar + mappedString;
            
            if(!H.isFull())
            {
                H.set(nextFreeID, expandedString); //if H is not full i wanna put this in the table
                nextFreeID++;    //increment appropriately
            }
            else
            {
                unsigned short key = 0;
                string value;
                H.discard(key, value);
                H.set(key, expandedString);
            }
            runSoFar = "";
            continue;
        }
        
        else
        {
            string mappedString;
            if(!H.get(us, mappedString))
            {
                return false;
            }
            
            H.touch(us);
            output += mappedString;    //they call this string s in the spec
            runSoFar = mappedString;
            continue;
            
            
            
        }
        
    }
    s=output;
    return true;
    
    
}


unsigned int computeHash(int number)
{
    return number;
}

unsigned int computeHash(std::string argument)
{
    int num = 0;
    for(int i = 0; i < argument.size(); i++)
    {
        num += argument[i];
    }
    return num;
}