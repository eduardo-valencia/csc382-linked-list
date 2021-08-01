#pragma once
#include "DynamicTest.h"
#include <iostream>

using namespace std;

class FindTest : DynamicTest
{
	void testOperation()
	{
		Node<string>* letterToFind = promptUserToFindItem();
		if (letterToFind == nullptr)
		{
			cout << "Item not found\n";
		}
		else
		{
			cout << "Item found.\n";
		}
	}
};