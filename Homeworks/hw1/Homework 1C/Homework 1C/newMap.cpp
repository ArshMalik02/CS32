//
//  newMap.cpp
//  Homework 1C
//
//  Created by Arsh Malik on 1/15/22.
//

#include "newMap.h"
#include "iostream"
using namespace std;

Map::Map()
{
    m_memberCount = 0;
    m_maxlen = DEFAULT_MAX_ITEMS;
    m_array = new member[m_maxlen];
}

Map::Map(int x)
{
    m_memberCount = 0;
    m_maxlen = x;
    m_array = new member[m_maxlen];
}

Map::Map(const Map &src)   // Copy constructor
{
    m_memberCount = src.m_memberCount;
    m_maxlen = src.m_maxlen;
    m_array = new member[m_maxlen];
    for (int j = 0; j < m_memberCount; j++)
        m_array[j] = src.m_array[j];
}

Map& Map::operator=(const Map &src)
{
    if (&src == this)
        return *this;
    delete [] m_array;
    m_memberCount = src.m_memberCount;
    m_maxlen = src.m_maxlen;
    m_array = new member[m_maxlen];
    for (int j = 0; j < m_maxlen; j++)
        m_array[j] = src.m_array[j];
    return *this;
}

bool Map::empty() const
{
    if (m_memberCount == 0)
        return true;
    return false;
}

int Map::size() const
{
    return m_memberCount;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (m_memberCount+1 > m_maxlen)
        return false;
    for (int i = 0; i < m_memberCount; i++)
    {
        if (m_array[i].m_key == key)
            return false;
    }
    
    // Adding new member
    m_array[m_memberCount].m_key = key;
    m_array[m_memberCount].m_value = value;
    m_memberCount++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < m_memberCount; i++)
    {
        if (m_array[i].m_key == key)
        {
            m_array[i].m_value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < m_memberCount; i++)
    {
        if (m_array[i].m_key == key)
        {
            m_array[i].m_value = value;
            return true;
        }
    }
    if (m_memberCount+1 > DEFAULT_MAX_ITEMS)
        return false;
    // Adding new member
    m_array[m_memberCount].m_key = key;
    m_array[m_memberCount].m_value = value;
    m_memberCount++;
    return true;
}

bool Map::erase(const KeyType& key)
{
    for (int i = 0; i < m_memberCount; i++)
    {
        if (m_array[i].m_key == key)
        {
            for (int k = i; k < m_memberCount - 1; k++)
            {
                m_array[k] = m_array[k+1];
            }
            m_memberCount--;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const
{
    for (int i = 0; i < m_memberCount; i++)
        if (m_array[i].m_key == key)
            return true;
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    for (int i = 0; i < m_memberCount; i++)
        if (m_array[i].m_key == key)
        {
            value = m_array[i].m_value;
            return true;
        }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0 || i >= m_memberCount)
        return false;
    
    for (int k = 0; k < m_memberCount; k++)
    {
        int count = 0;
        for (int j = 0; j < m_memberCount; j++)
        {
            if (m_array[k].m_key > m_array[j].m_key)
                count++;
        }
        if (count == i)
        {
            key = m_array[k].m_key;
            value = m_array[k].m_value;
            break;
        }
    }
    return true;
}

void Map::swap(Map& other)
{
    int tempMaxCount = this->m_maxlen;
    this->m_maxlen = other.m_maxlen;
    other.m_maxlen = tempMaxCount;
    
    int tempMemberCount = this->m_memberCount;
    this->m_memberCount = other.m_memberCount;
    other.m_memberCount = tempMemberCount;
    
    // Swapping the addresses of the map
    
    member *tempArrAddress = this->m_array;
    this->m_array = other.m_array;
    other.m_array = tempArrAddress;
}

void Map::dump() const
{
    for (int i = 0; i < m_memberCount; i++)
    {
        cerr << m_array[i].m_key << "->" << m_array[i].m_value << ", ";
    }
    cerr << endl;
}

Map::~Map()
{
    delete [] m_array;
}
