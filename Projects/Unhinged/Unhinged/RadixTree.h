//
//  RadixTree.h
//  Unhinged
//
//  Created by Arsh Malik on 3/5/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <map>
#include <string>


template <typename ValueType>
class RadixTree {
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    std::map<std::string, ValueType> rt;
    std::map<std::string, ValueType>* rtPTR;
};

template <typename ValueType>
inline
RadixTree<ValueType>::RadixTree()
{
    rtPTR = &rt;
}

template <typename ValueType>
inline
RadixTree<ValueType>::~RadixTree()
{}

template <typename ValueType>
inline
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
    rt[key] = value;
}

template <typename ValueType>
inline
ValueType* RadixTree<ValueType>::search(std::string key) const
{
    typename std::map<std::string, ValueType>::iterator it;
    it = rtPTR->find(key);
    if  (it == rtPTR->end())
    {
        return nullptr;
    }
    return &(it->second);
}
#endif /* RadixTree_h */
