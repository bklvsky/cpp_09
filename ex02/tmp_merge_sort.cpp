#include <iostream>

void merge(int arr [], int left, int mid, int right) {
	// 1. in fact we take 2 subarrays:
	//	left [left ... mid]
	// right [mid + 1, right]
	// both of them are sorted

	// the sorted result will be stored back in the initial arr[left ... right]
	
	// mid = 3, left = 1
	// [1] [2] [3], this is why we need the (+ 1) part
	int leftSubArrSize = mid - left + 1;
	int rightSubArrSize = right - mid;

	int leftSubArr [leftSubArrSize];
	int rightSubArr [rightSubArrSize];

	// stored both of the sorted subarray so that we don't lose the data
	for (int i = 0; i < leftSubArrSize; i++) {
		leftSubArr[i] = arr[left + i];
	}

	for (int i = 0; i < rightSubArrSize; i++) {
		rightSubArr[i] = arr[mid + i + 1];
	}

	// indices to iterate through both subarrays separately from each other
	int leftIndex = 0, rightIndex = 0;
	
	// will be used to iterate through the merged part arr[left ... right], we could have used just
	// the left variable, but it is just cleaner to make another one
	int mergedIndex = left;

	// it will never overflow the arr index, because the size of these arrays combined
	// make up to the "right" variable
	// but we can reach the end of one array and have remained elements in the other one
	while (leftIndex < leftSubArrSize && rightIndex < rightSubArrSize) {
		if (leftSubArr[leftIndex] <= rightSubArr[rightIndex] ) // we used <= to make the algorithm stable
		{
			arr[mergedIndex] = leftSubArr[leftIndex];
			leftIndex += 1;
		} else {
			arr[mergedIndex] = rightSubArr[rightIndex];
			rightIndex += 1;
		}
		mergedIndex += 1;
	}

	// we gather the remained elements if there are any
	while (leftIndex < leftSubArrSize) {
		arr[mergedIndex] = leftSubArr[leftIndex];
		leftIndex += 1;
		mergedIndex += 1;
	}

	while (rightIndex < rightSubArrSize) {
		arr[mergedIndex] = rightSubArr[rightIndex];
		rightIndex += 1;
		mergedIndex += 1;
	}
}

void mergeSort(int arr[], int left, int right) {
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;

	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

void putArray (int arr[], int n) {
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	int arr[] = {0, 3, 4, 10, 7, 2, 9, 1, 5, 6, 8, 11, -2, 12, 5};

	int size = sizeof(arr) / sizeof(arr[0]);
	mergeSort(arr, 0, size - 1);
	putArray(arr, size);
}
