#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node {
    T data;
    Node<T> *next;
};

template <class T>
class Stack {
    private:
        Node <T> *top;
    
    public:
        Stack(): top(nullptr) {}

        ~Stack() {
        }

};

#endif