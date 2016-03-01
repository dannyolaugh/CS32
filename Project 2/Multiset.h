//
//  Multiset.h
//  Project 2
//
//  Created by Daniel O'Laughlin on 1/23/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef __Project_2__Multiset__
#define __Project_2__Multiset__

#include <iostream>

typedef std::string ItemType;

class Multiset
{
public:
    Multiset();
    ~Multiset();
    Multiset(const Multiset& other);
    Multiset& operator=(const Multiset& rhs);
    bool empty() const;
    int size() const;
    int uniqueSize() const;
    bool insert(const ItemType& value);
    int erase(const ItemType& value);
    int eraseAll(const ItemType& value);
    bool contains(const ItemType& value) const;
    int count(const ItemType& value) const;
    int get(int i, ItemType& value) const;
    void swap(Multiset& other);
    
private:
    struct Node
    {  //structs are pulblic by nature
        Node* next = nullptr;
        Node* last = nullptr;
        ItemType variable;
        int count = 0;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif /* defined(__Project_2__Multiset__) */