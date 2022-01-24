//
//  Map.cpp
//  Project2
//
//  Created by Arsh Malik on 1/21/22.
//

#include "Map.h"
#include <iostream>
using namespace std;

Map::Map()
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

// Copy Constructor

Map::Map(const Map& other)
{
    if (other.head == nullptr)
    {
        head = nullptr;
        tail = nullptr;
        m_size = 0;
    }
    else
    {
        head = nullptr; tail = nullptr; m_size = 0;
        for (int i = 0; i < other.size(); i++)
        {
            KeyType Key; ValueType Val;
            other.get(i, Key, Val);
            insert(Key, Val);
        }
    }
}

// Assignment Operator

Map& Map::operator=(const Map& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Map::empty() const
{
    if (head == nullptr)
        return true;
    return false;
}

int Map::size() const
{
    return m_size;
}

bool Map::contains(const KeyType& key) const
{
    if (empty())
        return  false;
    for (Node* p = head; p != nullptr; p = p -> next)
    {
        if (p -> m_key == key)
            return true;
    }
    return false;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (contains(key))
        return false;
    
    if (empty())
    {
        Node* n = new Node;
        n->m_key = key;
        n->m_value = value;
        n->next = nullptr;
        n->prev = nullptr;
        head = n;
        tail = n;
        m_size++;
        return true;
    }
    // Pre sorting while inserting nodes
    
    // Case 1: If the key is smaller than every other key i.e needs to come first
    if (key < head->m_key)
    {
        Node* n = new Node;
        n->m_key = key;
        n->m_value = value;
        n->next = head;
        n->prev = nullptr;
        head->prev = n;
        head = n;
        m_size++;
        return true;
    }
    
    // Case 2: Key needs to be inserted somewhere in the middle
    
    Node* p = nullptr;
    for(p = head; p->next != nullptr; p = p->next)
    {
        if (p->next->next == nullptr)
            break;
        else if (key > p->m_key && key < p->next->m_key)
        {
            Node* n = new Node;
            n->m_key = key;
            n->m_value = value;
            n->next = p->next;
            p->next->prev = n;
            n->prev = p;
            p->next = n;
            m_size++;
            return true;
        }
    }
    // Case 3: If node is just less than the last node. Currently p points to the second last node
    if (key< tail->m_key)
    {
        Node*n = new Node;
        n->m_key = key;
        n->m_value = value;
        n->next = tail;
        n->prev = p;
        p->next = n;
        tail -> prev = n;
        m_size++;
        return true;
    }
    // taking p to the last node
    if (p->next!= nullptr)
        p = p->next;
    
    // Node couldn't be inserted in between. Inserting in the end...
    Node* n = new Node;
    n->m_key = key;
    n->m_value = value;
    n->next = nullptr;
    n->prev = p;
    tail = n;
    p->next = n;
    m_size++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    for (Node*p = head; p!=nullptr; p=p->next)
    {
        if (p->m_key == key)
        {
            p->m_value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    for (Node*p = head; p!=nullptr; p=p->next)
    {
        if (p!=nullptr && p->m_key == key)
        {
            p->m_value = value;
            return true;
        }
    }
    return insert(key, value);
}

bool Map::erase(const KeyType& key)
{
    if (!contains(key))
        return false;
    
    // Checking if we need to delete the first node
    
    if (head->m_key == key)
    {
        Node* toDelete = head;
        head = toDelete->next;
        toDelete->next->prev = nullptr;
        delete toDelete;
        return true;
    }
    
    // Deleting a node in the middle of the list
    Node* p = head;
    for (; p-> next != nullptr; p = p -> next)
    {
        if (p!=nullptr && p->m_key == key)
        {
            p->next->prev = p->prev;
            p->prev->next = p->next;
            delete p;
            return true;
        }
    }
    
    // If code reaches here, means last element needs to be deleted.
    // Currently p points to the last element.
    tail = p->prev;
    p->prev->next = nullptr;
    delete p;
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    for (Node* p = head; p != nullptr; p = p->next)
    {
        if (p != nullptr && p->m_key == key)
        {
            value = p->m_value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i<0 || i >= size() || empty())
        return false;
    
    int counter = 0;
    Node* p = head;
    while (p != nullptr && counter != i)
    {
        p = p->next;
        counter++;
    }
    key = p->m_key;
    value = p->m_value;
    return true;
}

void Map::swap(Map& other)
{
    Node* tempHead = this->head;
    this->head = other.head;
    other.head = tempHead;
    
    Node* tempTail = this->tail;
    this->tail = other.tail;
    other.tail = tempTail;
    
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}


void Map::dump() const
{
    for (Node* p = head; p!=nullptr; p = p->next)
    {
        cerr << p->m_key << " " << p->m_value << endl;
    }
}

Map::~Map()
{
    for (Node* p = head; p!=nullptr;)
    {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

// Non Member Functions

bool merge(const Map& m1, const Map& m2, Map& result)
{
    Map temp = m1;
    
    bool returnVal = true;
    
    for (int i = 0; i < m2.size(); i++)
    {
        KeyType k;
        ValueType v;
        m2.get(i, k, v);
        if (m1.contains(k))
        {
            ValueType m1value;
            m1.get(k, m1value);
            if (m1value != v)
            {
                temp.erase(k);
                returnVal = false;
            }
        }
        else
        {
            temp.insert(k, v);
        }
    }
    result = temp;
    return returnVal;
}

void reassign(const Map& m, Map& result)
{
    result = m;
    KeyType firstK; ValueType firstV;
    result.get(0, firstK, firstV);
    for (int i = 1; i < result.size(); i++)
    {
        KeyType tempKi; ValueType tempVi;
        KeyType tempK0; ValueType tempVi0;
        result.get(i, tempKi, tempVi);
        result.get(i-1, tempK0, tempVi0);
        result.update(tempK0, tempVi);
    }
    KeyType lastKey; ValueType lastVal;
    result.get(result.size()-1, lastKey, lastVal);
    result.update(lastKey, firstV);
}
