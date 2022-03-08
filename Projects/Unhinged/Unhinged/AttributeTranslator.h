//
//  AttributeTranslator.hpp
//  Unhinged
//
//  Created by Arsh Malik on 3/7/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include <string>
#include "RadixTree.h"
#include "provided.h"
#include <vector>

class AttributeTranslator
{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs( const AttValPair& source) const;
private:
    RadixTree<std::vector<AttValPair*>> CompatibleAttValPairs;
    std::vector<AttValPair*> ptrToAttValPairs;
};

#endif /* AttributeTranslator_h */
