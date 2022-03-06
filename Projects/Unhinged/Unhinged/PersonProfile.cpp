//
//  PersonProfile.cpp
//  Unhinged
//
//  Created by Arsh Malik on 3/5/22.
//

#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string name, std::string email)
{
    m_name = name;
    m_email = email;
    m_count = 0;
}

PersonProfile::~PersonProfile()
{
    ;
}

std::string PersonProfile::GetName() const
{
    return m_name;
}

std::string PersonProfile::GetEmail() const
{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    std::unordered_set<std::string>* p = map.search(attval.attribute);
    // Attribute exists but the value doesn't
    if (p!=nullptr)
    {
        if (p->find(attval.value)==p->end())
        {
            p->insert(attval.value);
            AttValVector.push_back(attval);
            m_count++;
            return;
        }
        else
            return;    // The attribute value pair exists
    }
    std::unordered_set<std::string> temp;
    temp.insert(attval.value);
    AttValVector.push_back(attval);
    map.insert(attval.attribute, temp);
    m_count++;
}

int PersonProfile::GetNumAttValPairs() const
{
    return m_count;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num<0 || attribute_num>GetNumAttValPairs())
        return false;
    attval = AttValVector[attribute_num];
    return true;
}

