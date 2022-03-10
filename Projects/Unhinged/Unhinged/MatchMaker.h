//
//  MatchMaker.hpp
//  Unhinged
//
//  Created by Arsh Malik on 3/8/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include <string>
#include <vector>
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email,int threshold) const;
private:
    MemberDatabase m_db;
    AttributeTranslator m_atDB;
    bool checkIfExists(const std::vector<EmailCount>& check, std::string email) const;
};

#endif /* MatchMaker_hpp */
