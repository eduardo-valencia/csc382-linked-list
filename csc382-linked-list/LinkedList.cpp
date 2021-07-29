#include "pch.h"
#include "LinkedList.h"

template <typename Data>
LinkedList<Data>::LinkedList()
{
	head = new Node<Data>{};
	Node<Data> tail{};
	head->linkToNode(tail);
}

template <typename Data>
Node<Data>* LinkedList<Data>::getHead()
{
	return head;
}

template <typename Data>
Node<Data>* LinkedList<Data>::find(Data* data)
{
	Node<Data>* currentNode = getHead();
	while (currentNode->getNext() != nullptr)
	{
		if (*(currentNode->getData()) == *data)
		{
			return currentNode;
		}
		currentNode = currentNode->getNext()
	}
	return nullptr;
}

template <typename Data>
void LinkedList<Data>::insert(Data* data)
{
	Node<Data>* endOfList = getHead();
	while (endOfList->getNext() != nullptr)
	{
		endOfList = endOfList->getNext();
	}
	Node<Data> nodeWithData{data};
	Node<Data>* lastNode = endOfList->getPrevious();
	lastNode->linkToNode(nodeWithData);
	nodeWithData.linkToNode(endOfList);
}

template <typename Data>
void LinkedList<Data>::Delete(Node<Data>* node)
{
	Node<Data>* previousNode = node->getPrevious();
	Node<Data>* nextNode = node->getNext();
	previousNode->linkToNode(nextNode);
	delete node;
}