#include <iostream>
using namespace std;

struct Node {
    int value;
    Node *next;
};

int whileLoop(Node* in);
int swapper(Node* in);

Node* fullsort(Node* in){					//calls helper functions
	whileLoop(in);
	return in;
}

int whileLoop(Node* in){					//imitates while loop recursively
	if(swapper(in) != 0)					//while swaps occur
		return whileLoop(in);				//continue to swap
	else return 0;
}

int swapper(Node* in){						
	if(!in->next) return 0;					//if you reach end, return NULL		
	if(in->value <= in->next->value) 		//if current is less than next
		return swapper(in->next);			//recurse
	else {									
		int temp = in->value;				//otherwise, swap current w next val
		in->value = in->next->value;
		in->next->value = temp;	
		return 1;							//return 1 for whileLoop function
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

	// cout << a.value << " " << a.next->value << " " << a.next->next->value;
	// cout << " " << a.next->next->next->value << " ";
	// cout << a.next->next->next->next->value << endl;

	//return 1;
// }