#pragma once
#include "Node.h"

template <typename Data>
class LinkedList
{
private:
	Node<Data>* head;
	Node<Data>* tail;

public:
	LinkedList();

	Node<Data>* getHead();

	Node<Data>* Find(Data* data);

	void Insert(Data data);

	void Delete(Node<Data>* node);
};