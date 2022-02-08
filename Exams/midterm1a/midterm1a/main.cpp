#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class StringList
{
  public:
    StringList(string text);
    // You may declare other member functions for your test code to call
    void eraseThrees();
    void dump();
  private:
    struct Node
    {
      char  value;
      Node* next;
      Node(char v, Node* n) : value(v), next(n) {}
    };
    Node* head;  // points to first Node in the list
};

StringList::StringList(string text)
{
    //  For example, StringList s("heap"); creates s containing
    //  a list with values  'h'  'e'  'a'  'p'
  head = nullptr;
  for (int k = text.size(); k > 0; k--)
    head = new Node(text[k-1], head);
}

// You may implement other member functions here for test purposes,
// but you will not turn them in as part of your submission.

void StringList::dump()
{
    for (Node* p = head; p!=nullptr; p= p->next)
    {
        cerr << p->value;
    }
    cerr << endl;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE eraseThrees IMPLEMENTATION

void StringList::eraseThrees()
{
    int count = 1;
    Node* p;
    for (p = head; p!= nullptr; p=p->next)
    {
        if (p->next!=nullptr && (count+1)%3==0)
        {
            Node* temp = p->next;
            p->next = temp->next;
            count++;
            delete temp;
        }
        count++;
    }
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE eraseThrees IMPLEMENTATION

int main()
{
  StringList x("treachery");
    x.dump();
  x.eraseThrees();
  // You might put some code here for test purposes, e.g., to verify
  // that x now contains  't'  'r'  'a'  'c'  'e'  'r'
  // You might run some other tests.
    x.dump();
  cout << "Program finished" << endl;
}
