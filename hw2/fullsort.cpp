#include <iostream>
using namespace std;

struct Node {
    int value;
    Node *next;
};

int helper1(Node* in);
int helper(Node* in);

Node* fullsort(Node* in){
	helper1(in);
	return in;
}

int helper1(Node* in){
	if(helper(in) != 0)	return helper1(in);
	else return 0;
}

int helper(Node* in){
	if(!in->next) return 0;							
	if(in->value <= in->next->value) return helper(in->next);
	else {
		int temp = in->value;				
		in->value = in->next->value;
		in->next->value = temp;	
		return 1;
	}
}


// int main(){

	// Node a, b, c, d, e;
	// a.value = 2;
	// b.value = 3;
	// c.value = 1;
	// d.value = 4;
	// e.value = 5;
	// a.next = &b;
	// b.next = &c;
	// c.next = &d;
	// d.next = &e;
	// e.next = NULL;

	// fullsort(&a);

	// cout << a.value << " " << a.next->value << " " << a.next->next->value << " " << a.next->next->next->value << " " << a.next->next->next->next->value;

	//return 1;
// }