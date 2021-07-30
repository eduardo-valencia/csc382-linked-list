#include "pch.h"
#include <gtest/gtest.h>
#include "algorithm"
#include "../csc382-linked-list-2/LinkedList.h"

using namespace std;

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
	tail = new Node<Data>{ nullptr };
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
		currentNode = currentNode->getNext();
		Data* currentData = currentNode->getData();
		if (currentData != nullptr && *currentData == *data)
		{
			return currentNode;
		}
	}
	return nullptr;
}

template <typename Data>
void LinkedList<Data>::insert(Data* data)
{
	Node<Data> nodeWithData{ data };
	Node<Data>* lastNode = tail->getPrevious();
	lastNode->linkToNode(&nodeWithData);
	nodeWithData.linkToNode(tail);
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
	vector<int>& nodeData;

	LinkedListTest(vector<int>& newNodeData) : nodeData{newNodeData}
	{
		linkedList = new LinkedList<int>{};
		vector<int>::iterator currentInt = newNodeData.begin();
		while (currentInt != newNodeData.end())
		{
			++currentInt;
			linkedList->insert(&*currentInt);
		}

	}

	~LinkedListTest()
	{
		delete linkedList;
	}

	int getLength()
	{
		int length = 0;
		Node<int>* currentNode = linkedList->getHead();
		while (currentNode->getNext() != nullptr)
		{
			currentNode = currentNode->getNext();
			++length;
		}
		return length;
	}
};

vector<int> testData{ 1, 2, 3 };

struct FindTest : LinkedListTest
{
	FindTest() : LinkedListTest(testData)
	{

	}

	void testDataFound(int* data)
	{
		Node<int>* foundNode = linkedList->find(data);
		EXPECT_TRUE(foundNode != nullptr);
		//EXPECT_EQ(*foundNode->getData(), *data);
	}

	void testDataNotFound(int* data)
	{
		Node<int>* foundNode = linkedList->find(data);
		EXPECT_EQ(foundNode, nullptr);
	}
};

TEST_F(FindTest, FindsDataAndReturnsNode)
{
	testDataFound(&(testData[1]));
}

//TEST_F(LinkedListTest, HasHead)
//{
//	Node<int>* head = linkedList->getHead();
//	EXPECT_TRUE(head != nullptr);
//}

//struct 