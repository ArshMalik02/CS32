//
//  MemberDatabase.hpp
//  Unhinged
//
//  Created by Arsh Malik on 3/6/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include <string>
#include <vector>
#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"

class MemberDatabase
{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<PersonProfile*> db;
    RadixTree<std::vector<std::string>> commonAttributeMembers;
    std::vector<PersonProfile*> ptrToPersonProfiles;
};

#endif /* MemberDatabase_hpp */
