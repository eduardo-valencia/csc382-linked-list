#include "Node.h"

template <typename Data>
Node<Data>::Node(Data* data) : data{ data }, next{ nullptr }, previous{ nullptr }
{

}

template <typename Data>
Data* Node<Data>::getData()
{
	return data;
}

template <typename Data>
void Node<Data>::setData(Data* newData)
{
	data = newData
}

template <typename Data>
Node<Data>* Node<Data>::getNext()
{
	return next;
}

template <typename Data>
void Node<Data>::setNext(Node<Data>* newNode)
{
	next = newNode;
}

template <typename Data>
Node<Data>* Node<Data>::getPrevious()
{
	return previous;
}

template <typename Data>
void Node<Data>::setPrevious(Node<Data>* newNode)
{
	previous = newNode;
}

template <typename Data>
void Node<Data>::linkToNode(Node<Data>* newNextNode)
{
	setNext(newNextNode);
	newNextNode->setPrevious = this;
}