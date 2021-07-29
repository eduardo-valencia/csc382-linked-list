#include "pch.h"
#include "LinkedList.h"

// From https:\/\/www.youtube.com/watch?v=16FI1-d2P4E
struct LinkedListTest : testing::Test
{
	LinkedList<int>* linkedList;

	LinkedListTest()
	{
		linkedList = new LinkedList<int>;
	}
};

TEST()