#include <iostream>
#include <cctype>
#include <string>
#include "Multiset.h"
using namespace std;

//why cant i cout

Multiset::Multiset()
{
    //is this the same count that is initialized in the header file
    
    for(int i=0; i < DEFAULT_MAX_ITEMS; i++)
    {
        arr[i].count=0;
    }
    
}

bool Multiset::empty() const
{
    
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(arr[i].count != 0)
            return false;
    }
    
    return true;
}

int Multiset::size() const
{
    int counter = 0;
    for(int i=0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(arr[i].count != 0)
            counter+= arr[i].count;
    }
    return counter;
}

int Multiset::uniqueSize() const
{
    int counter = 0;
    for(int i=0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(arr[i].count != 0)
            counter++;
    }
    return counter;
}

bool Multiset::insert(const ItemType& value)
{
    
    if(uniqueSize() < DEFAULT_MAX_ITEMS)
    {
        
        for(int i = 0; i <= uniqueSize(); i++)
        {
            if(arr[i].variable == value)
            {
                arr[i].count++;
                return true;
            }
            else if(arr[i].count == 0)
            {
                arr[i].variable = value;
                arr[i].count++;
                return true;
            }
        }
    }
    
    if(uniqueSize() == DEFAULT_MAX_ITEMS)
        //should i loop here.....?
    {
        for(int j = 0; j < DEFAULT_MAX_ITEMS; j++)
        {
            if(arr[j].variable == value)
            {
                arr[j].count++;
                return true;
            }
        }
    }
    
    return false;
    
}

int Multiset::erase(const ItemType& value)  //check over this
{
    if(uniqueSize() ==  DEFAULT_MAX_ITEMS)
    {
        for(int i=0; i < uniqueSize(); i++)
        {
            if(arr[i].variable == value && arr[i].count > 1)
            {
                arr[i].count--;
                return 1;
            }
            else if(arr[i].variable == value)
            {
                for(int j = i ; j < uniqueSize() && j != DEFAULT_MAX_ITEMS; j++) //should this just be < or <=
                {
                    arr[j].count = arr[j+1].count;
                    arr[j].variable = arr[j+1].variable;
                }
                arr[uniqueSize()-1].count = 0;
                return 1;
            }
        }
    }
    else
    {
        for(int i=0; i < uniqueSize(); i++)
        {
            if(arr[i].variable == value && arr[i].count > 1)
            {
                arr[i].count--;
                return 1;
            }
            else if(arr[i].variable == value)
            {
                for(int j = i ; j < uniqueSize() && j != DEFAULT_MAX_ITEMS; j++) //should this just be < or <=
                {
                    arr[j].count = arr[j+1].count;
                    arr[j].variable = arr[j+1].variable;
                }
                arr[uniqueSize()].count = 0;
                return 1;
            }
        }
    }
    return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
    if(uniqueSize() == DEFAULT_MAX_ITEMS)
    {
        for(int i = 0; i < uniqueSize(); i++)
        {
            int c = arr[i].count;
            if(arr[i].variable == value)
            {
                for(int j = i; j < uniqueSize() && j != DEFAULT_MAX_ITEMS; j++)
                {
                    arr[j].count = arr[j+1].count;
                    arr[j].variable = arr[j+1].variable;
                }
                arr[uniqueSize()-1].count = 0;
                return c;
            }
        }
    }
    
    else
    {
        for(int i = 0; i < uniqueSize(); i++)
        {
            int c = arr[i].count;
            if(arr[i].variable == value)
            {
                for(int j = i; j < uniqueSize() && j != DEFAULT_MAX_ITEMS; j++)
                {
                    arr[j].count = arr[j+1].count;
                    arr[j].variable = arr[j+1].variable;
                }
                arr[uniqueSize()].count = 0;
                return c;
            }
        }
    }
    
    return 0;
    
}

bool Multiset::contains(const ItemType& value) const
{
    for(int i=0; i < uniqueSize(); i++)
    {
        if(arr[i].variable == value)
            return true;
    }
    return false;
    
}

int Multiset::count(const ItemType& value) const
{
    
    for(int i = 0; i < uniqueSize(); i++)
    {
        if(arr[i].variable == value)
        {
            return arr[i].count;
        }
    }
    return 0;
}

int Multiset::get(int i, ItemType& value) const
{
    if(i >= 0 && i < uniqueSize())
    {
        value = arr[i].variable;
        return arr[i].count;
    }
    return 0;
}

void Multiset::swap(Multiset& other)
{
    for(int i = 0; i < uniqueSize(); i++)
    {
        ItemType tempVariable = arr[i].variable;
        int tempCount = arr[i].count;
        
        arr[i].variable = other.arr[i].variable;
        arr[i].count = other.arr[i].count;
        
        other.arr[i].count = tempCount;
        other.arr[i].variable = tempVariable;
        
    }
    
}

