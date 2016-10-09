#include "Postfix.h"
#include <math.h>
#include <string>
//#define DEBUG
//
//RUBEN CUADRA A01019102
//
//
Postfix::Postfix(std::string expression)
{
    setData(expression);
}

void Postfix::setData(std::string expression)
{
    infix_expression = expression;
    postfix_expression = "";
    convertExpression();
}

std::string Postfix::getInfix()
{
    return infix_expression;
}

std::string Postfix::getPostfix()
{
    return postfix_expression;
}

/*
 Returns an integer value indicating if an operator has higher precedence than another.
 Positive values indicate higher precedence.
 Negative values indicate lower precedence.
 A value of 0 indicates equal precedence.
 */
int Postfix::precedence(char current_operator, char other_operator)
{
    char operators[] = { '^', '*', '/', '%', '+', '-', '(' };
    int values[] = { 3, 2, 2, 2, 1, 1, 0 };
    int current_value;
    int other_value;
    
    for (int i = 0; i < 7; i++)
    {
        if (current_operator == operators[i])
        {
            current_value = values[i];
        }
        if (other_operator == operators[i])
        {
            other_value = values[i];
        }
    }
#ifdef DEBUG
    std::cout << "Comparing: " << current_operator << " and " << other_operator << " . result = " << current_value - other_value << std::endl;
#endif
    return current_value - other_value;
}

void Postfix::convertExpression()
{
    char token;
    Stack<char> conversion_stack;
    Node<char> * item;
    
    for (int i = 0; i < infix_expression.length(); i++)
    {
        // Get the next character in the expression
        token = infix_expression[i];
        // Pass operands directly to the postfix string
        if (token >= '0' && token <= '9')
        {
#ifdef DEBUG
            std::cout << "Found an operand: " << token << std::endl;
#endif
            postfix_expression += token;
        }
        // Store opening parenthesis in the stack
        else if (token == '(')
        {
#ifdef DEBUG
            std::cout << "Found opening : " << token << std::endl;
#endif
            conversion_stack.push(token);
        }
        // Pop everything in the stack until finding a matching parenthesis
        else if (token == ')')
        {
#ifdef DEBUG
            std::cout << "Found closing : " << token << std::endl;
#endif
            item = conversion_stack.top();
            while (item != nullptr && item->getData() != '(')
            {
                postfix_expression += item->getData();
                conversion_stack.pop();
                item = conversion_stack.top();
            }
            // Get rid of the matching parenthesis
            if (item->getData() == '(')
            {
                conversion_stack.pop();
            }
        }
        // Put operators in the stack depending on their precedence
        else if (token == '^' || token == '*' || token == '/' || token == '%' || token == '+' || token == '-')
        {
#ifdef DEBUG
            std::cout << "Found an operator: " << token << std::endl;
#endif
            // Compare against any operator in the stack
            if (!conversion_stack.isEmpty())
            {
                // Test whether the current token is higher or lower precedence
                item = conversion_stack.top();
                while (item != nullptr && precedence(token, item->getData()) <= 0)
                {
                    postfix_expression += item->getData();
                    conversion_stack.pop();
                    item = conversion_stack.top();
                }
            }
            conversion_stack.push(token);
#ifdef DEBUG
            conversion_stack.printList();
#endif
        }
    }
    // Put every operator still in the stack in the postfix expression
    while (!conversion_stack.isEmpty())
    {
        item = conversion_stack.pop();
        postfix_expression += item->getData();
    }
}

int Postfix::evaluate()
{
    Stack<int> postStack;
    char token;
    for (int i = 0; i < postfix_expression.length(); i++)
    {
        token = postfix_expression[i];
        postStack.push(token>='0'&&token<='9'?token-'0':compute(postStack.pop()->getData(),postStack.pop()->getData(),token));
    }
    return postStack.top()->getData();
}

int Postfix::compute(int num1, int num2, char sign)
{
    return sign=='^'?pow(num2,num1):sign=='*'?num2*num1:sign=='/'?num2/num1:sign=='%'?num2%num1:sign=='+'?num2+num1:sign=='-'?num2-num1:0;}
