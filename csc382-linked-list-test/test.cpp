#include "pch.h"
#include <gtest/gtest.h>
#include "../csc382-linked-list-2/LinkedList.h"

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
	data = newData;
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
	newNextNode->setPrevious(this);
}

template <typename Data>
LinkedList<Data>::LinkedList()
{
	head = new Node<Data>{ nullptr };
	Node<Data> tail{ nullptr };
	head->linkToNode(&tail);
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
		currentNode = currentNode->getNext();
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
	Node<Data> nodeWithData{ data };
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

// From https:\/\/www.youtube.com/watch?v=16FI1-d2P4E
struct LinkedListTest : testing::Test
{
	LinkedList<int>* linkedList;

	LinkedListTest()
	{
		linkedList = new LinkedList<int>{};
	}

	virtual ~LinkedListTest()
	{
		delete linkedList;
	}
};

TEST_F(LinkedListTest, HasHead)
{
	Node<int>* head = linkedList->getHead();
	EXPECT_TRUE(head != nullptr);
}
