#pragma once
#include "DynamicTest.h"
#include <iostream>

using namespace std;

class DynamicFindTest : DynamicTest
{
	void testOperation()
	{
		Node<string>* letterToFind = promptUserToFindItem();
		showWhetherItemWasFound(letterToFind);
	}
};