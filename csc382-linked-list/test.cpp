#include "pch.h"
#include "Node.h"
#include "LinkedList.h"
#include <gtest/gtest.h>

// From https:\/\/www.youtube.com/watch?v=16FI1-d2P4E
struct LinkedListTest : testing::Test
{
	LinkedList<int>* linkedList;

	LinkedListTest()
	{
		linkedList = new LinkedList<int>;
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

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

//TEST(LinkedListTest, HasHead)
//{
//	LinkedList<int> linkedList{};
//	EXPECT_TRUE(linkedList.getHead() != nullptr);
//}