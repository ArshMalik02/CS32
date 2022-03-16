//
//  MemberDatabase.cpp
//  Unhinged
//
//  Created by Arsh Malik on 3/6/22.
//

#include "MemberDatabase.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

MemberDatabase::MemberDatabase(){}

MemberDatabase::~MemberDatabase()
{
    for (int i = 0; i!=ptrToPersonProfiles.size(); i++)
    {
        delete ptrToPersonProfiles[i];
    }
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    string line;
    ifstream members(filename);
    if (members)
    {
        int flag = 1;
        PersonProfile* temp = nullptr;
        string name;
        string email;
        while ( getline (members,line))
        {
            if (!line.empty())
            {
                if (flag==1)
                {
                    name = line;
                    flag++;
                }
                else if (flag==2)
                {
                    email = line;
                    if (db.search(email)!=nullptr)
                        return false;
                    flag++;
                    PersonProfile* p =  new PersonProfile(name, email);
                    db.insert(email, p);
                    ptrToPersonProfiles.push_back(p);
                    temp = p;
                }
                else if (flag==3){
                    flag++;
                    continue;
                }
                else if (flag==4)
                {
                    // Adding to RT that maps emails to PersonProfiles
                    string attribute;
                    string value;
                    size_t k = line.find(",");
                    attribute = line.substr(0,k);
                    value = line.substr(k+1,line.size()-1);
                    AttValPair pair(attribute,value);
                    temp->AddAttValPair(pair);
                    // Adding to RadixTree from string to vector of string emails
                    vector<string>* emails = commonAttributeMembers.search(line);
                    if (emails==nullptr)
                    {
                        vector<string> tempEmailVector;
                        tempEmailVector.push_back(email);
                        commonAttributeMembers.insert(line, tempEmailVector);
                    }
                    else
                        emails->push_back(email);
                }
            }
            else
            {
                flag=1;
                temp = nullptr;
                continue;
            }
        }
        members.close();
        return true;
    }
    else
    {
        cout << "Unable to open file" << endl;
        return false;
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    if (db.search(email)==nullptr)
        return nullptr;
    return *(db.search(email));
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string src = input.attribute+","+input.value;
    vector<string>* temp = commonAttributeMembers.search(src);
    vector<string> temp1;
    if (temp==nullptr)
        return temp1;
    else
        return *temp;        
}
