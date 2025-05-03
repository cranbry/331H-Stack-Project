#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node {
    T data;            // node for storing data
    Node<T> *next;     // pointer to next node

    Node(const T& d, Node<T>* n = nullptr) : data(d), next(n) {}
};

template <class T>
class Stack {
    private:
        Node <T> *top; // pointer to the top node
    
    public:
        // constructor for initializing empty stack
        Stack(): top(nullptr) {}
        
        // destructor for freeing dynamic memory
        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }

    // method to push a value onto the top of th stack
    void push(const T& value) {
        // new node with given value that points to top
        Node<T> *p = new Node<T>(value, top);

        // updating top pointer to new node;
        top = p;
    }

    T pop() {
        if (top != nullptr) {
            // saving value at top of stack
            T value = top->data;

            // saving current top node to delete
            Node<T>* temp = top;

            // updating top to point to next node
            top = top->next;

            // free memo of old top node
            delete temp;

            return value;

        } else {
            cout << "Stack is empty" << endl;
            return T(); // returns default value for T
        }
    }

    T peek() {
        if (top != nullptr) {
            return top->data;
        } else {
            cout << "Stack is empty" << endl;
            return T(); // returns default value for T
        }
    }

    void display() {
        Node<T>* p;

        if (top == nullptr) {
            cout << "Stack is empty" << endl;
        } else {
            p = top;
            cout << "Stack elements are: " << endl;

            // going thru the list and printing each value
            while(p != nullptr) {
                cout << p->data << endl;
                p = p->next; 
            }
            cout << endl;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// InfixEval class for evaluating arithmetic 
// expressions in infix notation without converting it to postfix

class InfixEval {
    private:
        int precedence(char op) {
            if(op == '+'||op == '-') {
                return 1;
            }
            if(op == '*'||op == '/') {
                return 2;
            }
            return 0;
        }

    // operations with two operands
    int applyOp(int a, int b, char op) {
        switch(op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0) {
                    cout << "Division by 0 is not possible" << endl;
                    exit(1);
                } else {
                    return a / b;
                }
            default:
                return 0; // should not come to this if expression is valid
        }
    }

    bool processOperator(Stack<int>& numberStack, Stack<char>& opStack) {
        // first check for enough operands
        if (numberStack.isEmpty()) {
            cout << "Not enough operands for operator " << opStack.peek() << endl;
            return false;
        }

        int b = numberStack.pop();  // operand #2
        
        if (numberStack.isEmpty()) {
            cout << "Not enough operands for operator " << opStack.peek() << endl;
            return false;
        }
        int a = numberStack.pop();  // operand #1
        
        // get operator and call applyOp to apply it
        char op = opStack.pop();
        int result = applyOp(a, b, op);
        
        // pushing result onto stack
        numberStack.push(result);

        return true;
    }
    
    bool processNumber(const string &expr, int &index, Stack<int> &numberStack) {
        bool isNegative = false;

        if (expr[index] == '-') {
            isNegative = true;
            index++; // moving past the '-' sign

            // making sure there is digit after minus sign
            if (index >= expr.length() || !isdigit(expr[index])) {
                cout << "Number format is not valid" << endl;
                return false;
            }
        }
        
        // parsing the number
        int num = 0;
        while (index < expr.length() && isdigit(expr[index])) {
            num = num * 10 + (expr[index] - '0');
            index++;
        }

        // applying negative sign if needed
        if (isNegative) {
            num = -num;
        }

        // pushing num into the stack
        numberStack.push(num);

        // adjusting index because we've gone one character too far
        index--;
        return true;
    } 

    bool processParenthesis(Stack<int> &numberStack, Stack<char> &opStack) {
        // Process all operators until the matching opening parenthesis
        while (!opStack.isEmpty() && opStack.peek() != '(') {
            if (!processOperator(numberStack, opStack)) {
                return false;
            }
        }
        
        // Remove the opening parenthesis
        if (!opStack.isEmpty()) {
            opStack.pop();  // Pop '('
        } else {
            cout << "Mismatched parentheses or missing opening parenthesis" << endl;
            return false;
        }
        
        return true;
    }

    public:
        void evaluateExpression(const string &input) {
            // creating two stacks one for operands and one for operators
            Stack<int> numberStack;  // operands
            Stack<char> opStack;     // operators

            int index = 0;
            // processing each character in the input string
            while (index < input.length()) {
                char currentChar = input[index];

                // skipping spaces
                if (isspace(currentChar)) {
                    index++;
                    continue;
                }
                
                // Handle numbers (including negative numbers)
                if (isdigit(currentChar) || 
                   (currentChar == '-' && (index == 0 || 
                                         input[index-1] == '(' || 
                                         input[index-1] == '+' || 
                                         input[index-1] == '-' || 
                                         input[index-1] == '*' || 
                                         input[index-1] == '/'))) {
                    if (!processNumber(input, index, numberStack)) {
                        return; // error in number processing
                    }
                }
                // Handle opening parenthesis
                else if (currentChar == '(') {
                    opStack.push(currentChar);
                }
                // Handle closing parenthesis
                else if (currentChar == ')') {
                    if (!processParenthesis(numberStack, opStack)) {
                        return;  // error in parenthesis processing
                    }
                }
                // Handle operators
                else if (currentChar == '+' || currentChar == '-' || 
                         currentChar == '*' || currentChar == '/') {
                    
                    // Process operators with higher or equal precedence
                    while (!opStack.isEmpty() && 
                           precedence(opStack.peek()) >= precedence(currentChar) && 
                           opStack.peek() != '(') {
                        
                        if (!processOperator(numberStack, opStack)) {
                            return;  // error in operator processing
                        }
                    }
                    // push currentChar onto stack
                    opStack.push(currentChar);
                }
                // hadnling invalid characters
                else {
                    cout << "Invalid character '" << currentChar << "' at position " << index << endl;
                    return;
                }
                
                // move to next char
                index++;
            }
            
            // processing any remaining operators
            while (!opStack.isEmpty()) {
                // checking for errors in mismatched parentheses
                if (opStack.peek() == '(' || opStack.peek() == ')') {
                    cout << "Mismatched parentheses or missing closing parenthesis" << endl;
                    return;
                }
                
                if (!processOperator(numberStack, opStack)) {
                    return;  // error in operator processing
                }
            }
            
            // checking if evaluation was successful
            if (numberStack.isEmpty()) {
                cout << "Invalid expression or no result produced" << endl;
                return;
            }
            
            // final result
            int result = numberStack.pop();
            
            // checking for extra operands
            if (!numberStack.isEmpty()) {
                cout << "Expression has extra operands" << endl;
            }
            
            // print final result
            cout << "Result: " << result << endl;
        }
};

#endif