//
//  main.cpp
//  HW 2 Q 5
//
//  Created by Joseph Picchi on 4/27/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <cassert>
using namespace std;

// declarations of additional functions
bool convertToPostfix(string& infix, string& postfix);
bool prevValid(const char& prev, const char& current);
bool evalPostfix(const string& postfix, bool& result);
    // return true if the computation was successful, false otherwise
    // store the final answer in "result" if it's successful
char binaryOperationResult(const char& operand1, const char& operand2, const char& operator_);
    // returns 0 for false, 1 for true, -1 for invalid postfix notation


int evaluate(string infix, string& postfix, bool& result)
{
    // empty expressions are invalid
    if (infix.empty())
        return 1;
    
    // convert infix to postfix - check if the conversion was successful
    if (!convertToPostfix(infix, postfix))
        return 1;
    
    // evaluate the postfix string
    if (!evalPostfix(postfix, result))
        return 1;
    
    // tasks completed successfully
    return 0;
}
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.



// put an infix expression in postfix form:
// returns true if successful, false if not
bool convertToPostfix(string& infix, string& postfix)
{
    // initialize postfix to empty
    postfix = "";
    stack<char> operatorStack;
    
    char ch = ' ';
    char chBefore = ' ';
    size_t size = infix.size();
    
    // loop through each character in the infix string
    for (int i = 0; i < size; i++)
    {
        // get the current character
        ch = infix.at(i);
        
        // check if current char is allowed to follow previous char
        if (!prevValid(chBefore, ch))
            return false;
        
        switch (ch) {
            case 'T':
            case 'F':
                // append to postfix
                postfix += ch;
                break;
                
            case '!':
            case '(':
                // push it to the stack
                operatorStack.push(ch);
                break;
                
            case ')':
                
                // pop the stack until you reach '('
                while (!operatorStack.empty() && operatorStack.top() != '(')
                {
                    // append to postfix
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                
                // empty is invalid bc there's no corresponding '('
                if (operatorStack.empty())
                    return false;
                
                // pop the '('
                operatorStack.pop();
                break;
                
            case '&':
                while (!operatorStack.empty() && (operatorStack.top() == '!' || operatorStack.top() == '&'))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                
                operatorStack.push(ch);
                break;
                
            case '^':
                // pop the stack if precedence of ch <= precedence of top
                while (!operatorStack.empty() && operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                
                operatorStack.push(ch);
                break;
                
            case ' ':
                break;
                
            default:
                return false;
        }
        
        if (ch != ' ')
            chBefore = ch;
    }
    
    // empty out the stack
    while (!operatorStack.empty())
    {
        // can't have '(' without ')'
        if (operatorStack.top() == '(')
            return false;
        
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    
    // operation completed successfully
    return true;
}






// check if the following char can follow the previous one
bool prevValid(const char& prev, const char& current)
{
    switch (current)
    {
        case '!':
            if (prev == 'T' || prev == 'F' || prev == ')')
                return false;
            else
                return true;
            
        case '&':
        case '^':
            if (prev == '!' || prev == '&' || prev == '^' || prev == '(' || prev == ' ')
                return false;
            else
                return true;
            
        case 'T':
        case 'F':
            if (prev == ')' || prev == 'T' || prev == 'F')
                return false;
            else
                return true;
            
        case '(':
            if (prev == 'F' || prev == 'T' || prev == ')')
                return false;
            else
                return true;
            
        case ')':
            if (prev == '!' || prev == '&' || prev == '^' || prev == '(' || prev == ' ')
                return false;
            else
                return true;
            
        case ' ':
            return true;
            
        default:
            return false;
    }
}



// outut the result of an operation, given two operands and an operator
char binaryOperationResult(const char& operand1, const char& operand2, const char& operator_)
{
    char result = ' ';
    
    if (operator_ == '&')
    {
        if (operand1 == 'T' && operand2 == 'T')
            result = 'T';
        else
            result = 'F';
    }
    else if (operator_ == '^')
    {
        if ((operand1 == 'T' && operand2 == 'F') || (operand1 == 'F' && operand2 == 'T'))
            result = 'T';
        else
            result = 'F';
    }
    
    return result;
}




// produce a final result given a string in postfix form
bool evalPostfix(const string& postfix, bool& result)
{
    // initialize operand stack to empty
    stack<char> operandStack;
    
    size_t size = postfix.size();
    char ch;
    
    // for each character ch in postfix
    for (int i = 0; i < size; i++)
    {
        ch = postfix[i];
        
        if (ch == 'T' || ch == 'F')                 // ch is an operand
            operandStack.push(ch);
        else if (ch == '&' || ch == '^')            // ch is a binary operator
        {
            // invalid if there's not enough items
            if (operandStack.size() < 2)
                return false;
            
            // set operand2 to the top of the operand stack
            char operand2 = operandStack.top();
            operandStack.pop();
            
            // set operand1 to the top of the operand stack
            char operand1 = operandStack.top();
            operandStack.pop();
            
            // apply the operation and push the result
            operandStack.push(binaryOperationResult(operand1, operand2, ch));
        }
        else if (ch == '!')
        {
            // there must be an item before '!'
            if (operandStack.empty())
                return false;
            
            // get the top item
            char top = operandStack.top();
            operandStack.pop();
            
            // apply '!' to it
            if (top == 'T')
                top = 'F';
            else if (top == 'F')
                top = 'T';
            
            operandStack.push(top);
        }
    }
    
    // the operand stack should contain 1 item once the loop finishes
    if (operandStack.size() != 1)
        return false;
    
    // translate char to bool
    if (operandStack.top() == 'F')
        result = false;
    else if (operandStack.top() == 'T')
        result = true;
    else
        return false;
    
    // computation was successful
    return true;
}
