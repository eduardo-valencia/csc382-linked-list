// Defines the a doubly linked list.
// Uses Google Test
// Data is a generic type that the LinkedList's nodes will store.

#include "pch.h"
#include <gtest/gtest.h>
#include "algorithm"
#include "LinkedList.h"
#include "DynamicTest.h"
#include "DeletionTest.h"
#include "FindTest.h"

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
	head = new Node<Data>{defaultValue};
	tail = new Node<Data>{defaultValue};
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

// From https:\/\/www.youtube.com/watch?v=16FI1-d2P4E
// A test structure with helper methods for testing the linked list.
// Has a linkedList property, which is the list that we will test.
// Contains nodeData for data that should be inserted before the test.
struct LinkedListTest : testing::Test
{
	LinkedList<int>* linkedList;
	vector<int> nodeData;

	// Constructor to instantiate properties
	LinkedListTest()
	{
		linkedList = new LinkedList<int>{0};
		nodeData = vector<int>{};
	}

	// Destructor
	~LinkedListTest()
	{
		delete linkedList;
	}

	// Inserts all data from nodeData into the linked list
	void insertNodeData()
	{
		vector<int>::iterator currentInt = nodeData.begin();
		for (vector<int>::iterator currentInt = nodeData.begin(); currentInt != nodeData.end(); ++currentInt)
		{
			linkedList->Insert(*currentInt);

		}
	}

	// Returns length of the linked list
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

	// Tests that the given data pointer's exists in the list and that the given data matches the found data.
	void testDataFound(int* data)
	{
		Node<int>* foundNode = linkedList->Find(data);
		EXPECT_TRUE(foundNode != nullptr);
		EXPECT_EQ(*foundNode->getData(), *data);
	}
};

// Provides utility methods for testing the find operation
struct FindTest : LinkedListTest
{
	FindTest() : LinkedListTest()
	{

	}

	// Tests that data is not in the list.
	void testDataNotFound(int* data)
	{
		Node<int>* foundNode = linkedList->Find(data);
		EXPECT_EQ(foundNode, nullptr);
	}
};

// Provides utility methods for testing insertions
// Defines itemToInsert as default number to insert during testing
struct InsertionTest : LinkedListTest
{
	int itemToInsert;

	InsertionTest() : itemToInsert{ 100 }
	{

	}

	// Inserts the default number to insert
	void insertInteger()
	{
		linkedList->Insert(itemToInsert);
	}

	// Tests that list's length matches expected value.
	// Expected size calculated from node data
	void testLength()
	{
		int length = getLength();
		EXPECT_EQ(length, nodeData.size() + 1);
	}

	// Tests that data is in the list and that list size increased
	void testItemWasInserted(int data)
	{
		testDataFound(&data);
		testLength();
	}
};

// Provides utility methods for testing deletions
struct DeletionTest : LinkedListTest
{
	DeletionTest()
	{

	}

	// Tests that the length decreased
	void testLength()
	{
		int length = getLength();
		EXPECT_EQ(length, nodeData.size() - 1);
	}

	// Tests length decreased and that item was not found in list
	void testItemWasDeleted(int* data)
	{
		testLength();
		Node<int>* match = linkedList->Find(data);
		EXPECT_EQ(match, nullptr);
	}
};

// Like DeletionTest struct, but also inserts some nodes by default.
struct DeletionTestWithExistingNodes : DeletionTest
{
	// Constructor
	// Adds node data for testing, then inserts node data into linked list.
	DeletionTestWithExistingNodes()
	{
		nodeData.push_back(1);
		nodeData.push_back(2);
		nodeData.push_back(3);
		insertNodeData();
	}
};

// Tests item was inserted
TEST_F(InsertionTest, InsertsItem)
{
	insertInteger();
	testItemWasInserted(itemToInsert);
}

// Tests item was inserted when nodes already exist
TEST_F(InsertionTest, InsertsItemWhenNodesExist)
{
	nodeData.push_back(2);
	insertNodeData();
	insertInteger();
	testItemWasInserted(itemToInsert);
}

