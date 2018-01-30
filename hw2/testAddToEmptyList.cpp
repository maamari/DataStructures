#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

int main() {
	LListStr* list = new LListStr();

	// Check if the list is initially empty.
	checkEmpty(list, true);
	checkSize(list, 0);

	// Insert an item at the head.
	list->insert(0, "CSCI104");

	// Verify the list is not empty
	checkEmpty(list, false);
	checkSize(list, 1);

	// Check if the value is correct.
	checkGet(list, 0, "CSCI104");

	//remove off the front
	list->remove(0);
	checkEmpty(list, true);
	checkSize(list, 0);

	//insert multiple items
	list->insert(0, "Hotdogs");
	list->insert(1, "are");
	list->insert(2, "sandwiches");
	checkEmpty(list, false);
	checkSize(list, 3);

	//remove from the middle;
	list->remove(1);
	checkEmpty(list, false);
	checkSize(list, 2);

	//remove from the end;
	list->remove(1);

	//deletion of list


	// TODO: Continue adding tests for your program, or start your own file with your
	// own tests. Remember to submit a file that is named correctly!

	// Clean up memory.
	delete list;
}
