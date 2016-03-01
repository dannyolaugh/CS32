//
//  Multiset.cpp
//  Project 2
//
//  Created by Daniel O'Laughlin on 1/23/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#include "Multiset.h"
Multiset::Multiset()
{
}

Multiset::~Multiset()
{
    if(head != nullptr)
    {
        Node* ptr = head;
        while(ptr->next != nullptr)
        {
            Node* temp = ptr->next;  //what the hell is going on here.  FIX THIS
            delete ptr;
            ptr = temp;
        }
        delete ptr;
    }
}

Multiset::Multiset(const Multiset& other)  //not sure if this works
{
    Node* ptr;
    for(ptr = other.head; ptr->next != nullptr; ptr = ptr->next) //loop through other
    {
        for(int i = 0; i < ptr->count; i++)
        {
            insert(ptr->variable); //insert the variable of other into current multiset as many times as it occurs
        }
    }
    for(int k = 0; k < ptr->count; k++)        //make sure to insert into the last node
    {
        insert(ptr->variable);
    }
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
    if(this != &rhs)           //checks for aliasing  //WHAT IF THEY ARE THE SAME THOUGH???
    {
        Multiset temp(rhs);      //makes a copy of rhs
        swap(temp);               //swaps it with the original, so now original has the value of rhs
    }
    return *this;
}


bool Multiset::empty() const
{
    if(head == nullptr)       //if head == null there's no nodes
        return true;
    else
        return false;
}

int Multiset::size() const
{
    int number = 0;     //serves as a counter
    Node* ptr;
    if (empty())
        return  number;
    else
    {
        for(ptr = head; ptr->next != nullptr; ptr = ptr->next) //follow each ptr until you come to null signifying the end
        {
            number += ptr->count;    //increment number by the count of the node
        }
        number += ptr->count;   //make sure to increment number by the count of the last node bc it isnt checked in the loop
    }
    return number;
}

int Multiset::uniqueSize() const
{
    int number = 0; //serves as a counter
    Node* ptr;
    for(ptr = head; ptr->next != nullptr; ptr = ptr->next)
    {
        if(ptr->count != 0)
            number++;         //increment counter by 1 no matter the count of the node
    }
    number++;
    return number;
}

bool Multiset::insert(const ItemType& value)
{
    Node* ptr;
    // Node* newNode = new Node;
    if(empty())
    {
        Node* newNode = new Node;      //must make a new node
        head = newNode;                 //set head and tail pointers to point to newNode
        tail = newNode;
        newNode->variable = value;         //variable gets value and increment count
        newNode->count++;
        return true;
    }
    
    for(ptr = head; ptr->next != nullptr && ptr->variable != value; ptr = ptr->next)
    {
        ; //will leave the loop once it finds value or it is at the last node in the linked list
    }
    if(ptr->variable == value)
    {
        ptr->count++;
        return true;
    }
    
    
    if(tail->next == nullptr) //which it always will be, if the value is not already there create new node
    {
        Node* newNode = new Node;
        ptr->next = newNode;          //at this point ptr is pointing to the last node, but you need to add the newNode
        tail = newNode;              //new node is now the last node
        newNode->next = nullptr;
        newNode->last = ptr;         //ptr preceeds new node
        newNode->variable = value;   //variable gets value increment count
        newNode->count++;
    }
    return true;
    
}

int Multiset::erase(const ItemType& value) //dont delete anything is value isnt there
{
    Node* ptr;
    for(ptr = head; ptr->next != nullptr && ptr->variable != value; ptr = ptr->next)
    {
        ;
    }
    if(ptr->variable == value)
    {
        if(ptr->count > 1)      //if count is zero must delete node
        {
            ptr->count--;
            return 1;
        }
        else
        {
            
            if(uniqueSize() == 1)  //the entire linked list will be gone
            {
                head = nullptr;
                tail = nullptr;
                delete ptr;
                return 1;
            }
            else if(head == ptr)  //if value is found in the first node
            {
                head = ptr->next;
                ptr->next->last = nullptr;
                return 1;
            }
            else if(ptr->next == nullptr) //if value is found in the last node
            {
                ptr->last->next = nullptr;
                delete ptr;
                return 1;
            }
            else        //any other case such as value being found in a node in the middle of the linked list
            {
                ptr->last->next = ptr->next;
                ptr->next->last = ptr->last;
                delete ptr;
                return 1;
            }
            
            
        }
    }
    
    else
        return 0;
    
}


