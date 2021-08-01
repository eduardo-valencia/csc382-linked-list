#pragma once
#include "DynamicTest.h"
#include <iostream>

using namespace std;

class FindTest : DynamicTest
{
	void testOperation()
	{
		Node<string>* letterToFind = promptUserToFindItem();
		showWhetherItemWasFound();
	}
};