// Tests find operation returns pointer to node
TEST_F(FindTest, FindsDataAndReturnsNode)
{
	nodeData.push_back(2);
	insertNodeData();
	testDataFound(&(nodeData[0]));
}

// Tests find returns null pointer when data does not exist.
TEST_F(FindTest, ReturnsNullPointerWhenItemDoesNotExist)
{
	int numberToFind = 100;
	testDataNotFound(&numberToFind);
}

// Tests deletion operation deletes a specific node, and only that node.
TEST_F(DeletionTestWithExistingNodes, DeletesItems)
{
	Node<int>* nodeToDelete = linkedList->getHead()->getNext();
	int nodeData = *nodeToDelete->getData();
	linkedList->Delete(nodeToDelete);
	testItemWasDeleted(&nodeData);
}

// Add dynamic test constructor.
// Takes the test name and makes a linked list for testing
DynamicTest::DynamicTest(string name) : name{ name }, linkedList{LinkedList<string>{""}}
{
}

// Prompts the user and returns their answer
string DynamicTest::prompt(string question)
{
	cout << question << endl;
	string answer;
	cin >> answer;
	return answer;
}

// Asks the user what letter they want to insert, then inserts it.
void DynamicTest::promptUserToInsertDataItem(bool& shouldContinue)
{
	string itemToInsert = prompt("What letter do you want to insert?");
	linkedList.Insert(itemToInsert);
	string shouldContinueAnswer = prompt("Do you want to insert another item? (yes/no)");
	shouldContinue = shouldContinueAnswer == "yes";
}

// Asks the user what letters they want to insert.
// Continues until they stop saying yes.
void DynamicTest::promptUserToInsertData()
{
	bool shouldContinue = true;
	while (shouldContinue)
	{
		promptUserToInsertDataItem(shouldContinue);
	}
}

// Asks the user what letter they want to find, then returns the match
Node<string>* DynamicTest::promptUserToFindItem()
{
	string letterToFind = prompt("Type in the letter to find.");
	return linkedList.Find(&letterToFind);
}

// Shows whether the match was found, given a pointer.
void DynamicTest::showWhetherItemWasFound(Node<string>* item)
{
	if (item == nullptr)
	{
		cout << "Item not found\n";
	}
	else
	{
		cout << "Item found.\n";
	}
}

// Says the name of the test, asks the user to insert data, and tests the operation.
void DynamicTest::startTest()
{
	cout << "Beginning test " << name << endl;
	promptUserToInsertData();
	testOperation();
}

// Find test's constructor
// The find test also acts as the insertion test because it reports whether the inserted items were found.
// Sets the test name for find operation
DynamicFindTest::DynamicFindTest() : DynamicTest("insertion and find")
{

}

// Asks the user what letter they want to find, then shows whether it was found
void DynamicFindTest::testOperation()
{
	Node<string>* letterToFind = promptUserToFindItem();
	showWhetherItemWasFound(letterToFind);
}

// Sets deletion test name
DynamicDeletionTest::DynamicDeletionTest() : DynamicTest("deletion")
{

}

// Asks the user what letter they want to delete assuming they will enter one of the letters they inserted.
// If they entered a valid letter, it will delete the item and report whether it was found after the deletion.
// If it was not found after deletion, then it was successful.
void DynamicDeletionTest::testOperation()
{
	string letterToDelete = prompt("What letter do you want to delete?");
	Node<string>* match = linkedList.Find(&letterToDelete);
	showWhetherItemWasFound(match);
	if (match == nullptr)
	{
		cout << "Invalid item to delete.";
		return;
	}
	linkedList.Delete(match);
	showWhetherItemWasFound(match);
}


// Runs the dynamic tests.
int main()
{
	DynamicFindTest findTest{};
	findTest.startTest();
	DynamicDeletionTest deletionTest{};
	deletionTest.startTest();
	return 0;
}