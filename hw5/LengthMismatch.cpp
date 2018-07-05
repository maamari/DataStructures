#include "LengthMismatch.h"
#include <string>
using namespace std;

LengthMismatch :: LengthMismatch (int len1, int len2) {
	mismatch = "Data structures have lengths " + 
	to_string(len1) + " & " + to_string(len2);
}

string LengthMismatch :: what() {
	return mismatch;
}