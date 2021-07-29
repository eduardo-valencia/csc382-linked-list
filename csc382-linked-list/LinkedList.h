#pragma once
#include "Node.h"

template <typename Data>
class LinkedList
{
private:
	Node<Data>* head;

public:
	LinkedList();

	Node<Data>* getHead();

	Node<Data>* find(Data* data);

	void insert(Data* data);

	void Delete(Node<Data>* node);
};