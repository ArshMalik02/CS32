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
#include "utility.h"

using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_db = &mdb;
    m_atDB = &at;
}

MatchMaker::~MatchMaker(){}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    if (threshold<=0)
        threshold = 1;
    vector<EmailCount> matches;
    const PersonProfile* person = m_db->GetMemberByEmail(email);
    unordered_set<string> setOfCompatibleAtValPairs;
    
    // Getting the attVals of the person
    for (int i = 0; i!=person->GetNumAttValPairs(); i++)
    {
        AttValPair atval;
        person->GetAttVal(i, atval);            // getting a single attval
        vector<AttValPair> compatibleAtValPairs = m_atDB->FindCompatibleAttValPairs(atval); // getting that attvals's compatible attvals
        for (int j = 0; j!=compatibleAtValPairs.size(); j++)
        {
            setOfCompatibleAtValPairs.insert(compatibleAtValPairs[j].attribute+","+compatibleAtValPairs[j].value);
        }
    }
    unordered_set<string>::iterator it = setOfCompatibleAtValPairs.begin();
    while (it!=setOfCompatibleAtValPairs.end())
    {
        string att = (*it).substr(0, (*it).find(","));
        string val = (*it).substr((*it).find(",")+1,it->size()-1);
        AttValPair av(att,val);
        vector<string> setOfPeopleWithCompatibleAtVals = m_db->FindMatchingMembers(av);
        for (int k = 0; k!= setOfPeopleWithCompatibleAtVals.size(); k++)
        {
            const PersonProfile* p = m_db->GetMemberByEmail(setOfPeopleWithCompatibleAtVals[k]);
            int count = 0;
            for (int i = 0; i!= p->GetNumAttValPairs(); i++)
            {
                AttValPair avp;
                p->GetAttVal(i, avp);
                if (setOfCompatibleAtValPairs.find(avp.attribute+","+avp.value)!=setOfCompatibleAtValPairs.end())
                    count++;
            }
            if (count>=threshold)
            {
                EmailCount matchedPerson(setOfPeopleWithCompatibleAtVals[k], count);
                if (checkIfExists(matches, setOfPeopleWithCompatibleAtVals[k])==false)
                    matches.push_back(matchedPerson);
            }
        }
        it++;
    }
    sort(matches.begin(), matches.end(), &compareEmailCounts);
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



