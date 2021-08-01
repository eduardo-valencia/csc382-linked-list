#pragma once
#include "DynamicTest.h"
#include <iostream>

using namespace std;

class DynamicDeletionTest : DynamicTest
{
	void testOperation()
	{
		string letterToDelete = prompt("What letter do you want to delete?");
		Node<string>* match = showWhetherItemWasFound(match);
		if (match == nullptr)
		{
			cout << "Invalid item to delete.";
			return;
		}
		linkedList.Delete(match);
		showWhetherItemWasFound(match);
	}
};