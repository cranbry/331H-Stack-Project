#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

/**
 * Main program for the infix expression evaluator:
 
 - This program takes as input a numeric expression in infix notation, such as 3+4*2, 
   and outputs the result using stacksto evaluate arithmetic expressions in infix notation 
   without converting it into postfix notation. 

    * * * * * *  * * * *

 * Supported features:

  - Basic arithmetic operations: +, -, *, /
  - Parentheses for grouping expressions
  - Negative numbers
  - Spaces in the expression are ignored

    * * * * * *  * * * *

 * Sample test cases:

  - 3+4*2         (Result: 11)
  - 3*(4-2)+6     (Result: 12)
  - -5+10         (Result: 5)
  - (3+4)*(5-2)   (Result: 21)

 */

int main() {

    cout << "This program evaluates arithmetic expressions in infix notation." << endl;
    cout << "Supports: +, -, *, /" << endl;
    cout << "You can use parentheses and negative numbers." << endl << endl;
    
    // input from user
    string expression;
    cout << "Enter an infix expression to evaluate: ";
    getline(cin, expression);  // reading all to find spaces
    
    // eval object
    InfixEval evaluator;
    
    // evaluate expression and display result
    evaluator.evaluateExpression(expression);
    
    return 0;

}