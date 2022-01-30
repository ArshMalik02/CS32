
#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
string removeSpace(string s);
bool isOperator(char c);
bool checkPrecedence(char x, stack<char> &opStack);
bool checkMismatchedBrackets(string str);

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("((a))", m, pf, answer) == 0  &&
                                        pf == "a");
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    // Step 1: Converting infix to postfix and also checking for syntax of infix string
    stack<char> operators;
    string pf = "";
    string infixNoSpace = removeSpace(infix);
    bool infixStatus = true;
    int returnVal = 1;
    
    if (infix == "")
    {
        return 1;
    }
    
    for (int i = 0; i != infixNoSpace.size(); i++)
    {
        char ch = infixNoSpace[i];
        if (!isalpha(ch) && ch!='+' && ch!='-' && ch!='*' && ch!='/' && ch!='(' && ch!=')')
        {
            returnVal = 1;
            infixStatus = false;
            break;
        }
        else if (isalpha(ch))
        {
            if (isupper(ch))
            {
                returnVal = 1;
                infixStatus = false;
                break;
            }
            else if (i!=0)
            {
                if (isalpha(infixNoSpace[i-1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            else if (i!=infixNoSpace.size()-1)
            {
                if (isalpha(infixNoSpace[i+1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            
            pf+=ch;
        
        }
        
        else if (ch == '(')
        {
            if (i == infixNoSpace.size()-1)
            {
                returnVal = 1;
                infixStatus = false;
                break;
            }
            
            else if (i!=0)
            {
                if (isalpha(infixNoSpace[i-1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            else if (i != infixNoSpace.size()-1)
            {
                if (isOperator(infixNoSpace[i+1]) || infixNoSpace[i+1] == ')')
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            
            operators.push(ch);
            
        }
        else if (ch == ')')
        {
            if (i!=0)
            {
                if (isOperator(infixNoSpace[i-1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            else if (i != infixNoSpace.size()-1)
            {
                if (isalpha(infixNoSpace[i+1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            
            while (operators.top()!='(')
            {
                pf += operators.top();
                operators.pop();
            }
            operators.pop();
            
        }
        else if (isOperator(ch))
        {
            if (i == 0)
            {
                returnVal = 1;
                infixStatus = false;
                break;
            }
            else if (i == infixNoSpace.size()-1)
            {
                returnVal = 1;
                infixStatus = false;
                break;
            }
            else if (i!=0)
            {
                if (isOperator(infixNoSpace[i-1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            else if (i != infixNoSpace.size()-1)
            {
                if (isOperator(infixNoSpace[i+1]))
                {
                    returnVal = 1;
                    infixStatus = false;
                    break;
                }
            }
            while (!operators.empty() && operators.top()!='(' && checkPrecedence(ch, operators))
            {
                pf += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }
    
    while (!operators.empty())
    {
        pf += operators.top();
        operators.pop();
    }
    cerr << pf << endl;
    postfix = pf;
    if (infixStatus==false || checkMismatchedBrackets(pf) == false)
        return returnVal;
    
    // Step 2: Evaluate the postfix
    
    
    return 0;
}


string removeSpace(string s)
{
    string val = "";
    for (int i = 0; i!=s.size(); i++)
    {
        if (s[i] != ' ')
        {
            val+=s[i];
        }
    }
    return val;
}


bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*')
        return true;
    return false;
}

bool checkPrecedence(char x, stack<char> &opStack)
{
    char top = opStack.top();
    switch (x) {
        case '+':
            if (top == '-' || top == '+')
                return true;
            break;
        case '-':
            if (top == '-' || top == '+')
                return true;
            break;
        case '*':
            if (top == '*' || top == '/')
                return true;
        case '/':
            if (top == '*' || top == '/')
                return true;
        default:
            break;
        
    }
    return false;
}

bool checkMismatchedBrackets(string str)
{
    stack<char> vals;
    bool returnVal = true;
    
    for (int i = 0; i!=str.size(); i++)
    {
        if (str[i] == '(')
            vals.push('(');
        else if (str[i] == ')')
        {
            if (!vals.empty())
            {
                char topVal = vals.top();
                vals.pop();
                if (topVal != '(')
                {
                    returnVal = false;
                    break;
                }
            }
            else
            {
                returnVal = false;
                break;
            }
        }
    }
    if (!vals.empty())
        returnVal = false;
    return returnVal;
}
