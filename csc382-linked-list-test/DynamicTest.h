#pragma once
#include "LinkedList.h"
#include <iostream>

using namespace std;

class DynamicTest
{
private:
	string name;

protected:
	LinkedList<string> linkedList;

public:
	DynamicTest(string name);

	string prompt(string question);

	void promptUserToInsertDataItem(bool& shouldContinue);

	void promptUserToInsertData();

	void virtual testOperation() = 0;

	Node<string>* promptUserToFindItem();

	void showWhetherItemWasFound(Node<string>* item);

	void startTest();
};