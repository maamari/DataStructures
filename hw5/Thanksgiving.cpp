#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include "LengthMismatch.h"
#include "qsort.h"
#include "functor.h"

using namespace std;

vector<pair <int, int> > assignPlates(vector<int> t, vector<int> p)
{	 
	sort(t.begin(), t.end());
	sort(p.begin(), p.end());

	unsigned int tSize = (int)t.size(), pSize = (int)p.size(), plate = 0;
	vector<pair <int, int> > result;

	if(tSize != pSize)
		throw LengthMismatch(tSize,pSize);

	while(plate < pSize) {
		if(p[plate]+t[tSize-1-plate] != t[tSize-1] + p[0]) {
			result.clear();
			break;
		}
		result.push_back(pair<int, int> (t[pSize-1-plate], p[plate]));
		plate++;
	}
	return result;
}
