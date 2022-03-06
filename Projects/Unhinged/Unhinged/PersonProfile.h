//
//  PersonProfile.h
//  Unhinged
//
//  Created by Arsh Malik on 3/5/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include <string>
#include "provided.h"
#include "RadixTree.h"
#include <unordered_set>
#include <vector>

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::unordered_set<std::string>> map;
    std::vector<AttValPair> AttValVector;
    int m_count;
};

#endif /* PersonProfile_h */
