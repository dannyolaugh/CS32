#include <iostream>
#include <cctype>
#include <string>
#include "newMultiset.h"

using namespace std;

Multiset::Multiset(int x)
{
    arr = new MyBoyBrady[x];
    sizeofarray = x;
}

Multiset::~Multiset()
{
    delete [] arr;
}

Multiset::Multiset(const Multiset& other)
{
    // arr = other.arr;   //is this right??? idk
    sizeofarray = other.sizeofarray;
    arr = new MyBoyBrady[other.sizeofarray];
    for(int i = 0; i < other.sizeofarray; i++)
    {
        ItemType emptyvariable;
        arr[i].count= other.get(i, emptyvariable);
        arr[i].variable = emptyvariable;
    }
    
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
    if(this != &rhs)
    {
        /*delete [] arr;
         sizeofarray = rhs.sizeofarray;    //copy all the values to rhs
         arr = new MyBoyBrady[rhs.sizeofarray];
         for(int i = 0; i < sizeofarray; i++)
         {
         arr[i].count = rhs.arr[i].count;
         arr[i].variable = rhs.arr[i].variable;
         }
         return *this;*/
        Multiset temp(rhs);
        swap(temp);
        return *this;
    }
    return *this;    //idk if this is correct
}


bool Multiset::empty() const
{
    
    for(int i = 0; i < sizeofarray; i++)
    {
        if(arr[i].count != 0)
            return false;
    }
    
    return true;
}

int Multiset::size() const
{
    int counter = 0;
    for(int i=0; i < sizeofarray; i++)
    {
        if(arr[i].count != 0)
            counter+= arr[i].count;
    }
    return counter;
}

int Multiset::uniqueSize() const
{
    int counter = 0;
    for(int i=0; i < sizeofarray; i++)
    {
        if(arr[i].count != 0)
            counter++;
    }
    return counter;
}

bool Multiset::insert(const ItemType& value)
{
    if(uniqueSize() < sizeofarray)
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
    //    if(uniqueSize() == sizeofarray)
    //
    //    {
    //        if(arr[sizeofarray-1].variable == value)
    //        {
    //            arr[sizeofarray-1].count++;
    //            return true;
    //        }
    //    }
    
    return false;
}

int Multiset::erase(const ItemType& value)  //check over this
{
    if(uniqueSize() ==  sizeofarray)
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
                for(int j = i ; j < uniqueSize() && j != sizeofarray; j++) //should this just be < or <=
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
                for(int j = i ; j < uniqueSize() && j != sizeofarray; j++) //should this just be < or <=
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
    if(uniqueSize() == sizeofarray)
    {
        for(int i = 0; i < uniqueSize(); i++)
        {
            int c = arr[i].count;
            if(arr[i].variable == value)
            {
                for(int j = i; j < uniqueSize() && j != sizeofarray; j++)
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
                for(int j = i; j < uniqueSize() && j != sizeofarray; j++)
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
        if(arr[i].variable == value && arr[i].count > 0)
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
    if(i >= 0 && i < this->uniqueSize())
    {
        value = arr[i].variable;
        return arr[i].count;
    }
    return 0;
}

void Multiset::swap(Multiset& other)
{
    MyBoyBrady* temparr = arr;
    arr = other.arr;
    other.arr = temparr;
    int tempsize = sizeofarray;
    sizeofarray = other.sizeofarray;
    other.sizeofarray= tempsize;
    
}