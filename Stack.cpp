#include "Stack.h"

template <class T>
Stack<T>::Stack() : List<T>() {    }

template <class T>
bool Stack<T>::isEmpty() const {  return List<T>::isEmpty();  }

template <class T>
int Stack<T>::size() {  return List<T>::size();  }

template <class T>
void Stack<T>::push(const T& value) {  List<T>::push_back(value);  }

template <class T>
void Stack<T>::pop(){  List<T>::pop_back();  }

template <class T>
T Stack<T>::topAndPop() {
        T tmp;
        tmp = List<T>::getBack();
        pop();
        return tmp;
}

template <class T>
T Stack<T>::getTop() {  return List<T>::getBack();   }

template <class T>
void Stack<T>::print() const {  List<T>::print();   }
