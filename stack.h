#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node {
    T data;            // node for storing data
    Node<T> *next;     // pointer to next node
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
        Node<T> *p = new Node<T>{value, top}; 

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

                    cout << "Division is not possible" << endl;
                    exit(1);
                }  else {
                    return a / b;
                }
            default:
                return 0; // should not come to this if expression is valid
        }
    }

    public:
        void evaluateExpression(const string &input) {
            // creating two stacks one for operands and one for operators
            Stack<int> numberStack;  // operands
            Stack<char> opStack;     // operators

            int inputLength = input.length();
            // processing each character in the input string
            for(int i = 0; i < inputLength; i++) {
                char c = input[i];

                if (isspace(c)) {
                    continue;
                } 
                // checking for numbers / can be neg
                // - sign at start for neg nums or after an operator or opening "()"
                if (isdigit(c) || (c == '-' && (i == 0 || 
                              input[i-1] == '(' || 
                              input[i-1] == '+' || 
                              input[i-1] == '-' || 
                              input[i-1] == '*' || 
                              input[i-1] == '/'))) {
                // for negative numbers
                bool isNegative = false;
                if (c == '-') {
                    isNegative = true;
                    i++;  // moving to next char after minus sign
                    
                    // checking if there is digit after minus sign
                    if (i >= input.length() || !isdigit(input[i])) {
                        cout << "Error: Invalid negative number format" << endl;
                        return;
                    }
                    c = input[i];  // update char
                }
            }
        }

};

#endif