#include <iostream>
#include "lliststr.h"

using namespace std;

LListStr::LListStr() {
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

LListStr::~LListStr() {
	while(head_) {
		Item *temp = head_->next;
		delete head_;
		head_ = temp;
	}
	
	tail_ = NULL;
	size_ = 0;
}

int LListStr::size() const {
	return size_;
}

bool LListStr::empty() const {
	if(!size_) {
		return true;
	}
	else {
		return false;
	}
}

void LListStr::insert(int pos, const std::string &val) {
	Node* inFront = posTraverser(pos);
	Node* behind = posTraverser(pos-1);
	Node* newNode = new Node();	

	//set newNode?

	newNode->next = behind->next;
	behind->next = newNode;
	newNode->prev = inFront->prev;
	inFront->prev = newNode;
}

void LListStr::remove(int pos) {
	Node* inFront = posTraverser(pos);
	Node* behind = posTraverser(pos-1);
	Node* removed = new Node();	
 	// Node* inFront = new Node();
	// Node* behind = new Node();
	// Node* removed = new Node();
	// int posCounter = 0;

	// while(posCounter != pos){
	// 	behind = inFront;
	// 	inFront = inFront->next;
	// 	posCounter++;
	// }

	behind->next = removed->next;
	inFront->prev = removed->prev;
	
	removed->next = NULL; removed->prev = NULL; removed->val = NULL;
}

void LListStr::set(int pos, const std::string &val) {
	Node* setNode = new Node();
	int posCounter = 0;

	while(posCounter != pos){
		setNode = setNode->next;
		posCounter++;
	}

	setNode->val = val;
}

std::string LListStr::get(int pos) const{
  	Node* setNode = new Node();
	int posCounter = 0;

	while(posCounter != pos){
		setNode = setNode->next;
		posCounter++;
	}

	return setNode->val;
}

LListStr::Item* LListStr::posTraverser(int pos){
	Node* current = new Node();
	int posCounter = 0;

	while(posCounter != pos){
		current = current->next;
		posCounter++;
	}

	return current;
}