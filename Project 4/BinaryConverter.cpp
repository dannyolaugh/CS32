#include "provided.h"
#include <string>
#include <vector>
using namespace std;



const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
    string binary;
    string final;
    for(int i = 0; i < numbers.size(); i++)
    {
        binary += convertNumberToBitString(numbers[i]);   //append to binay convertNumberToBitString translation
    }
    
    for(int k = 0; k < binary.size(); k++)
    {
        if(binary[k] == '0')         //if character is '0' append a space
        {
            final += ' ';
        }
        else               //otherwise if its a 1 append a tab
        {
            final += '\t';
        }
        
    }
    
    return final;
}

bool BinaryConverter::decode(const string& bitString,
                             vector<unsigned short>& numbers)
{
    string binary;
    string final;
    unsigned short value = 0;
    
    if(bitString.size()%16 != 0)      //must be a multiple of 16
        return false;
    
    for(int k = 0; k < bitString.size(); k++)
    {
        if(bitString[k] == ' ')    //spaces correspond to 0s while tabs correspond to 1s
        {
            binary += '0';
        }
        else if(bitString[k] == '\t')
        {
            binary += '1';
        }
        else           //if not a tab or space
        {
            return false;
            
        }
    }
    
    for(int i = 0; i < binary.size(); i+=16)
    {
        convertBitStringToNumber(binary.substr(i, 16), value);  //sets value to a number
        numbers.push_back(value);  //put value into numbers vector
    }
    
    return true;
    
}

string convertNumberToBitString(unsigned short number)
{
    string result(BITS_PER_UNSIGNED_SHORT, '0');
    for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
    {
        k--;
        if (number % 2 == 1)
            result[k] = '1';
    }
    return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
    if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
        return false;
    number = 0;
    for (size_t k = 0; k < bitString.size(); k++)
    {
        number *= 2;
        if (bitString[k] == '1')
            number++;
        else if (bitString[k] != '0')
            return false;
    }
    return true;
}
