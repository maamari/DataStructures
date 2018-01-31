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

	cout << "Check if the list is initially empty." << endl;
	checkEmpty(list, true);
	checkSize(list, 0);

	cout << endl << "Insert an item at the head." << endl;
	list->insert(0, "CSCI104");
	checkSize(list, 1);

	cout << endl << "Insert second item at the head." << endl;
	list->insert(0, "CSCI201");
	checkSize(list, 2);

	cout << endl << "Verify the list is not empty." << endl;
	checkEmpty(list, false);
	
	cout << endl << "Check if the value is correct." << endl;
	checkGet(list, 0, "CSCI201");
	checkGet(list, 1, "CSCI104");
	checkSize(list, 2);

	cout << endl << "Remove off the front." << endl;
	list->remove(0);
	checkSize(list, 1);
	list->remove(0);
	checkEmpty(list, true);

	cout << endl << "Insert multiple items." << endl;
	list->insert(0, "Hotdogs");
	list->insert(1, "are");
	list->insert(2, "sandwiches");
	checkEmpty(list, false);
	checkSize(list, 3);

	cout << endl << "Remove from the middle." << endl;
	list->remove(1);
	checkEmpty(list, false);
	checkGet(list, 0, "Hotdogs");
	checkGet(list, 1, "sandwiches");
	checkSize(list, 2);

	cout << endl << "Remove from the end." << endl;
	list->remove(1);
	list->remove(0);
	checkEmpty(list, true);
	checkSize(list, 0);

	cout << endl << "Error avoider." << endl;
	list->insert(0, "Test");

	// TODO: Continue adding tests for your program, or start your own file with your
	// own tests. Remember to submit a file that is named correctly!

	// Clean up memory.
	delete list;
}
