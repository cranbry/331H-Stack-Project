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
        }

    // method to push a value onto the top of th stack
    void push(const T& value) {
        // new node with given value that points to top
        Node<T> *p = new Node<T>{value, top}; 

        // updating top pointer to new node;
        top = p;
    }

};

#endif