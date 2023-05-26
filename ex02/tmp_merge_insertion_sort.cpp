#include <list>
#include <iostream>

void swap(int & a, int & b) {
	a += b;
	b = a - b;
	a -= b;
}

// class Pair {
// 	public:
// 	Pair() : first(0), second(0) {}

// 	Pair (int first, int second): first(first), second(second) {}
// 	~Pair() {}

// 	int first;
// 	int second;
// 	void sort() {
// 		if (first > second) {
// 			swap (first, second);
// 		}
// 	}
// };

// std::ostream & operator<< (std::ostream & s, const Pair & rhs) {
// 	s << "[" << rhs.first << ", " << rhs.second << "]";
// 	return s;
// }

// Determine if the array is even or odd numbered in length. 
// If odd, remove the last number, designate it as a ‘straggler’ and insert it later into the sorted array.

// Arbitrarily divide the sequence to sort into pairs of two values.

// Sort the pairs bitwise, so the order is always [less, greater].

// Sort the sequence recursively by the value of it’s largest pair.

// Create a new sequence ‘S’, by pulling out the [highest] value of each pair and inserting it into ‘S’.

// The remaining values form a temporary ‘pend’ array.

// Based on the length of ‘pend’, build the optimal insertion sequence using relevant Jacobsthal numbers.

// Loop through the elements in ‘pend’, and using the insertion sequence built in the previous step, 
// use binary search to insert each ‘pend’ element into ‘S’.

// If a ‘straggler’ was found, do a leftover loop and insertion to complete the list.


// size = 5
// 0 1 | 2 3 | 4

// fourth fucks off size = 4

// i should be less than size but the step is 2

void mergeSort(int arr [], size_t size) {
	int staggler = -1;
	if (size % 2 != 0) {
		staggler = arr[size - 1];
		size -= 1;
	}

	for (int i = 0; i < size ; i += 2) {
		if (arr[i] > arr[i + 1])
			swap(arr[i], arr[i + 1]);
			std::cout << "[" << arr[i] << ", " << arr[i + 1] << "]" << " ";
	}
	std::cout << std::endl;
}

void putArray (int arr[], int n) {
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}


int main()
{
	int arr[] = {0, 3, 4, 10, 7, 2, 9, 1, 5, 6, 8, 11, 2, 12, 5};

	int size = sizeof(arr) / sizeof(arr[0]);
	mergeSort(arr, size);
	// putArray(arr, size);
}
