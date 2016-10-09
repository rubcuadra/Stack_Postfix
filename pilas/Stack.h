/*
    Gilberto Echeverria

    Implementation of the Stack as a subclass of LinkedList
*/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "LinkedList.h"

template <class T>
class Stack : public LinkedList<T> {
    public:
        Node<T> * pop();
        Node<T> * top();
        void push(Node<T> * new_item);
        void push(const T & data);
		bool isEmpty();
};

/*
   Get the item that was last inserted into the stack
*/
template <class T>
Node<T> * Stack<T>::pop()
{
    return LinkedList<T>::removeHead();
}

template <class T>
Node<T> * Stack<T>::top()
{
    return LinkedList<T>::getHead();
}


template <class T>
void Stack<T>::push(Node<T> * new_item)
{
    LinkedList<T>::insertHead(new_item);
}

template <class T>
void Stack<T>::push(const T & data)
{
    Node<T> * item = new Node<T>(data);
    LinkedList<T>::insertHead(item);
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (this->head == nullptr)
		return true;
	return false;
}
#endif
