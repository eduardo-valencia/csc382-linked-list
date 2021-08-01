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

template <typename Data>
void LinkedList<Data>::Insert(Data* data)
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
	vector<int> nodeData;

	LinkedListTest()
	{
		linkedList = new LinkedList<int>{};
		nodeData = vector<int>{};
	}

	~LinkedListTest()
	{
		delete linkedList;
	}

	void insertNodeData()
	{
		vector<int>::iterator currentInt = nodeData.begin();
		for (vector<int>::iterator currentInt = nodeData.begin(); currentInt != nodeData.end(); ++currentInt)
		{
			linkedList->Insert(&*currentInt);

		}
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
		Node<int>* foundNode = linkedList->Find(data);
		EXPECT_TRUE(foundNode != nullptr);
		EXPECT_EQ(*foundNode->getData(), *data);
	}
};

struct FindTest : LinkedListTest
{
	FindTest() : LinkedListTest()
	{

	}

	void testDataNotFound(int* data)
	{
		Node<int>* foundNode = linkedList->Find(data);
		EXPECT_EQ(foundNode, nullptr);
	}
};

struct InsertionTest : LinkedListTest
{
	int itemToInsert;

	InsertionTest() : itemToInsert{ 100 }
	{

	}

	void insertInteger()
	{
		linkedList->Insert(&itemToInsert);
	}

	void testLength()
	{
		int length = getLength();
		EXPECT_EQ(length, nodeData.size() + 1);
	}

	void testItemWasInserted(int data)
	{
		testDataFound(&data);
		testLength();
	}
};

struct DeletionTest : LinkedListTest
{
	DeletionTest()
	{

	}

	void testLength()
	{
		int length = getLength();
		EXPECT_EQ(length, nodeData.size() - 1);
	}

	void testItemWasDeleted(int* data)
	{
		testLength();

		Node<int>* match = linkedList->Find(data);
		EXPECT_EQ(match, nullptr);
	}
};

struct DeletionTestWithExistingNodes : DeletionTest
{
	DeletionTestWithExistingNodes()
	{
		nodeData.push_back(1);
		nodeData.push_back(2);
		nodeData.push_back(3);
		insertNodeData();
	}
};

TEST_F(InsertionTest, InsertsItem)
{
	insertInteger();
	testItemWasInserted(itemToInsert);
}

TEST_F(InsertionTest, InsertsItemWhenNodesExist)
{
	nodeData.push_back(2);
	insertNodeData();
	insertInteger();
	testItemWasInserted(itemToInsert);
}

TEST_F(FindTest, FindsDataAndReturnsNode)
{
	nodeData.push_back(2);
	insertNodeData();
	testDataFound(&(nodeData[0]));
}

TEST_F(FindTest, ReturnsNullPointerWhenItemDoesNotExist)
{
	int numberToFind = 100;
	testDataNotFound(&numberToFind);
}

TEST_F(DeletionTestWithExistingNodes, DeletesItems)
{
	Node<int>* nodeToDelete = linkedList->getHead()->getNext();
	int nodeData = *nodeToDelete->getData();
	linkedList->Delete(nodeToDelete);
	testItemWasDeleted(&nodeData);
}

//TEST_F(DeletionTestWithExistingNodes, DoesNotDeleteAnythingWhenDataNotFound)
//{
//	Node<int>
//}
