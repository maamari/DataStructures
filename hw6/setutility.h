#include <set>

template<class T>
std::set<T> intersectSet(const std::set<T> one, const std::set<T> two)
{
	std :: set<T> results;
	typename std :: set<T> :: iterator it1 = one.begin(), it2 = two.begin();
	while (it1 != one.end() && it2 != two.end()) {	
		if(*it1 > *it2)
			it2++;
		else if(*it1 < *it2)
			it1++;
		else{
			results.insert(*it1);
			it1++; it2++;
		}
	}
	return results;
}

template<class T>
std::set<T> unionSet(std::set<T> one, const std::set<T> two) {
	typename std::set<T> :: const_iterator it =two.begin();
	while(it != two.end()) {
		if(one.find(*it) == one.end())
			one.insert(*it);
		it++;
	}
	return one;
}