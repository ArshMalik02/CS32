//#include "RadixTree.h"
//#include "PersonProfile.h"
//#include "provided.h"
//#include "MemberDatabase.h"
//#include <iostream>
//#include "AttributeTranslator.h"
//#include "MatchMaker.h"
//using namespace std;
//
//int main()
//{
////    AttributeTranslator ab;
////    ab.Load("/Users/arshmalik/Documents/Projects/CS32-Projects/Projects/Unhinged/Unhinged/translator.txt");
////    vector<AttValPair> test;
////    AttValPair source("trait","transparent");
////    test = ab.FindCompatibleAttValPairs(source);
////    for (int i = 0; i!= test.size(); i++)
////    {
////        cerr << test[i].attribute << endl;
////        cerr << test[i].value << endl;
////    }
////    MemberDatabase mdb;
////    mdb.LoadDatabase("/Users/arshmalik/Documents/Projects/CS32-Projects/Projects/Unhinged/Unhinged/members.txt");
////    AttValPair prof("job","accountant");
////    vector<string> emails = mdb.FindMatchingMembers(prof);
////    cerr << "--------------------------" << endl;
////    for (int i = 0; i!=emails.size(); i++)
////    {
////        cerr << emails[i] << endl;
////    }
////    RadixTree<AttValPair> rt;
////    AttValPair a1("hobby", "cricket");
////    AttValPair b1("hobby", "football");
////    AttValPair a2("age", "4");
////    rt.insert(a1.attribute, a1);
////    rt.insert(a2.attribute, a2);
////    rt.insert(b1.attribute, b1);
////    AttValPair* ptr = rt.search("hobby");
////    cerr << ptr->value << endl;
////    cerr << ptr->value << endl;
//}
//main.cpp


#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include "utility.h"

const std::string MEMBERS_FILE    = "/Users/arshmalik/Documents/Projects/CS32-Projects/Projects/Unhinged/Unhinged/testMembers.txt";
const std::string TRANSLATOR_FILE = "/Users/arshmalik/Documents/Projects/CS32-Projects/Projects/Unhinged/Unhinged/testTranslator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}
