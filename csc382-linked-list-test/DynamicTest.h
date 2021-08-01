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

	void virtual testOperation();

	Node<string>* promptUserToFindItem();

	Node<string>* showWhetherItemWasFound(Node<string>* item);

	static void startTest();
};