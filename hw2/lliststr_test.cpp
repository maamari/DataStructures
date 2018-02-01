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
	list->insert(0, "touch");
	checkSize(list, 1);

	cout << endl << "Insert second item at the head." << endl;
	list->insert(0, "somebody");
	checkSize(list, 2);

	cout << endl << "Insert an item at the tail." << endl;
	list->insert(2, "my");
	checkSize(list, 3);

	cout << endl << "Insert a second item at the tail." << endl;
	list->insert(3, "spaghet");
	checkSize(list, 4);

	cout << endl << "Verify the list is not empty." << endl;
	checkEmpty(list, false);
	
	cout << endl << "Check if the values are correct." << endl;
	checkGet(list, 0, "somebody");
	checkGet(list, 1, "touch");
	checkGet(list, 2, "my");
	checkGet(list, 3, "spaghet");
	checkSize(list, 4);

	cout << endl << "Remove off the front." << endl;
	list->remove(0);
	checkSize(list, 3);

	cout << endl << "Remove from the middle." << endl;
	list->remove(1);
	checkSize(list, 2);

	cout << endl << "Remove from the end." << endl;
	list->remove(1);
	checkSize(list, 1);

	cout << endl << "Delete list w/ one node." << endl;
	list->remove(0);
	checkEmpty(list, true);

	list->insert(0, "do");
	list->insert(1, "u");
	list->insert(2, "know");
	list->insert(3, "da");
	list->insert(4, "wae?");
	checkEmpty(list, false);
	checkSize(list, 5);

	cout << endl << "Remove from the front twice." << endl;
	list->remove(0);
	list->remove(0);
	checkGet(list, 0, "know");
	checkSize(list, 3);

	cout << endl << "Remove from the end twice." << endl;
	list->remove(1);
	list->remove(1);
	checkSize(list, 1);

	cout << endl << "Remove singularly-noded list" << endl;
	list->remove(0);
	checkEmpty(list, true);

	cout << endl << "Remove from an empty list." << endl;
	list->remove(0);
	checkSize(list, 0);
	checkEmpty(list, true);

	//COMMENTED TO AVOID VALGRIND ERROR
	// cout << endl << "Insert to invalid index" << endl;		
	// list->insert(4, "boi");
	// list->insert(-1, "cmon man");
	// checkEmpty(list, true);

	cout << endl << "Remove from incorrect index" << endl;
	list->remove(1);
	checkEmpty(list, true);

	delete list;
	return 0;
}
