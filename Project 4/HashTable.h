//
//  HashTable.h
//  project 4
//
//  Created by Daniel O'Laughlin on 3/7/15.
//  Copyright (c) 2015 Daniel O'Laughlin. All rights reserved.
//

#ifndef project_4_HashTable_h
#define project_4_HashTable_h

#include "provided.h"    //include so you can use the computeHasg

template <typename KeyType,	typename ValueType>
class HashTable
{
public:
    HashTable(unsigned int numBuckets,	unsigned int capacity);   //possibly make pointers to most recent
    ~HashTable();
    bool isFull()	const;
    bool set(const KeyType&	key, const ValueType& value, bool permanent = false);
    bool get(const KeyType& key, ValueType& value) const;
    bool touch(const KeyType& key);
    bool discard(KeyType& key,	ValueType& value);
private:
				//	We	prevent a	HashTable from	being	copied	or	assigned	by	declaring	the
				//	copy	constructor	and	assignment	operator	private	and	not	implementing	them.
    struct Node
    {
        ValueType value;
        KeyType m_key;
        Node* next;        //next in the linked list
        Node* nextUp;        //next in order that it was added
        Node* last;
        Node* behindInOrder;
    };
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
    Node** arr;
    int m_numObjects;
    int m_numBuckets;
    int max;
    Node* nextToGetDeleted;
};



template <typename KeyType,	typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int numBuckets, unsigned int capacity)
{
    arr = new Node*[numBuckets];    //dynamically allocate the array
    max = capacity;
    m_numObjects = 0;
    m_numBuckets = numBuckets;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::isFull() const
{
    return m_numObjects == max;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::get(const KeyType& key, ValueType& value) const
{
    unsigned int num = computeHash(key);
    int bucketKey = num % m_numBuckets;
    
    Node* ptr = arr[bucketKey];
    while(ptr != nullptr)
    {
        value = ptr->value;  // check this again
        if(ptr->m_key == key)
            return true;
        ptr = ptr->next;
    }
    return false;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::set(const KeyType& key, const ValueType& value, bool permanent)
{
    if(isFull())
        return false;
    
    unsigned int num = computeHash(key);    //key would be the name
    int bucketKey = num % m_numBuckets;        //index of the array
    
    Node* newNode = new Node();
    newNode->value = value;
    newNode->m_key = key;
    
    if(permanent == false)
    {
        if(nextToGetDeleted == nullptr)
            nextToGetDeleted = newNode;
        
        else
        {
            Node* p = nextToGetDeleted;
            for(;p->nextUp != nullptr; p = p->nextUp)
            {
                ;
            }
            p->nextUp = newNode;
            newNode->behindInOrder = p; //
        }
    }
    
    Node* Nptr = arr[bucketKey];
    
    while(Nptr != nullptr){
        if(Nptr->m_key == key){
            if(!permanent)
            {
                if(Nptr->nextUp != nullptr)
                    Nptr->nextUp->behindInOrder = newNode;
                
                
                if(Nptr->behindInOrder != nullptr)
                    Nptr->behindInOrder->nextUp = newNode;
                
                newNode->nextUp = Nptr->nextUp;
                newNode->behindInOrder = Nptr->behindInOrder;
            }
            
            
            if(Nptr->next != nullptr)
            {
                newNode->next = Nptr->next;
                Nptr->next->last = newNode;
            }
            
            
            if(Nptr->last != nullptr)
                Nptr->last->next = newNode;
            
            newNode->last = Nptr->last;
            delete Nptr;
            return true;
        }
        
        if(Nptr->next == nullptr){
            Nptr->next = newNode;
            newNode->last = Nptr;
            m_numBuckets++;
        }
        Nptr = Nptr->next;
    }
    return true;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::touch(const KeyType& key)
{
    unsigned int num = computeHash(key);
    int bucketKey = num % m_numBuckets;
    
    Node* ptr = arr[bucketKey];
    while(ptr != nullptr)
    {
        if(ptr->m_key == key)
        {
            ptr->nextUp = nextToGetDeleted->nextUp;
            nextToGetDeleted = ptr;
            ptr->behindInOrder = nullptr;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

template <typename KeyType,	typename ValueType>
bool HashTable<KeyType, ValueType>::discard(KeyType& key,	ValueType& value)
{
    if(nextToGetDeleted == nullptr)
        return false;
    
    Node* p = nextToGetDeleted;
    
    
    if(p->next != nullptr)
    {
        p->next->last = p->last;
    }
    
    if(p->last != nullptr)
    {
        p->last->next = p->next;
    }
    
    p->nextUp->behindInOrder = nullptr;
    nextToGetDeleted = p->nextUp;
    value = p->value;
    key = p->m_key;
    m_numObjects--;
    
    delete p;
    return true;
}

template <typename KeyType,	typename ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
    for(int i = 0; i < m_numBuckets; i++)
    {
        Node* ptr = arr[i];
        if(ptr == nullptr)
            continue;
        while(ptr != nullptr)
        {
            Node* q = ptr->next;
            delete ptr;
            ptr = q;
        }
    }
    delete [] arr;
}