#include <iostream>
#include "main.h"

using namespace std;

int main()
{
	cout << "Hello, world\n";
	LinkedList<int> myLinkedList{ 0 };
	myLinkedList.Insert(100);
	return 0;
}
