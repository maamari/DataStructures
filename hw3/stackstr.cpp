#include "stackstr.h"

StackStr::StackStr() {

}

StackStr::~StackStr() {
}

/**
* Returns true if the stack is empty, false otherwise
*/
bool StackStr::empty() const {
	return (list_.empty());
}

int StackStr::size() const{
	return list_.size();
}

/**
* Pushes a new value, val, onto the top of the stack
*/
void StackStr::push (const std::string& val) {
	list_.insert(list_.size(), val);
}

/**
* Returns the top value on the stack.
* If the stack is empty, the correct behavior is to throw
* an exception: use LList_String::get to achieve this.
*/
std::string StackStr::top () const {
	return list_.get(list_.size()-1);
}

/**
* Removes the top element on the stack.
* Should do nothing if the stack is empty.
*/
void StackStr::pop () {
	if(list_.empty())
		return;
	list_.remove(list_.size()-1);
}