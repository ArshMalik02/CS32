#ifndef RadixTree_h
#define RadixTree_h

#include <string>
#include <vector>

template <typename ValueType>
class RadixTree {
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    struct Node
    {
        // Node constructor
        Node()
        {
            for (int i = 0; i!= 128; i++)
                arr[i] = nullptr;
            endOfWord = false;
        }
        
        Node(std::string key, const ValueType& value)
        {
            m_word = key;
            m_value = value;
            endOfWord = true;
            for (int i = 0; i!= 128; i++)
                arr[i] = nullptr;
        }
        
        std::string m_word;
        ValueType m_value;
        bool endOfWord;
        Node* arr[128];
    };
    Node* root;
    void deleteTree(Node* pair);
    void insertHelper(std::string key, const ValueType& value, Node* &child, Node* &parent);
};

template <typename ValueType>
inline
RadixTree<ValueType>::RadixTree()
{
    root = new Node;
}

template <typename ValueType>
inline
void RadixTree<ValueType>::deleteTree(Node* pair)
{
    for (int i = 0; i!=128; i++)
    {
        if (pair->arr[i] == nullptr)
            continue;
        else
        {
            Node* nodeToDelete = pair->arr[i];
            deleteTree(nodeToDelete);
            delete nodeToDelete;
        }
    }
}

template <typename ValueType>
inline
RadixTree<ValueType>::~RadixTree()
{
    deleteTree(root);
    delete root;
}

template <typename ValueType>
inline
void RadixTree<ValueType>::insertHelper(std::string key, const ValueType& value, Node* &child, Node* &parent)
{
    if (key.size()==0)
        return;
    if (child == nullptr)
    {
        child = new Node(key, value);
    }
    else
    {
        std::string wordAlreadyInTree = child->m_word;
        std::string commonPrefix = "";
        int i1 = 0; int i2 = 0;
        while (i1<wordAlreadyInTree.size() && i2 < key.size())
        {
            if (wordAlreadyInTree[i1] == key[i2])
            {
                commonPrefix+=wordAlreadyInTree[i1];
            }
            else
                break;
            i1++;
            i2++;
        }
        if (i1==wordAlreadyInTree.size() && i2!=key.size())  // The entire wordAlreadyInTree is a prefix of key
        {
            std::string partToBeAdded = key.substr(i2,key.size()-1);
            int indexOfAddition = key[i2];
            insertHelper(partToBeAdded, value, child->arr[indexOfAddition], child);
        }
        else if (i2==key.size() && i1 != wordAlreadyInTree.size())
        {
            // Updating the current child
            // slower
            // slow break slower into slow and er
            // slo break into slo and w
            std::string stringAfterFactorOutPrefix = wordAlreadyInTree.substr(i1, wordAlreadyInTree.size()-1);
            int indexOfAddition = stringAfterFactorOutPrefix[0];
            ValueType valueOfCurrentWord = child->m_value;
            child->m_value = value;
            child->m_word = key;
            std::vector<int> idChildrenToBeMoved;
            Node* childrenToBeMoved[128];
            for (int i = 0; i!=128; i++)
            {
                if (child->arr[i] != nullptr)
                {
                    childrenToBeMoved[i] = child->arr[i];
                    idChildrenToBeMoved.push_back(i);
                    child->arr[i] = nullptr;
                }
            }
            
            // creating new node
            child->arr[indexOfAddition] = new Node(stringAfterFactorOutPrefix, valueOfCurrentWord);
            for (int i = 0; i!=idChildrenToBeMoved.size(); i++)
            {
                child->arr[indexOfAddition]->arr[idChildrenToBeMoved[i]] = childrenToBeMoved[idChildrenToBeMoved[i]];
            }
        }
        else if (i1!=wordAlreadyInTree.size() && i2!=key.size())
        {
            // splitting the curent word in the node and the key being inserted
            std::string currentWordLeftAfterPrefix = wordAlreadyInTree.substr(i1, wordAlreadyInTree.size()-1);
            std::string keyLeftAfterPrefix = key.substr(i2,key.size()-1);
            
            // Adding a new node for the currentWordLeft and updating the word
            child->m_word = wordAlreadyInTree.substr(0,i1);
            child->endOfWord = false;
            std::vector<int> idChildrenToBeMoved;
            Node* childrenToBeMoved[128];
            for (int i = 0; i!=128; i++)
            {
                if (child->arr[i] != nullptr)
                {
                    childrenToBeMoved[i] = child->arr[i];
                    idChildrenToBeMoved.push_back(i);
                    child->arr[i] = nullptr;
                }
            }
            int indexOfAddition = currentWordLeftAfterPrefix[0];
            child->arr[indexOfAddition] = new Node(currentWordLeftAfterPrefix, child->m_value);
            for (int i = 0; i!=idChildrenToBeMoved.size(); i++)
            {
                child->arr[indexOfAddition]->arr[idChildrenToBeMoved[i]] = childrenToBeMoved[idChildrenToBeMoved[i]];
            }
            
            // Adding a new node for the left part of the key
            insertHelper(keyLeftAfterPrefix, value, child->arr[keyLeftAfterPrefix[0]], child);
        }
        else
        {
            child->m_value = value;
            child->endOfWord = true;
        }
    }
}

template <typename ValueType>
inline
void RadixTree<ValueType>::insert(std::string key, const ValueType& value)
{
    if (key.size()==0)
        return;
    int index = key[0];
    insertHelper(key, value, root->arr[index], root);
}

template <typename ValueType>
inline
ValueType* RadixTree<ValueType>::search(std::string key) const
{
    return nullptr;
}


#endif /* RadixTree_h */
