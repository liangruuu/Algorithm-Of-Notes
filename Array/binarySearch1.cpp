#include<iostream>

using namespace std;

template<typename T>

int binarySearch(T arr[], int n, T target) {
	int l = 0, r = n - 1, mid;
	while(l <= r) {
		mid = l + (r - l) / 2;
		if(arr[mid] == target)
			return mid;
		if(arr[mid] > target) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return -1;
}

int main(void) {
	int arr[] = {1,2,3,4,5,6};
	int index;
	index = binarySearch(arr, 6, 6);
	cout << index << endl;

	return 0;
}
