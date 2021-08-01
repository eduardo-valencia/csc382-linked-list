#pragma once
#include "DynamicTest.h"
#include <iostream>

using namespace std;

class DynamicDeletionTest : DynamicTest
{
	void testOperation()
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
};