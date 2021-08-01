#include "pch.h"
#include <gtest/gtest.h>
#include "algorithm"
#include "LinkedList.h"

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
LinkedList<Data>::LinkedList()
{
	head = new Node<Data>{ nullptr };
	tail = new Node<Data>{ nullptr };
	head->next = tail;
	tail->previous = head;
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
	Node<Data>* lastNode = tail->getPrevious();
	lastNode->next = new Node<Data>{ data };
	lastNode->next->previous = lastNode;
	lastNode->next->next = tail;
	tail->previous = lastNode->next;
}

template <typename Data>
void LinkedList<Data>::Delete(Node<Data>* node)
{
	Node<Data>* previousNode = node->getPrevious();
	Node<Data>* nextNode = node->getNext();
	previousNode->next = nextNode;
	previousNode->next->previous = previousNode;
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
		for (vector<int>::iterator currentInt = newNodeData.begin(); currentInt != newNodeData.end(); ++currentInt)
		{
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
			if (currentNode->getNext() != nullptr)
			{
			++length;
			}
		}
		return length;
	}

	void testDataFound(int* data)
	{
		Node<int>* foundNode = linkedList->find(data);
		EXPECT_TRUE(foundNode != nullptr);
		EXPECT_EQ(*foundNode->getData(), *data);
	}
};

vector<int> testData{ 1, 2, 3 };

struct FindTest : LinkedListTest
{
	FindTest() : LinkedListTest(testData)
	{

	}

	void testDataNotFound(int* data)
	{
		Node<int>* foundNode = linkedList->find(data);
		EXPECT_EQ(foundNode, nullptr);
	}
};

struct InsertionTest : LinkedListTest
{
	InsertionTest() : LinkedListTest(testData)
	{

	}

	void testLength()
	{
		int length = getLength();
		EXPECT_EQ(length, testData.size() + 1);
	}

	void testItemWasInserted(int data)
	{
		testDataFound(&data);
		testLength();
	}
};

struct DeletionTest : LinkedListTest
{
	DeletionTest() : LinkedListTest(testData)
	{

	}

	void testLength()
	{
		int length = getLength();
		EXPECT_EQ(length, testData.size() - 1);
	}

	void testItemWasDeleted(int* data)
	{
		testLength();

		Node<int>* match = linkedList->find(data);
		EXPECT_EQ(match, nullptr);
	}
};

//TEST(Nodes, ShouldLinkToNextNode)
//{
//	int node1Data = 1;
//	int node2Data = 2;
//	Node<int> node1{ &node1Data };
//	Node<int> node2{ &node2Data };
//	node1.linkToNode(node2);
//	EXPECT_EQ(node1.getNext(), &node2);
//	EXPECT_EQ(node2.getPrevious(), &node1);
//}

TEST_F(InsertionTest, InsertsItem)
{
	int newItem = 100;
	linkedList->insert(&newItem);
	testItemWasInserted(newItem);
}

TEST_F(FindTest, FindsDataAndReturnsNode)
{
	testDataFound(&(testData[1]));
}

TEST_F(DeletionTest, DeletesItems)
{
	Node<int>* nodeToDelete = linkedList->getHead()->getNext();
	int nodeData = *nodeToDelete->getData();
	linkedList->Delete(nodeToDelete);
	testItemWasDeleted(&nodeData);
}

//TEST_F(LinkedListTest, HasHead)
//{
//	Node<int>* head = linkedList->getHead();
//	EXPECT_TRUE(head != nullptr);
//}

//struct 