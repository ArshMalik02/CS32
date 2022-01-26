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
    if (other.head == nullptr)          // Checking if the other map is empty
    {
        head = nullptr;
        tail = nullptr;
        m_size = 0;
    }
    else
    {
        head = nullptr; tail = nullptr; m_size = 0;
        for (int i = 0; i < other.size(); i++)          // Looping through the other map inserting its values in                                               //the current map
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
    if (this != &rhs)     // this map shouldn't be same as the rhs map
    {
        Map temp(rhs);      // Creating a temp map and swapping the entire map with the current one
        swap(temp);
    }                       // Here temp goes away as it's a local variable
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
        if (p -> m_key == key)              // Looping through all the nodes and if key is found, then return true
            return true;
    }
    return false;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (contains(key))                     // Map should not contain already contain the same key
        return false;
    
    if (empty())                            // Custom Case: Inserting the first element
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
    for (Node*p = head; p!=nullptr; p=p->next)   // Looping through Map and finding the key, setting its new value
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
    for (Node*p = head; p!=nullptr; p=p->next)       // If key exists, need to update it
    {
        if (p!=nullptr && p->m_key == key)
        {
            p->m_value = value;
            return true;
        }
    }
    return insert(key, value);                      // Otherwise, insert
}

bool Map::erase(const KeyType& key)
{
    if (!contains(key))
        return false;
    
    // Checking if we need to delete the first node
    
    if (head->m_key == key)
    {
        if (head->next!=nullptr)
        {
            Node* toDelete = head;
            head = toDelete->next;
            toDelete->next->prev = nullptr;
            delete toDelete;
            m_size--;
            return true;
        }
        else
        {
            Node* toDel = head;
            head = nullptr;
            tail = nullptr;
            m_size--;
            delete toDel;
            return true;
        }
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
            m_size--;
            return true;
        }
    }
    
    // If code reaches here, means last element needs to be deleted.
    // Currently p points to the last element.
    tail = p->prev;
    p->prev->next = nullptr;
    delete p;
    m_size--;
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    for (Node* p = head; p != nullptr; p = p->next)    // If the key is found, set value to key's value
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
    if (i<0 || i >= size() || empty())          // checking if i is in range
        return false;
    
    int counter = 0;
    Node* p = head;
    while (p != nullptr && counter != i)        // taking p to the required node
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
    Node* tempHead = this->head;            // swapping head pointer
    this->head = other.head;
    other.head = tempHead;
    
    Node* tempTail = this->tail;            // swapping tail pointer
    this->tail = other.tail;
    other.tail = tempTail;
    
    int tempSize = m_size;                  // swapping sizes
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
    for (Node* p = head; p!=nullptr;)           // Deleting all the nodes
    {
        Node* n = p->next;
        delete p;
        p = n;
    }
}

// Non Member Functions

bool merge(const Map& m1, const Map& m2, Map& result)
{
    Map temp = m1;              // Creating a temp map. will be changed later as required
    
    bool returnVal = true;
    
    for (int i = 0; i < m2.size(); i++)
    {
        KeyType k;
        ValueType v;
        m2.get(i, k, v);
        if (m1.contains(k))             // if both m1 and m2 contain k
        {
            ValueType m1value;
            m1.get(k, m1value);
            if (m1value != v)           // if k's values dont match then remove from temp
            {
                temp.erase(k);
                returnVal = false;
            }
        }
        else                            // only one of m2 contains k
        {
            temp.insert(k, v);
        }
    }
    result = temp;                      // finally assigning our temp to result
    return returnVal;
}

void reassign(const Map& m, Map& result)
{
    result = m;
    KeyType firstK; ValueType firstV;
    result.get(0, firstK, firstV);         // Getting the first node's key and value
    for (int i = 1; i < result.size(); i++)
    {
        KeyType tempKi; ValueType tempVi;
        KeyType tempK0; ValueType tempVi0;
        result.get(i, tempKi, tempVi);          // Assigning the current node's values to its prev node
        result.get(i-1, tempK0, tempVi0);
        result.update(tempK0, tempVi);
    }
    KeyType lastKey; ValueType lastVal;
    result.get(result.size()-1, lastKey, lastVal);
    result.update(lastKey, firstV);             // setting the last node's value to the first's
}
