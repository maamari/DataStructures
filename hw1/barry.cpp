#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

bool increasing(int a)
{
	if (a > 0) {

		//if the recursive call fails, don't bother to check further.
<<<<<<< HEAD
		if(!increasing(a/10)) return false;
=======
		if (!increasing (a/10)) return false;
>>>>>>> f76dd1d2a81bd00d8e6a7d6d88745a4be4caef8d

		//the least significant digit
		int last = a % 10;

		//the second least significant digit, 0 if a < 10
		int prev = (a / 10) % 10;
<<<<<<< HEAD
		
		//make your changes only below this line.  You may not use any loops
			if(prev <= last) {
				return true;
			}
			else {
				return false;
			}
		}
		return true;		//CHANGE FALSE TO TRUE
	}

=======

		//make your changes only below this line.  You may not use any loops.

		if (prev <= last) return true;

		return false;
	}

	return false;
}

>>>>>>> f76dd1d2a81bd00d8e6a7d6d88745a4be4caef8d
//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an integer." << endl;
    return 1;
  }
  int x = atoi(argv[1]);
  if(increasing(x)) cout << "Increasing order." << endl;
  else cout << "Not increasing order." << endl;
  return 0;
}
