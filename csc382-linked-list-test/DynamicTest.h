#pragma once
#include "LinkedList.h"
#include <iostream>

using namespace std;

class DynamicTest
{
private:
	LinkedList<string> linkedList;
	string name;

public:
	DynamicTest(string name);

	string prompt(string question);

	void promptUserToInsertDataItem(bool& shouldContinue);

	void promptUserToInsertData();

	void virtual testOperation();

	Node<string>* promptUserToFindItem();

	static void startTest();
};