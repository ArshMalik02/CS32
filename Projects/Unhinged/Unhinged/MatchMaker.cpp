//
//  MatchMaker.cpp
//  Unhinged
//
//  Created by Arsh Malik on 3/8/22.
//

#include "MatchMaker.h"
#include "provided.h"
#include <algorithm>
#include <vector>
#include <set>
#include <string>

using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_db = mdb;
    m_atDB = at;
}

MatchMaker::~MatchMaker(){}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    vector<EmailCount> matches;
    const PersonProfile* person = m_db.GetMemberByEmail(email);
    vector<AttValPair> setOfCompatibleAtValPairs;
    
    // Getting the attVals of the person
    for (int i = 0; i!=person->GetNumAttValPairs(); i++)
    {
        AttValPair atval;
        person->GetAttVal(i, atval);            // getting a single attval
        vector<AttValPair> compatibleAtValPairs = m_atDB.FindCompatibleAttValPairs(atval); // getting that attvals's compatible attvals
        for (int j = 0; j!=compatibleAtValPairs.size(); j++)
        {
            setOfCompatibleAtValPairs.push_back(compatibleAtValPairs[j]);
        }
    }
    vector<AttValPair>::iterator it = setOfCompatibleAtValPairs.begin();
    while (it!=setOfCompatibleAtValPairs.end())
    {
        vector<string> setOfPeopleWithCompatibleAtVals = m_db.FindMatchingMembers(*it);
        for (int k = 0; k!= setOfPeopleWithCompatibleAtVals.size(); k++)
        {
            const PersonProfile* p = m_db.GetMemberByEmail(setOfPeopleWithCompatibleAtVals[k]);
            int count = 0;
            for (int i = 0; i!= p->GetNumAttValPairs(); i++)
            {
                AttValPair avp;
                p->GetAttVal(i, avp);
                if (find(setOfCompatibleAtValPairs.begin(), setOfCompatibleAtValPairs.end(), avp)!=setOfCompatibleAtValPairs.end())
                    count++;
            }
            if (count>=threshold)
            {
                EmailCount matchedPerson(setOfPeopleWithCompatibleAtVals[k], count);
                matches.push_back(matchedPerson);
            }
        }
        it++;
    }
    return matches;
}

bool MatchMaker::checkIfExists(const std::vector<EmailCount>& check, std::string email) const
{
    for (int i = 0; i!=check.size(); i++)
    {
        if (check[i].email==email)
            return true;
    }
    return false;
}



