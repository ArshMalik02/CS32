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

bool MemberDatabase::LoadDatabase(std::string file)
{
    string line;
    ifstream members(file);
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
                    string attribute;
                    string value;
                    size_t k = line.find(",");
                    attribute = line.substr(0,k);
                    value = line.substr(k+1,line.size()-1);
                    AttValPair pair(attribute,value);
                    temp->AddAttValPair(pair);
                }
                cout << line << '\n';
            }
            else
            {
                flag=1;
                temp = nullptr;
                //continue;
                break;          // This only takes the first member
            }
            //          break;
        }
        members.close();
    }
    else cout << "Unable to open file" << endl;
    return true;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    if (db.search(email)==nullptr)
        return nullptr;
    return *(db.search(email));
}

