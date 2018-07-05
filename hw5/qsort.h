#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include "functor.h"

template <class T>
void swap(std :: vector<T> &arr, int &one, int &two) {
	T temp = arr[one];
	arr[one] = arr[two];
	arr[two] = temp;
}


template <class T, class Comparator>
int partition(std :: vector<T> &arr, int left, int right, Comparator comp) {
	int middle = (left + right)/2, front = left;
	T pvt = arr[right];

	// if(comp(arr[middle], arr[left])) swap(arr, left, middle);
	// if(comp(arr[right], arr[left])) swap(arr, right, left);
	// if(comp(arr[right], arr[middle])) swap(arr, right, middle);

	// swap(arr, middle, right);

	while(front < right){
		if(comp(arr[front], pvt) || arr[front] == pvt) {
			swap(arr, left, front);
			left++;
		}
		front++;
	}
	swap(arr, left, right);
	return left;
} 

template <class T, class Comparator>
void RealQuickSort(int begin, int end, std :: vector<T> &arr, Comparator comp) {
	if(begin < end) {
		int location = partition(arr, begin, end, comp);
		RealQuickSort(begin, location-1, arr, comp);
		RealQuickSort(location+1, end, arr, comp);
 	}               
}

template <class T, class Comparator>
void QuickSort(std :: vector<T> &arr, Comparator comp) {
	RealQuickSort(0 , (int)arr.size()-1, arr, comp);
}