int Multiset::eraseAll(const ItemType& value)
{
    Node* ptr;
    int temp = 0;
    for(ptr = head; ptr->next != nullptr && ptr->variable != value; ptr = ptr->next)
    {
        ;
    }
    
    if(ptr->variable == value)
    {
        temp = ptr->count;
        
        if(uniqueSize() == 1)  //the entire linked list will be gone
        {
            head = nullptr;
            tail = nullptr;
            delete ptr;
            return temp;
        }
        else if(head == ptr)   //if value is found in the first node
        {
            head = ptr->next;
            ptr->next->last = nullptr;
            return temp;
        }
        else if(ptr->next == nullptr)   //if value is found in the last node
        {
            ptr->last->next = nullptr;
            delete ptr;
            return temp;
        }
        else         //any other case such as value being found in a node in the middle of the linked list
        {
            ptr->last->next = ptr->next;
            ptr->next->last = ptr->last;
            delete ptr;
            return temp;   //retrun the count
        }
    }
    
    return 0;
}

bool Multiset::contains(const ItemType& value) const
{
    Node* ptr;
    for(ptr = head; ptr->next != nullptr && ptr->variable != value; ptr = ptr->next)
    {
        ; //leave loop is ptr is pointing to last node or the node that contains value
    }
    if(ptr->variable == value) //check why it left loop
        return true;
    return false;
}

int Multiset::count(const ItemType& value) const
{
    Node* ptr;
    for(ptr = head; ptr->next != nullptr && ptr->variable != value; ptr = ptr->next)
    {
        ;  //leave loop is ptr is pointing to last node or the node that contains value
    }
    if(ptr->variable == value)
        return ptr->count;
    return 0;
}

int Multiset::get(int i, ItemType& value) const
{
    Node* ptr = head;
    for(int j = 0; j < i; j++)  //int i is the index+1 of the item you want
    {
        if(ptr->next != nullptr)
            ptr = ptr->next;           //when ptr points to that index leave the loop
        else
            return 0;
    }
    value = ptr->variable;
    return ptr->count;    //return the count of that variable
    
}

void Multiset::swap(Multiset& other)
{
    
    //switch head and tail pointers, thus swapping multisets
    
    Node* temptr;
    temptr = other.head;
    other.head = head;
    head = temptr;
    
    Node* temptail;
    temptail = other.tail;
    other.tail = tail;
    tail = temptail;
    
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result) //aliasing
{
    
    if(&ms1 == &result)      //check for aliasing
    {
        Multiset* temporaryMult = new Multiset(ms1);
        result = *temporaryMult;
    }
    if(&ms2 == &result)  //check for aliasing
    {
        Multiset* temporaryMult2 = new Multiset(ms2);
        result = *temporaryMult2;
    }
    result = ms1;     //set result back equal to ms1
    ItemType temp;
    int x;  //how many times that temp is in ms2
    for(int k = 0; k < ms2.uniqueSize(); k++)
    {
        x =  ms2.get(k, temp);
        for(int i=0; i < x; i++)  //insert temp as many times as it occurs
        {
            result.insert(temp);
        }
    }
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)   //aliasing
{
    if(&ms1 == &result)   //check for aliasing
    {
        Multiset* temporaryMult = new Multiset(ms1);
        result = *temporaryMult;
    }
    if(&ms2 == &result)   //check for aliasing
    {
        Multiset* temporaryMult2 = new Multiset(ms2);
        result = *temporaryMult2;
    }
    result = ms1;    //set result back equal to ms1
    ItemType temp;
    int x;  //how many times that temp is in ms2
    for(int k = 0; k < ms2.uniqueSize(); k++)
    {
        x =  ms2.get(k, temp);
        for(int i=0; i < x; i++)
        {
            result.erase(temp);    //erase as many times as temp occurs
        }
    }
    
}