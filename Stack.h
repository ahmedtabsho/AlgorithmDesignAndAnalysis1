#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "List.h"
#include "List.cpp"

template <class T>
class Stack : private List<T> {
public:
    Stack();
    bool isEmpty() const;
    int size();
    void push(const T& value); // eleman ekleme
    void pop(); // ust elemani cikariyor
    T topAndPop(); // ust elemani dondurup siliyor
    T getTop() ; // ust elemani veriyor
    void print() const;
};


#endif // STACK_H_INCLUDED
