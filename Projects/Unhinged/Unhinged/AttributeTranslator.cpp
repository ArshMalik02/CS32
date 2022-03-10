//
//  AttributeTranslator.cpp
//  Unhinged
//
//  Created by Arsh Malik on 3/7/22.
//

#include "AttributeTranslator.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

AttributeTranslator::AttributeTranslator(){}

AttributeTranslator::~AttributeTranslator()
{
    for (int i = 0; i!=ptrToAttValPairs.size(); i++)
    {
        delete ptrToAttValPairs[i];
    }
}

bool AttributeTranslator::Load(string filename)
{
    string line;
    ifstream attvals(filename);
    if (attvals)
    {
        while (getline(attvals, line))
        {
            // line: job,chef,hobby,eating
            size_t firstCommaID = line.find(",");
            string lineAfterFirstComma = line.substr(firstCommaID+1, line.size()-1);
            // chef,hobby,eating
            
            size_t secondCommaID = lineAfterFirstComma.find(",");
            string attvalcommon = line.substr(0,firstCommaID+secondCommaID+1);
            // job,chef
            string attvalcompatible = line.substr(firstCommaID+secondCommaID+2,line.size()-1);
            // hobby,eating
            
            size_t thirdCommaID = attvalcompatible.find(",");
            string compatibleAttribute = attvalcompatible.substr(0,thirdCommaID);
            // hobby
            string compatibleValue = attvalcompatible.substr(thirdCommaID+1,attvalcompatible.size()-1);
            // eating
            
            // Inserting AttValPair into the radix tree.
            
            if (CompatibleAttValPairs.search(attvalcommon)==nullptr)
            {
                vector<AttValPair*> temp;
                AttValPair* pair = new AttValPair(compatibleAttribute,compatibleValue);
                temp.push_back(pair);
                CompatibleAttValPairs.insert(attvalcommon, temp);
                ptrToAttValPairs.push_back(pair);
            }
            else
            {
                AttValPair* pair = new AttValPair(compatibleAttribute,compatibleValue);
                CompatibleAttValPairs.search(attvalcommon)->push_back(pair);
                ptrToAttValPairs.push_back(pair);
            }
        }
        attvals.close();
        return true;
    }
    else
        return false;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs( const AttValPair& source) const
{
    vector<AttValPair> temp;
    vector<AttValPair*>* temp1 = CompatibleAttValPairs.search(source.attribute+","+source.value);
    if (temp1 == nullptr)
    {
        return temp;
    }
    else
    {
        for (int i = 0; i!=temp1->size(); i++)
        {
            temp.push_back(*((*temp1)[i]));
        }
        return temp;
    }
}
