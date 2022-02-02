
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
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
                                        pf == "ae+"  &&  answer == -6);
                answer = 999;
                assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("a+(-a+e)(i+o)", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("a+()", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
                  // unary operators not allowed:
                assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
                assert(evaluate("a*b", m, pf, answer) == 2  &&
                                        pf == "ab*"  &&  answer == 999);
                assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                                        pf == "yoau-*+"  &&  answer == -1);
                answer = 999;
                assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                                        pf == "oyy-/"  &&  answer == 999);
                assert(evaluate(" a  ", m, pf, answer) == 0  &&
                                        pf == "a"  &&  answer == 3);
                assert(evaluate("((a))", m, pf, answer) == 0  &&
                                        pf == "a"  &&  answer == 3);
    assert(evaluate("(a+o )* i)/((a / i)", m, pf, answer)==1);
            cout << "Passed all tests" << endl;
        }

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    // Step 1: Converting infix to postfix and also checking for syntax of infix string
    stack<char> operators;
    string pf = "";
    string infixNoSpace = removeSpace(infix);
    bool infixStatus = true;
    int returnVal = 1;
    
    if (infixNoSpace == "")
    {
        return 1;
    }
    
    if (checkMismatchedBrackets(infixNoSpace)==false)
        return 1;
    
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
                if (isalpha(infixNoSpace[i-1]) || infixNoSpace[i-1] == ')')
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
                if (isalpha(infixNoSpace[i-1]) || infixNoSpace[i-1] == ')')
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
                if (infixNoSpace[i-1] == '(' || isOperator(infixNoSpace[i-1]))
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
                if (infixNoSpace[i-1] == '(' || isOperator(infixNoSpace[i-1]))
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
    
    postfix = pf;
    
    if (infixStatus==false)
        return returnVal;
    
    for (int i = 0; i != postfix.size(); i++)
    {
        if (isalpha(postfix[i]) && !values.contains(postfix[i]))
            return 2;
    }
    
    
    // Step 2: Evaluate the postfix
    
    stack<int> operands;
    for (int i = 0; i != postfix.size(); i++)
    {
        char ch = postfix[i];
        if (isalpha(ch))
        {
            int v;
            values.get(ch, v);
            operands.push(v);
        }
        else
        {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            
            // Applying the operation
            switch (ch) {
                case '+':
                    operands.push(operand1+operand2);
                    break;
                case '-':
                    operands.push(operand1-operand2);
                    break;
                case '*':
                    operands.push(operand1*operand2);
                    break;
                case '/':
                    if (operand2==0)
                    {
                        return 3;
                    }
                    operands.push(operand1/operand2);
                default:
                    break;
            }
        }
    }
    result = operands.top();
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
            break;
        case '/':
            if (top == '*' || top == '/')
                return true;
            break;
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
