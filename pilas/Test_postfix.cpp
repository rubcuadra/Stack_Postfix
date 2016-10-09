#include <iostream>
#include "Postfix.h"

int main()
{
	std::string expression = "(8+(2-1^30/12)*9)*(7^2)-5";
    std::cout << expression<<"\n";
	Postfix postfix(expression);

	// Show the contents of the current expression
	std::cout << "Infix: " << postfix.getInfix().c_str() << std::endl;
	std::cout << "Postfix: " << postfix.getPostfix().c_str() << std::endl;
	std::cout << "Evaluation: " << postfix.evaluate() << std::endl;
	return 0;
}