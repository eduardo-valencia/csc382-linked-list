#include "main.h"

using namespace std;

// Node's constructor.
// Takes a pointer to data and instantiates the data, next, and previous properties.
template <typename Data>
Node<Data>::Node(Data data) : data{ data }, next{ nullptr }, previous{ nullptr }
{

}

// Returns a pointer to the data.
template <typename Data>
Data* Node<Data>::getData()
{
	return &data;
}

// Sets the data using a pointer.
template <typename Data>
void Node<Data>::setData(Data newData)
{
	data = newData;
}

// Gets the next node in the list.
template <typename Data>
Node<Data>* Node<Data>::getNext()
{
	return next;
}

// Sets the next node in the list.
template <typename Data>
void Node<Data>::setNext(Node<Data>* newNode)
{
	next = newNode;
}

// Gets previous node in the list.
template <typename Data>
Node<Data>* Node<Data>::getPrevious()
{
	return previous;
}

// Sets the previous node in the list.
template <typename Data>
void Node<Data>::setPrevious(Node<Data>* newNode)
{
	previous = newNode;
}

// LinkedList's constructor.
// Creates an empty head and tail node.
template <typename Data>
LinkedList<Data>::LinkedList(Data defaultValue)
{
	head = new Node<Data>{ defaultValue };
	tail = new Node<Data>{ defaultValue };
	head->next = tail;
	tail->previous = head;
}

// Returns list's head
template <typename Data>
Node<Data>* LinkedList<Data>::getHead()
{
	return head;
}

// Finds a node, given a pointer to data.
// Compare the data values, and not the pointers themselves.
// Returns either a null pointer or a pointer to the found node.
template <typename Data>
Node<Data>* LinkedList<Data>::Find(Data* data)
{
	Node<Data>* currentNode = getHead();
	while (currentNode->getNext() != nullptr)
	{
		currentNode = currentNode->getNext();
		Data* currentData = currentNode->getData();
		if (currentData != nullptr && *currentData == *data)
		{
			return currentNode;
		}
	}
	return nullptr;
}

// Inserts data, given a pointer to data.
// Creates a new node for the data and adds it to the end of the list.
template <typename Data>
void LinkedList<Data>::Insert(Data data)
{
	Node<Data>* lastNode = tail->getPrevious();
	lastNode->next = new Node<Data>{ data };
	lastNode->next->previous = lastNode;
	lastNode->next->next = tail;
	tail->previous = lastNode->next;
}

// Takes a pointer to a node and deletes the node from the list.
// Links the node's previous and next nodes together.
template <typename Data>
void LinkedList<Data>::Delete(Node<Data>* node)
{
	Node<Data>* previousNode = node->getPrevious();
	Node<Data>* nextNode = node->getNext();
	previousNode->next = nextNode;
	previousNode->next->previous = previousNode;
	delete node;
}